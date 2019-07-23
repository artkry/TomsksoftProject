#include "mainwindow.h"
#include "dbsingleton.h"
#include "editform.h"
#include "daywidget.h"
#include "aboutwindow.h"
#include "instructionwindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDateTimeEdit>
#include <QDate>
#include <QGroupBox>

MainWindow::MainWindow() 
{
	this->setGeometry(300, 100, 700, 500);

	_selectedDate = QDate::currentDate();
	
	_mainLayout = new QVBoxLayout(this);
	createMenu();
	createHorizontalLayout();
	createCalendarGroupBox();
	_mainLayout->addLayout(_calendarLayout);
	setLayout(_mainLayout);

	setWindowTitle("Home Accounting");
}

MainWindow::~MainWindow() {}

void MainWindow::createMenu() 
{
	QMenuBar *menuBar = new QMenuBar;
	QMenu *fileMenu = new QMenu(tr("&Menu"), this);

	QAction *instructionAction = fileMenu->addAction(tr("&Instruction"));
	QAction *aboutAction = fileMenu->addAction(tr("&About"));
	QAction *exitAction = fileMenu->addAction(tr("&Exit"));

	menuBar->addMenu(fileMenu);

	connect(instructionAction, &QAction::triggered, this, &MainWindow::instructAction);
	connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutAction);
	connect(exitAction, &QAction::triggered, this, &QDialog::accept);

	_mainLayout->setMenuBar(menuBar);
}

void MainWindow::createHorizontalLayout()
{
	QHBoxLayout *layout = new QHBoxLayout;
	QDateTimeEdit *monthEdit = new QDateTimeEdit;
	monthEdit->setDisplayFormat("MMMM yyyy");
	monthEdit->setDateRange(QDate(2010, 1, 1), QDate(2030, 1, 1));
	monthEdit->setDate(_selectedDate);

	monthEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	connect(monthEdit, SIGNAL(dateChanged(QDate)), this, SLOT(changeMonth(QDate)));

	layout->addWidget(monthEdit);
	
	_mainLayout->addLayout(layout);
}

void MainWindow::createCalendarGroupBox()
{
	QDate date(_selectedDate.year(), _selectedDate.month(), 1);
	DATABASE.fillThisMonth(date);

	_calendarLayout = new QGridLayout;
	_calendarLayout->setVerticalSpacing(0);
	_calendarLayout->setHorizontalSpacing(0);
	_calendarLayout->setSizeConstraint(QLayout::SetFixedSize);

	for (int weekDay = 0; weekDay < 7; ++weekDay) {
		QLabel *weekDayName = new QLabel(QString("%1").arg(QDate::longDayName(weekDay + 1)));
		_calendarLayout->addWidget(weekDayName, 0, weekDay + 1, Qt::AlignCenter);
	}

	int weekNum = 1;
	while (date.month() == _selectedDate.month()) {
		int weekDay = date.dayOfWeek();
		DayWidget *day = new DayWidget(date);

		connect(day, SIGNAL(clicked(QDate)), this, SLOT(makeChanges(QDate)));
		
		_calendarLayout->addWidget(day, weekNum, weekDay);
		_calendarLayout->setRowStretch(weekNum, 1);
		
		date = date.addDays(1);
		if (weekDay == 7 && date.month() == _selectedDate.month()) { weekNum++; }
	}


}

void MainWindow::changeMonth(QDate date_)
{
	_selectedDate = QDate(date_.year(), date_.month(), _selectedDate.day());
	reRenderCalendar();
}

void MainWindow::reRenderCalendar()
{
	QLayoutItem *item;
	while (item = _calendarLayout->itemAt(0)) {
		_calendarLayout->removeItem(item);
		_calendarLayout->removeWidget(item->widget());
		delete item->widget();
		delete item;
	}
	delete _calendarLayout;

	createCalendarGroupBox();

	_mainLayout->insertLayout(1, _calendarLayout);
	_mainLayout->update();
}

void MainWindow::makeChanges(QDate date_)
{
	EditForm editform(date_, this);
	switch (editform.exec())
	{
	case QDialog::Rejected:
		break;
	case QDialog::Accepted:
		/*DATABASE.updateDayWidgetData(date_, editform.getInComing(),
			editform.getExpense(), editform.getSurPlus());*/
		DATABASE.updateThisMonth(date_, editform.getInComing(),
			editform.getExpense(), editform.getSurPlus());
		reRenderCalendar();
	default:
		break;
	}
}

void MainWindow::aboutAction() 
{
	AboutWindow aboutwindow(this);
	switch (aboutwindow.exec())
	{
	case QDialog::Accepted:
		break;
	default:
		break;
	}
}

void MainWindow::instructAction() 
{
	InstructionWindow inctructionwindow(this);
	switch (inctructionwindow.exec())
	{
	case QDialog::Accepted:
		break;
	default:
		break;
	}
}