#include "dbfasade.h"
#include "daywidget.h"

int DBFasade::authId = 0;

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
	int itter = 0;
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
		qDebug() << itter;
		qDebug() << dtimeQ;
		qDebug() << incomingQ;
		qDebug() << expenseQ;
		qDebug() << surplusQ;

		fillBufer(incomingQ, expenseQ, surplusQ, dtimeQ, itter);
		
		itter++;
	}

	return true;
}

bool DBFasade::pushUserData(double inComing_, double expense_, double surPlus_, QString date_)
{
	query->clear();

	bool isCorrect;
	QString str_ = "UPDATE UsersData SET incoming = '%1' expense = '%2' surplus = '%3' "
		"WHERE UsersData.uid = '%4' AND UsersData.dtime = '%5';";
	QString str = str_.arg(inComing_).arg(expense_).arg(surPlus_).arg(authId).arg(date_);
	
	isCorrect = query->exec(str);

	if(!isCorrect){
		qDebug() << "pushRequest failed (DBFasade query)";
		return false;
	}
	else {
		qDebug() << "pushRequest ok (DBFasade query)";
		return true;
	}

}

void DBFasade::fillBufer(double inComing_, double expense_, double surPlus_, QString date_, int itter)
{
	dateBufer item;
	bufer.append(item);

	bufer[itter].date = date_;
	bufer[itter].inComingB = inComing_;
	bufer[itter].expenseB = expense_;
	bufer[itter].surPlusB = surPlus_;

	qDebug() << "№: " << itter
		<< "date: " << bufer[itter].date
		<< "inc: " << bufer[itter].inComingB
		<< "exp: " << bufer[itter].expenseB
		<< "sur: " << bufer[itter].surPlusB;
}

DayWidget DBFasade::fillDayWidgetFromBufer(DayWidget &day)
{
	QList<dateBufer>::iterator count;

	QString dayDate = day.getDate();
	
	qDebug() << "enter func";
	for (count = bufer.begin(); count != bufer.end(); ++count) {
		if (count->date == dayDate) {
			qDebug() << "enter if";
			day.setInComing(count->inComingB);
			day.setExpense(count->expenseB);
			day.setSurPlus(count->surPlusB);
			break;
		}
	}
	qDebug() << "close func";
}