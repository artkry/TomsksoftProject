#include "dbfasade.h"
#include "daywidget.h"

int DBFasade::authId = 0;
int DBFasade::calcTime = 31;

DBFasade::DBFasade()
{
	sdb = QSqlDatabase::addDatabase("QSQLITE");
	sdb.setDatabaseName("database.db");

	if (!sdb.open()) {
		qDebug() << "Can't open DataBase (DBFasade constructor error)";
	}

	query = new QSqlQuery(sdb);

	if (!sdb.tables().contains("Users")) {
		query->exec("CREATE TABLE Users ("
			"id INTEGER PRIMARY KEY AUTOINCREMENT, "
			"profile_name TEXT NOT NULL UNIQUE, "
			"passwd TEXT NOT NULL"
			");"
		);
	}

	if (!sdb.tables().contains("UsersData")) {
		query->exec("CREATE TABLE UsersData ("
			"uid INTEGER, "
			"dtime TEXT NOT NULL, "
			"incoming REAL DEFAULT 0, "
			"expense REAL DEFAULT 0, "
			"surplus REAL, "
			"FOREIGN KEY (uid) REFERENCES Users(id)"
			");"
		);
	}

}

DBFasade::~DBFasade() 
{
	delete query;
	//sdb.close();
	//sdb.removeDatabase(sdb.connectionName());
	delete &rec;
}

bool DBFasade::authRequest(QString login, QString pass)
{
	query->clear();

	bool isCorrect;
	QString str_ = "SELECT passwd, id FROM Users WHERE Users.profile_name LIKE '%1';";
	QString str = str_.arg(login);
	isCorrect = query->exec(str);

	if(!isCorrect){
		qDebug() << "authRequest failed (DBFasade query)";
		return false;
	}
	else {
		qDebug() << "authRequest success (DBFasade query)";
	}

	rec = query->record();
	query->first();

	if (query->value(rec.indexOf("passwd")).toString() == pass) {
		authLogin = login;
		authId = query->value(rec.indexOf("id")).toInt();
		//qDebug() << authLogin;
		qDebug() << "authidrequest:" << authId;
		return true;
	}
	else {
		qDebug() << "Incorrect pass! (DBFasade authRequest)";
		return false;
	}
}

bool DBFasade::createUser(QString login, QString pass)
{
	if (isCreated(login)) {
		query->clear();
		bool isCorrect;
		QString str_ = "INSERT INTO Users (profile_name, passwd) VALUES ('%1','%2');";
		QString str = str_.arg(login).arg(pass);

		isCorrect = query->exec(str);

		if (!isCorrect) {
			qDebug() << "Create User failed(DBFasade createUser)";
			return false;
		}
		else {
			qDebug() << "Create User success(DBFasade createUser)";
			return true;
		}
	}
	else {
		return false;
	}
	
}

bool DBFasade::isCreated(QString login) 
{
	query->clear();

	bool isCorrect;
	QString str_ = "SELECT id FROM Users WHERE Users.profile_name = '%1';";
	QString str = str_.arg(login);
	isCorrect = query->exec(str);

	rec = query->record();
	query->first();

	if (query->value(rec.indexOf("id")).toInt() != 0) {
		qDebug() << "This profile name is already exists! Try again.";
		return false;

	}
	else {
		qDebug() << "All right.";
		return true;
	}
}

bool DBFasade::pullUserData() 
{
	query->clear();

	bool isCorrect;
	QString str_ = "SELECT dtime, incoming, expense, surplus FROM UsersData WHERE UsersData.uid = '%1' ORDER BY dtime;";
	qDebug() << authId;
	QString str = str_.arg(authId);

	isCorrect = query->exec(str);

	if (!isCorrect) {
		qDebug() << "pullRequest failed (DBFasade query)";
		return false;
	}
	else {
		qDebug() << "pullRequest ok (DBFasade query)";
	}

	//кидаем данные в буфер
	rec = query->record();
	//int itter = 0;
	QString dtimeQ = "";
	double incomingQ = 0.0;
	double expenseQ = 0.0;
	double surplusQ = 0.0;
	
	while (query->next()) {
		dtimeQ = query->value(rec.indexOf("dtime")).toString();
		incomingQ = query->value(rec.indexOf("incoming")).toDouble();
		expenseQ = query->value(rec.indexOf("expense")).toDouble();
		surplusQ = query->value(rec.indexOf("surplus")).toDouble();

		qDebug() << "cicle";
		qDebug() << dtimeQ;
		qDebug() << incomingQ;
		qDebug() << expenseQ;
		qDebug() << surplusQ;

		fillBufer(incomingQ, expenseQ, surplusQ, dtimeQ);
	}

	return true;
}

void DBFasade::removeUserData()
{
	query->clear();

	bool isCorrect;
	QString str_ = "DELETE FROM UsersData WHERE UsersData.uid = '%1';";
	QString str = str_.arg(authId);

	isCorrect = query->exec();

	if (!isCorrect) {
		qDebug() << "removeRequest failed (DBFasade query)";
	}
	else {
		qDebug() << "removeRequest ok (DBFasade query)";
	}
}

