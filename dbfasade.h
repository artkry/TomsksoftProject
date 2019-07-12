#ifndef DBFASADE_H
#define DBFASADE_H

#include <QtSql>

class QSqlDatabase;
class QSqlQuery;
class QSqlRecord;
class DayWidget;

class DBFasade
{

public:
	DBFasade();
	~DBFasade();
	bool authRequest(QString login, QString pass);
	bool createUser(QString login, QString pass);
	bool isCreated(QString login);
	bool pullUserData();
	bool pushUserData(double inComing_, double expense_, double surPlus_, QString date_);
	DayWidget fillDayWidgetFromBufer(DayWidget &day);

protected:
	void fillBufer(double inComing_, double expense_, double surPlus_, QString date_, int itter);

	struct dateBufer
	{
		QString date;
		double inComingB;
		double expenseB;
		double surPlusB;
	};

	QList <dateBufer> bufer;
	QSqlDatabase sdb;
	QSqlQuery *query;
	QSqlRecord rec;

	QString authLogin;
	static int authId;
};
#endif // !DBFASADE_H
