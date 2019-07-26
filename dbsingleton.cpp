#include "dbsingleton.h"

#include <QSqlDatabase>

DBSingleton *DBSingleton::_instance = 0;
DBSingletonDestroyer DBSingleton::_destroyer;

DBSingletonDestroyer::~DBSingletonDestroyer() { delete _instance; }

void DBSingletonDestroyer::init(DBSingleton *db) { _instance = db; }

DBSingleton &DBSingleton::getInstance()
{
	if (!_instance) {
		_instance = new DBSingleton();
		_destroyer.init(_instance);
	}
	return *_instance;
}

DBSingleton::DBSingleton() 
{
	_sdb = QSqlDatabase::addDatabase("QSQLITE");
	_sdb.setDatabaseName("database.db");

	if (!_sdb.open()) {
		qDebug() << "Can't open DataBase (DBFasade constructor error)";
	}

	QSqlQuery query;

	if (!_sdb.tables().contains("Users")) {
		query.exec("CREATE TABLE Users ("
			"id INTEGER PRIMARY KEY AUTOINCREMENT, "
			"profile_name TEXT NOT NULL UNIQUE, "
			"passwd TEXT NOT NULL"
			");"
		);
	}

	if (!_sdb.tables().contains("UsersData")) {
		query.exec("CREATE TABLE UsersData ("
			"uid INTEGER, "
			"dtime TEXT NOT NULL, "
			"incoming REAL DEFAULT 0, "
			"expense REAL DEFAULT 0, "
			"surplus REAL, "
			"FOREIGN KEY (uid) REFERENCES Users(id)"
			"PRIMARY KEY (uid, dtime)"
			");"
		);
	}
}

bool DBSingleton::authRequest(QString login, QString pass) 
{
	QSqlQuery query;
	bool isCorrect;

	QString str_ = "SELECT passwd, id FROM Users WHERE Users.profile_name LIKE '%1';";
	QString str = str_.arg(login);

	isCorrect = query.exec(str);
	if (!isCorrect) {
		qDebug() << "authRequest failed (DBFasade query)";
		return false;
	}
	else {
		qDebug() << "authRequest success (DBFasade query)";
	}

	QSqlRecord rec = query.record();
	query.first();

	if (query.value(rec.indexOf("passwd")).toString() == pass) {
		_authId = query.value(rec.indexOf("id")).toInt();
		return true;
	}
	else {
		qDebug() << "Incorrect pass! (DBFasade authRequest)";
		return false;
	}
}

