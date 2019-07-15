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
	void fillDayWidgetFromBufer(DayWidget &day);
	void calculateChanges(QString date_, double inComing_, double expense_, double surPlus_);
	void clearBufer();

protected:
	void fillBufer(double inComing_, double expense_, double surPlus_, QString date_);
	QString addStringDay(QString date_);

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
	static int calcTime;
};
#endif // !DBFASADE_H
