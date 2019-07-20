#include "dbfasade.h"

int DBFasade::_authId = 0;
QSqlDatabase DBFasade::_sdb = QSqlDatabase::addDatabase("QSQLITE");

DBFasade::DBFasade()
{
	_sdb.setDatabaseName("database.db");

	if (!_sdb.open()) {
		qDebug() << "Can't open DataBase (DBFasade constructor error)";
	}

	_query = new QSqlQuery(_sdb);

	if (!_sdb.tables().contains("Users")) {
		_query->exec("CREATE TABLE Users ("
			"id INTEGER PRIMARY KEY AUTOINCREMENT, "
			"profile_name TEXT NOT NULL UNIQUE, "
			"passwd TEXT NOT NULL"
			");"
		);
	}

	if (!_sdb.tables().contains("UsersData")) {
		_query->exec("CREATE TABLE UsersData ("
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
	delete _query;
}

bool DBFasade::authRequest(QString login, QString pass)
{
	_query->clear();

	bool isCorrect;
	QString str_ = "SELECT passwd, id FROM Users WHERE Users.profile_name LIKE '%1';";
	QString str = str_.arg(login);
	isCorrect = _query->exec(str);

	if (!isCorrect) {
		qDebug() << "authRequest failed (DBFasade query)";
		return false;
	}
	else {
		qDebug() << "authRequest success (DBFasade query)";
	}

	QSqlRecord rec = _query->record();
	_query->first();

	if (_query->value(rec.indexOf("passwd")).toString() == pass) {
		_authLogin = login;
		_authId = _query->value(rec.indexOf("id")).toInt();
		//qDebug() << authLogin;
		//qDebug() << "authidrequest:" << _authId;
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
		_query->clear();
		bool isCorrect;
		QString str_ = "INSERT INTO Users (profile_name, passwd) VALUES ('%1','%2');";
		QString str = str_.arg(login).arg(pass);

		isCorrect = _query->exec(str);

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
	_query->clear();

	bool isCorrect;
	QString str_ = "SELECT id FROM Users WHERE Users.profile_name = '%1';";
	QString str = str_.arg(login);
	isCorrect = _query->exec(str);

	QSqlRecord rec = _query->record();
	_query->first();

	if (_query->value(rec.indexOf("id")).toInt() != 0) {
		qDebug() << "This profile name is already exists! Try again.";
		return false;
	}
	else {
		qDebug() << "All right.";
		return true;
	}
}

void DBFasade::fillDayWidget(QDate date_, double &inComing_, double &expense_, double &surPlus_) 
{
	//QSqlQuery *query = new QSqlQuery(_sdb);
	_query->clear();

	double yesterdaySurplus = getYesterdaySurplus(date_);

	QString str = "SELECT incoming, expense FROM UsersData WHERE UsersData.dtime = '%1' AND UsersData.uid = %2;";
	QString str_ = str.arg(date_.toString("yyyy.MM.dd")).arg(_authId);

	bool isCorrect = _query->exec(str_);

	if (!isCorrect) {
		qDebug() << "fill query not ok dbfasade";
	}
	else {
		qDebug() << "fill query ok dbfasade";
	}

	QSqlRecord rec = _query->record();
	_query->isActive();
	_query->isSelect();

	if (!_query->first()) {
		inComing_ = 0.0;
		expense_ = 0.0;
		surPlus_ = yesterdaySurplus;
		insertThisWidget(date_, 0.0, 0.0, yesterdaySurplus);
	}
	else {
		inComing_ = _query->value(rec.indexOf("incoming")).toDouble();
		expense_ = _query->value(rec.indexOf("expense")).toDouble();
		surPlus_ = yesterdaySurplus + inComing_ - expense_;
	}
}

double DBFasade::getYesterdaySurplus(QDate date_)
{
	//QSqlQuery *query = new QSqlQuery(_sdb);
	_query->clear();

	QDate yesterdayDate = date_.addDays(-1);
	double yesterdaySurplus = 0.0;

	QString str = "SELECT surplus FROM UsersData WHERE UsersData.dtime = '%1' AND UsersData.uid = %2;";
	QString str_ = str.arg(yesterdayDate.toString("yyyy.MM.dd")).arg(_authId);

	bool isCorrect = _query->exec(str_);

	if (!isCorrect) {
		qDebug() << "yesterdaydate isn't correct dbfasade";
		//return -1;
	}
	else {
		qDebug() << "yesterdaydate is correct dbfasade";
	}

	QSqlRecord rec = _query->record();

	if (!_query->first()) {
		return yesterdaySurplus;
	}
	else {
		return yesterdaySurplus = _query->value(rec.indexOf("surplus")).toDouble();
	}
}

void DBFasade::updateDayWidgetData(QDate date_, double inComing_, double expense_, double surPlus_) 
{
	double yesterdaySurplus = getYesterdaySurplus(date_);

	//QSqlQuery *query = new QSqlQuery(_sdb);
	_query->clear();

	QString str = "UPDATE UsersData "
		"SET incoming = %1, "
		"expense = %2, "
		"surplus = %3 "
		"WHERE UsersData.uid = %4 AND UsersData.dtime = '%5';";

	double todaySurplus;
	QString str_;
	if (surPlus_ == 0.0) {
		todaySurplus = yesterdaySurplus + inComing_ - expense_;
		str_ = str.arg(inComing_).arg(expense_).arg(todaySurplus).arg(_authId).arg(date_.toString("yyyy.MM.dd"));
	}
	else {
		//todaySurplus = surPlus_;
		todaySurplus = yesterdaySurplus + inComing_ - expense_;
		double trueSurplus = yesterdaySurplus + inComing_ - expense_;

		if (todaySurplus != trueSurplus) {
			//как то обозначить
		}

		str_ = str.arg(inComing_).arg(expense_).arg(todaySurplus).arg(_authId).arg(date_.toString("yyyy.MM.dd"));
	}

	bool isCorrect = _query->exec(str_);

	if (!isCorrect) {
		qDebug() << "non correct update dbfasasde";
	}
	else {
		qDebug() << "correct update dbfasasde";
	}

	updateDataBase(date_, todaySurplus);
}

void DBFasade::updateDataBase(QDate date_, double surPlus_)
{
	double surplus = surPlus_;
	QDate currentDate = date_;
	QSqlQuery *query = new QSqlQuery(_sdb);
	QString str = "SELECT incoming, expense FROM UsersData WHERE UsersData.uid = %1 AND UsersData.dtime = '%2';";
	QString strUpdate = "UPDATE UsersData "
		"SET surplus = %1 "
		"WHERE UsersData.uid = %2 AND UsersData.dtime = '%3';";

	while (true) {
		currentDate = currentDate.addDays(1);
		QString str_ = str.arg(_authId).arg(currentDate.toString("yyyy.MM.dd"));
		query->exec(str_);
		QSqlRecord rec = query->record();
		query->isActive();
		query->isSelect();
		if (!query->first()) {
			break;
		}
		else {
			double incomingDB = query->value(rec.indexOf("incoming")).toDouble();
			double expenseDB = query->value(rec.indexOf("expense")).toDouble();
			surplus += incomingDB - expenseDB;
			double result = surplus;
			
			QString strUpdate_ = strUpdate.arg(result).arg(_authId).arg(currentDate.toString("yyyy.MM.dd"));
			query->exec(strUpdate_);
		}	
	}
}

void DBFasade::insertThisWidget(QDate date_, double inComing_, double expense_, double surPlus_) 
{
	//QSqlQuery *query = new QSqlQuery(_sdb);
	_query->clear();
	QString str = "INSERT INTO UsersData (uid, dtime, incoming, expense, surplus)"
		"VALUES(%1, '%2', %3, %4, %5)";
	QString str_ = str.arg(_authId).arg(date_.toString("yyyy.MM.dd")).arg(inComing_).arg(expense_).arg(surPlus_);

	bool isCorrect = _query->exec(str_);

	if (!isCorrect) {
		qDebug() << "query non correct insertDW";
	}
	else {
		qDebug() << "query correct insertDW";
	}
}

void DBFasade::getCurrentDateData(QDate date_, double &inComing_, double &expense_, double &surPlus_) 
{
	//QSqlQuery *query = new QSqlQuery(_sdb);
	_query->clear();
	QString str = "SELECT incoming, expense, surplus FROM UsersData WHERE UsersData.dtime = '%1' AND UsersData.uid = %2;";
	QString str_ = str.arg(date_.toString("yyyy.MM.dd")).arg(_authId);

	bool isCorrect = _query->exec(str_);

	QSqlRecord rec = _query->record();
	_query->first();

	inComing_ = _query->value(rec.indexOf("incoming")).toDouble();
	expense_ = _query->value(rec.indexOf("expense")).toDouble();
	surPlus_ = _query->value(rec.indexOf("surplus")).toDouble();
}