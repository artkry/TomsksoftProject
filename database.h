#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>


class Database
{
public:
	static QSqlDatabase sdb;
	Database();
	void initDataBase();
};
#endif // !DATABASE_H
