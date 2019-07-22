#ifndef DAYWIDGET_H
#define DAYWIDGET_H

#include <QWidget>
#include <QDate>

class QVBoxLayout;

class DayWidget : public QWidget
{
	Q_OBJECT
public:
	DayWidget(QDate date_);
	~DayWidget();

	void setDate(QDate date_);
	void setInComing(double inComing_);
	void setExpense(double expense_);
	void setSurPlus(double surPlus_);
	
	QDate getDate() const;
	double getInComing() const;
	double getExpense() const;
	double getSurPlus() const;

signals:
	void clicked(QDate date);

protected:
	void mousePressEvent(QMouseEvent *event);
	void createFormLayout();

	QDate _date;
	double _inComing;
	double _expense;
	double _surPlus;

	QVBoxLayout *_mainLayout;
};
#endif // !DAYWIDGET_H
