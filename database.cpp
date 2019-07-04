#include "database.h"

#include <QSqlQuery>

QSqlDatabase Database::sdb;

Database::Database()
{
	sdb = QSqlDatabase::addDatabase("QSQLITE", "Connect");
	sdb.setDatabaseName("database.db");
	sdb.open();

	if (!sdb.open()) {
		qDebug() << sdb.lastError().text();
	}
	else {
		qDebug() << "DB connect Success!";
	}

	initDataBase();
}

void Database::initDataBase()
{

	QSqlQuery a_query(sdb);
	QString str;
	bool isCorrect = false;

	//Создаем таблицу Users
	str = "CREATE TABLE IF NOT EXISTS Users ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"profile_name TEXT NOT NULL UNIQUE, "
		"passwd TEXT NOT NULL"
		");";

	isCorrect = a_query.exec(str);
	if (!isCorrect) {
		qDebug() << "Error: Table 'Users' wasn't created!";
	}
	else {
		qDebug() << "Success: Table 'Users' was created!";
	}

	//Создаем таблицу UsersData
	str = "CREATE TABLE IF NOT EXISTS UsersData ("
		"uid INTEGER, "
		"dtime TEXT NOT NULL, "
		"incoming REAL DEFAULT 0, "
		"expense REAL DEFAULT 0, "
		"surplus REAL, "
		"FOREIGN KEY (uid) REFERENCES Users(id) "
		");";

	isCorrect = a_query.exec(str);
	if (!isCorrect) {
		qDebug() << "Error: Table 'UsersData' wasn't created!";
	}
	else {
		qDebug() << "Success: Table 'UsersData' was created!";
	}

}

//void Database::isCreateDataBase()
//{
	//QFile fout("database.db");
	//if (!fout.exists()) {
		//initDataBase();
		//qDebug() << "Create Database cuz of it's not exists";
	//}
//}