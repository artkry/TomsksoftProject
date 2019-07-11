#ifndef DAYWIDGET_H
#define DAYWIDGET_H

#include <QWidget>
#include <QDate>

//class QLabel;
class QGroupBox;

class DayWidget : public QWidget
{
	Q_OBJECT
public:
	DayWidget(QDate date_, double inComing_, double expense_, double surPlus_);
	~DayWidget();

signals:
	void clicked();

protected:
	void mousePressEvent(QMouseEvent *event);
	void createFormGroupBox();

	void setDate(QDate date_);
	void setInComing(double inComing_ = 0.0);
	void setExpense(double expense_ = 0.0);
	void setSurPlus(double surPlus_ = 0.0);
	
	QDate getDate() const;
	double getInComing() const;
	double getExpense() const;
	double getSurPlus() const;

	QDate date;

    double inComing;
	double expense;
	double surPlus;

	QGroupBox *formGroupBox;
};
#endif // !DAYWIDGET_H
