#ifndef DBFASADE_H
#define DBFASADE_H

#include <QtSql>

class QSqlDatabase;
class QSqlQuery;
class QSqlRecord;
class DayWidget;
class EditForm;

class DBFasade
{
public:
	DBFasade();
	~DBFasade();
	bool authRequest(QString login, QString pass);
	bool createUser(QString login, QString pass);
	bool isCreated(QString login);
	void fillDayWidget(QDate date_, DayWidget &day);
	void updateDayWidgetData(QDate date_, double inComing_, double expense_, double surPlus_);
	void getCurrentDateData(QDate date_, EditForm &form);
	//void pushUserData();
	double getYesterdaySurplus(QDate date_);
	
protected:
	void insertThisWidget(QDate date_, double inComing_, double expense_, double surPlus_);
	//double getYesterdaySurplus(QDate date_);
	void updateDataBase(QDate date_, double surPlus_);

	QSqlDatabase _sdb;
	QSqlQuery *_query;

	QString _authLogin;
	static int _authId;
};
#endif // !DBFASADE_H
