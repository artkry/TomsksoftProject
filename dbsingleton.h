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

	bool authRequest(QString login, QString pass);
	bool createUser(QString login, QString pass);
	void fillDayWidget(QDate date_, double &inComing_, double &expense_, double &surPlus_);
	void updateDayWidgetData(QDate date_, double inComing_, double expense_, double surPlus_);
	void getCurrentDateData(QDate date_, double &inComing_, double &expense_, double &surPlus_);
	double getYesterdaySurplus(QDate date_);

	void setAuthId(int id);
	int getAuthId() const;

	void setAuthLogin(QString login);
	QString getAuthLogin() const;

protected:
	DBSingleton();
	~DBSingleton() {};
	DBSingleton(const DBSingleton&);
	DBSingleton &operator=(DBSingleton&);
	friend class DBSingletonDestroyer;

	void insertThisWidget(QDate date_, double inComing_, double expense_, double surPlus_);
	void updateDataBase(QDate date_, double surPlus_);
	bool isCreated(QString login);
private:
	static DBSingleton *_instance;
	static DBSingletonDestroyer _destroyer;

	QSqlDatabase _sdb;

	int _authId;
	QString _authLogin;
};

#define DATABASE DBSingleton::getInstance()
#endif // !DBSINGLETON_H

