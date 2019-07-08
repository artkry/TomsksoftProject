#ifndef DBFASADE_H
#define DBFASADE_H

#include <QtSql>

class QSqlDatabase;
class QSqlQuery;
class QSqlRecord;

class DBFasade
{

public:
	DBFasade();
	~DBFasade();
	bool authRequest(QString login, QString pass);
	bool createUser(QString login, QString pass);
	bool isCreated(QString login);
	void pullUserData();
	void pushUserData();

protected:

	QSqlDatabase sdb;
	QSqlQuery *query;
	QSqlRecord rec;
};
#endif // !DBFASADE_H
