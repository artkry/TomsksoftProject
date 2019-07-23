#ifndef DBSINGLETON_H
#define DBSINGLETON_H

#include <QtSql>

class QSqlDatabase;
class DBSingleton;

class DBSingletonDestroyer
{
public:
	~DBSingletonDestroyer();
	void init(DBSingleton *db);
private:
	DBSingleton *_instance;
};

class DBSingleton
{
public:
	static DBSingleton &getInstance();
	//функции системы логин
	bool authRequest(QString login, QString pass);
	bool createUser(QString login, QString pass);
	//функции, связанные с расчетами и заполнением
	void fillThisMonth(QDate date_);
	void fillWidget(QDate date_, double &inComing_, double &expense_, double &surPlus_);
	void updateThisMonth(QDate date_, double inComing_, double expense_, double surPlus_);
	//функции для editform
	double getYesterdaySurplusFromBufer(QDate date_);
	void getCurrentDateData(QDate date_, double &inComing_, double &expense_, double &surPlus_);

protected:
	DBSingleton();
	~DBSingleton() {};
	DBSingleton(const DBSingleton&);
	DBSingleton &operator=(DBSingleton&);
	friend class DBSingletonDestroyer;

	//второстепенные функции для расчетов и регистрации
	bool isCreated(QString login);
	double getPreviosMonthSurplus(QDate date_);
	void setCurrentMonthSurPlus(QDate date_, double surPlus_);

private:
	static DBSingleton *_instance;
	static DBSingletonDestroyer _destroyer;

	struct dayStruct
	{
		QString s_dtime;
		double s_incoming;
		double s_expense;
		double s_surplus;
	};

	struct monthStruct
	{
		int s_year;
		int s_month;
		double s_monthSurplus;
	};

	QList <dayStruct> monthBufer;
	QList <monthStruct> surplusBufer;

	QSqlDatabase _sdb;

	int _authId;
};

#define DATABASE DBSingleton::getInstance()
#endif // !DBSINGLETON_H

