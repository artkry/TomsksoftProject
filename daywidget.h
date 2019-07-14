#ifndef DAYWIDGET_H
#define DAYWIDGET_H

#include <QWidget>
//#include <QDate>

class QGroupBox;
class DBFasade;
class QVBoxLayout;

class DayWidget : public QWidget
{
	Q_OBJECT
public:
	DayWidget(QString date_, double inComing_, double expense_, double surPlus_);
	~DayWidget();

	QString getDate() const;
	void setInComing(double inComing_);
	void setExpense(double expense_);
	void setSurPlus(double surPlus_);
	double getInComing() const;
	double getExpense() const;
	double getSurPlus() const;

signals:
	void clicked(QString date_);

protected:
	void mousePressEvent(QMouseEvent *event);
	void createFormGroupBox();

	void setDate(QString date_);

	QString date;
	double inComing;
	double expense;
	double surPlus;

	QGroupBox *formGroupBox;
	QVBoxLayout *mainLayout;
};
#endif // !DAYWIDGET_H
