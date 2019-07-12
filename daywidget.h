#ifndef DAYWIDGET_H
#define DAYWIDGET_H

#include <QWidget>
//#include <QDate>

class QGroupBox;
class DBFasade;

class DayWidget : public QWidget
{
	Q_OBJECT
public:
	DayWidget(QString date_, double inComing_, double expense_, double surPlus_);
	~DayWidget();

	QString getDate() const;
	void setInComing(double inComing_ = 0.0);
	void setExpense(double expense_ = 0.0);
	void setSurPlus(double surPlus_ = 0.0);
	double getInComing() const;
	double getExpense() const;
	double getSurPlus() const;

signals:
	void clicked();

protected:
	void mousePressEvent(QMouseEvent *event);
	void createFormGroupBox();

	void setDate(QString date_);

	QString date;
	mutable double inComing;
	mutable double expense;
	mutable double surPlus;

	QGroupBox *formGroupBox;
};
#endif // !DAYWIDGET_H
