#include "dbfasade.h"


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
	delete &rec;
	sdb.close();
	sdb.removeDatabase(sdb.connectionName());
}


bool DBFasade::authRequest(QString login, QString pass)
{
	query->clear();

	bool isCorrect;
	QString str_ = "SELECT passwd FROM Users WHERE Users.profile_name LIKE '%1';";
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
		return true;
		authLogin = login;
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

void DBFasade::pullUserData() 
{}

void DBFasade::pushUserData() 
{}