bool DBSingleton::createUser(QString login, QString pass) 
{
	QSqlQuery query;

	if (isCreated(login)) {
		bool isCorrect;
		QString str_ = "INSERT INTO Users (profile_name, passwd) VALUES ('%1','%2');";
		QString str = str_.arg(login).arg(pass);

		isCorrect = query.exec(str);

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

bool DBSingleton::isCreated(QString login) 
{
	QSqlQuery query;
	bool isCorrect;

	QString str_ = "SELECT id FROM Users WHERE Users.profile_name = '%1';";
	QString str = str_.arg(login);
	isCorrect = query.exec(str);

	QSqlRecord rec = query.record();
	query.first();

	if (query.value(rec.indexOf("id")).toInt() != 0) {
		qDebug() << "This profile name is already exists! Try again.";
		return false;
	}
	else {
		qDebug() << "All right.";
		return true;
	}
}

void DBSingleton::getCurrentDateData(QDate date_, double &inComing_, double &expense_, double &surPlus_) 
{
	QList<dayStruct>::iterator count;
	for (count = monthBufer.begin(); count != monthBufer.end(); ++count) {
		if (count->s_dtime == date_.toString("yyyy.MM.dd")) {
			inComing_ = count->s_incoming;
			expense_ = count->s_expense;
			surPlus_ = count->s_surplus;
			break;
		}
	}
}

double DBSingleton::getYesterdaySurplusFromBufer(QDate date_) 
{
	QDate yesterdayDate = date_.addDays(-1);
	QList<dayStruct>::iterator count;

	for (count = monthBufer.begin(); count != monthBufer.end(); ++count) {
		if (count->s_dtime == yesterdayDate.toString("yyyy.MM.dd")) {
			return count->s_surplus;
			break;
		}
	}
}

void DBSingleton::fillThisMonth(QDate date_) 
{
	monthBufer.clear();

	QString str = "SELECT dtime, incoming, expense, surplus FROM UsersData WHERE UsersData.uid = %1 AND UsersData.dtime LIKE '%2';";
	QString str_ = str.arg(_authId).arg(date_.toString("yyyy.MM") + "%");

	QSqlQuery query;
	query.exec(str_);

	QSqlRecord rec = query.record();

	double previosMonthSurplus = getPreviosMonthSurplus(date_);
	qDebug() << "prev monthsurplus" << previosMonthSurplus;

	if (!query.first()) {
		int monthCount = date_.daysInMonth();
		QDate dtime = date_;
		qDebug() << "takogo dnya net";
		for (int i = 0; i < monthCount; i++) {
			dayStruct day;
			day.s_dtime = dtime.toString("yyyy.MM.dd");
			day.s_incoming = 0.0;
			day.s_expense = 0.0;
			day.s_surplus = previosMonthSurplus;

			monthBufer.append(day);
			dtime = dtime.addDays(1);
		}

	}
	else {
		query.previous();
		while (query.next()) {
			dayStruct day;
			day.s_dtime = query.value(rec.indexOf("dtime")).toString();
			day.s_incoming = query.value(rec.indexOf("incoming")).toDouble();
			day.s_expense = query.value(rec.indexOf("expense")).toDouble();
			previosMonthSurplus += day.s_incoming - day.s_expense;
			day.s_surplus = previosMonthSurplus;
			
			monthBufer.append(day);
			qDebug() << "takoi den est" << day.s_dtime;
		}

	}
	qDebug() << "ostatok mesyaca: " << previosMonthSurplus;
	setCurrentMonthSurPlus(date_, previosMonthSurplus);
}

void DBSingleton::fillWidget(QDate date_, double &inComing_, double &expense_, double &surPlus_) 
{
	QList<dayStruct>::iterator count;

	for (count = monthBufer.begin(); count != monthBufer.end(); ++count) {
		if (count->s_dtime == date_.toString("yyyy.MM.dd")) {
			inComing_ = count->s_incoming;
			expense_ = count->s_expense;
			surPlus_ = count->s_surplus;
			qDebug() << "fill widget for " << count->s_dtime << "  date";
			break;
		}
	}
}

void DBSingleton::updateThisMonth(QDate date_, double inComing_, double expense_, double surPlus_)
{
	QList <dayStruct>::iterator countF;
	QList <dayStruct>::iterator countS;

	double yesterdaySurplus = getYesterdaySurplusFromBufer(date_);

	qDebug() << "prev day ost: " << yesterdaySurplus;
	for (countF = monthBufer.begin(); countF != monthBufer.end(); ++countF) {
		if (countF->s_dtime == date_.toString("yyyy.MM.dd")) {
			countF->s_incoming = inComing_;
			countF->s_expense = expense_;
			countF->s_surplus = yesterdaySurplus + inComing_ - expense_;
			yesterdaySurplus = countF->s_surplus;
			qDebug() << countF->s_dtime <<" day ost: " << yesterdaySurplus;
			break;
		}
	}

	for (countS = ++countF; countS != monthBufer.end(); ++countS) {
		countS->s_surplus = yesterdaySurplus + countS->s_incoming - countS->s_expense;
		yesterdaySurplus = countS->s_surplus;
	}
    

	QString str = "REPLACE INTO UsersData(uid, dtime, incoming, expense, surplus)"
		"VALUES(%1, '%2', %3, %4, %5)";
	QList <dayStruct>::iterator countT;

	QSqlQuery query;
	//query.exec() выполняется в среднем 100-120мс из-за за этого пролагивает при обновлении
	for (countT = monthBufer.begin(); countT != monthBufer.end(); ++countT) {
		QString str_ = str.arg(_authId).arg(countT->s_dtime).arg(countT->s_incoming).arg(countT->s_expense).arg(countT->s_surplus);
		query.exec(str_);
		query.clear();
	}
}

double DBSingleton::getPreviosMonthSurplus(QDate date_)  
{
	QDate prevMonthDate = date_.addMonths(-1);
	qDebug() << "GPMS: " << prevMonthDate;
	double previosMonthSurplus = 0.0;
	if (surplusBufer.isEmpty()) {
		return previosMonthSurplus;
	}
	else {
		QList<monthStruct>::iterator count;
		for (count = surplusBufer.begin(); count != surplusBufer.end(); ++count) {
			if (count->s_month == prevMonthDate.month() && count->s_year == prevMonthDate.year()) {
				previosMonthSurplus = count->s_monthSurplus;
				break;
			}
		}
	}

	return previosMonthSurplus;
}

void DBSingleton::setCurrentMonthSurPlus(QDate date_, double surPlus_) 
{
	monthStruct item;
	
	item.s_year = date_.year();
	item.s_month = date_.month();
	item.s_monthSurplus = surPlus_;

	surplusBufer.append(item);

	if (surplusBufer.isEmpty()) 
	{
		monthStruct item;

		item.s_year = date_.year();
		item.s_month = date_.month();
		item.s_monthSurplus = surPlus_;

		surplusBufer.append(item);
	}
	else {
		QList <monthStruct>::iterator count;
		for (count = surplusBufer.begin(); count != surplusBufer.end(); ++count) {
			if (count->s_month == date_.month() && count->s_year == date_.year()) {
				count->s_monthSurplus = surPlus_;
				break;
			}
		}
	}
}

