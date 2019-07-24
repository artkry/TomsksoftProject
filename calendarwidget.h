#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QDialog>
#include <QDate>

class QVBoxLayout;

class CalendarWidget : public QDialog
{
	Q_OBJECT
public:
	CalendarWidget(QDate date_, QDialog *parent = 0);
	~CalendarWidget();

	//QDate getCurrentDate();

private:
	void createCalendar(QDate date_);

	//QDate _selectedDate;
	QVBoxLayout *_mainLayout;
};
#endif // !CALENDARWIDGET_H