void DBFasade::pushUserDataSQL(double inComing_, double expense_, double surPlus_, QString date_)
{
	query->clear();

	bool isCorrect;
	QString str_ = "INSERT INTO UsersData(uid, dtime, incoming, expense, surplus)"
		"VALUES(%1, '%2', %3, %4, %5)";
	QString str = str_.arg(authId).arg(date_).arg(inComing_).arg(expense_).arg(surPlus_);
	
	isCorrect = query->exec(str);

	if(!isCorrect){
		qDebug() << "pushRequest failed (DBFasade query)";
		//return false;
	}
	else {
		qDebug() << "pushRequest ok (DBFasade query)";
		//return true;
	}
}

void DBFasade::pushData()
{
	QList<dateBufer>::iterator count;

	for (count = bufer.begin(); count != bufer.end(); ++count) {
		pushUserDataSQL(count->inComingB, count->expenseB, count->surPlusB, count->date);
	}
}

void DBFasade::fillBufer(double inComing_, double expense_, double surPlus_, QString date_)
{
	dateBufer item;
	item.date = date_;
	item.inComingB = inComing_;
	item.expenseB = expense_;
	item.surPlusB = surPlus_;
	
	bufer.append(item);
}

void DBFasade::fillDayWidgetFromBufer(DayWidget &day)
{
	QList<dateBufer>::iterator count;

	QString dayDate = day.getDate();
	
	//qDebug() << "enter func";
	for (count = bufer.begin(); count != bufer.end(); ++count) {
		if (count->date == dayDate) {
			//qDebug() << "enter if";
			day.setInComing(count->inComingB);
			day.setExpense(count->expenseB);
			day.setSurPlus(count->surPlusB);
			break;
		}
	}
	//qDebug() << "close func";
}

void DBFasade::calculateChanges(QString date_, double inComing_, double expense_, double surPlus_)
{
	QList<dateBufer>::iterator count;
	int itter = 0;

	QString currentDate = date_;
	int currentIndex = 0;
	//цикл поиска таргетного дня в буфере
	for (count = bufer.begin(); count != bufer.end(); ++count) {
		if (count->date == date_) {
			count->inComingB += inComing_;
			count->expenseB += expense_;
			//если поле остаток пустое
			if (surPlus_ == 0.0) {
				QList<dateBufer>::iterator sCount;
				QString yesterdayDate = minusStringDay(date_);
				int flag = 0;
				/*ищем остаток с предыдущего дня, если предыдущий день есть,
				то расчитываем с его учетом*/ 
				for (sCount = bufer.begin(); sCount != bufer.end(); ++sCount) {
					if (sCount->date == yesterdayDate) {
						count->surPlusB = sCount->surPlusB + count->inComingB - count->expenseB;
						flag = 1;
					}
				}
				//если предыдущего дня нет в буфере, то остаток считаем из разности прихода\расхода
				if (flag == 0) {
					count->surPlusB = count->inComingB - count->expenseB;
				}

			}
			else { count->surPlusB = surPlus_; }//если поле остаток не пустое, то просто пишем его в буфер этого дня
			
			itter = count - bufer.begin();

			break;
		}
	}
	//если таргетного дня нет в буфере, то создаем его
	if (itter == 0) {
		dateBufer item;
		item.date = currentDate;
		item.inComingB = inComing_;
		item.expenseB = expense_;

		if (surPlus_ == 0.0) {
			item.surPlusB = item.inComingB - item.expenseB;
		}
		else { item.surPlusB = surPlus_; }
		bufer.append(item);

		itter = bufer.size() - 1;
	}
	//цикл заполнения остальных 30 дней
	for (int i = 0; i < calcTime - 1; i++) {
		currentIndex = itter;
		currentDate = addStringDay(currentDate);
		//ищем, существует ли запись о дне в буфере
		//если да - то пересчитываем с учетом вчерашнего остатка
		QList<dateBufer>::iterator tcount;
		for (tcount = bufer.begin(); tcount != bufer.end(); ++tcount) {
			if (tcount->date == currentDate) {
				
				QList<dateBufer>::iterator fcount = tcount;
				--fcount;
				tcount->surPlusB = fcount->surPlusB + tcount->inComingB - tcount->expenseB;
				++fcount;

				itter = tcount - bufer.begin();
				break;
			}
		}
		//если нет, то создаем и записываем данные
		if (currentIndex == itter) {
			dateBufer item;
			item.date = currentDate;
			item.inComingB = 0.0;
			item.expenseB = 0.0;
			item.surPlusB = bufer[currentIndex].surPlusB;

			bufer.append(item);
			itter = bufer.size() - 1;
		}
	}
}

QString DBFasade::addStringDay(QString date_)
{
	QDate date = QDate::fromString(date_, "dd.MM.yyyy");
	date = date.addDays(1);
	return date.toString("dd.MM.yyyy");
}

QString DBFasade::minusStringDay(QString date_)
{
	QDate date = QDate::fromString(date_, "dd.MM.yyyy");
	date = date.addDays(-1);
	return date.toString("dd.MM.yyyy");
}

void DBFasade::clearBufer() { bufer.clear(); }