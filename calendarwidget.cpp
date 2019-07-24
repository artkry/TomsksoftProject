#include "calendarwidget.h"
#include "daywidget.h"
#include "dbsingleton.h"

#include <QDate>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>

CalendarWidget::CalendarWidget(QDate date_, QDialog *parent) : QDialog(parent)
{
	//_selectedDate = QDate::currentDate();

	_mainLayout = new QVBoxLayout;
	createCalendar(date_);
	setLayout(_mainLayout);
}

CalendarWidget::~CalendarWidget() {}

void CalendarWidget::createCalendar(QDate date_) 
{
	//QDate date(_selectedDate.year(), _selectedDate.month(), 1);
	QDate date(date_.year(), date_.month(), 1);
	DATABASE.fillThisMonth(date);

	QGridLayout *calendarLayout = new QGridLayout;
	calendarLayout->setVerticalSpacing(0);
	calendarLayout->setHorizontalSpacing(0);
	calendarLayout->setSizeConstraint(QLayout::SetFixedSize);

	for (int weekDay = 0; weekDay < 7; ++weekDay) {
		QLabel *weekDayName = new QLabel(QString("%1").arg(QDate::longDayName(weekDay + 1)));
		calendarLayout->addWidget(weekDayName, 0, weekDay + 1, Qt::AlignCenter);
	}

	int weekNum = 1;
	while (date.month() == date_.month()) {
		int weekDay = date.dayOfWeek();
		DayWidget *day = new DayWidget(date);

		connect(day, SIGNAL(clicked(QDate)), this, SLOT(makeChanges(QDate)));

		calendarLayout->addWidget(day, weekNum, weekDay);
		calendarLayout->setRowStretch(weekNum, 1);

		date = date.addDays(1);
		if (weekDay == 7 && date.month() == date_.month()) { weekNum++; }
	}
	_mainLayout->addLayout(calendarLayout);
}

