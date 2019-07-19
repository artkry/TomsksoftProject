#include "mainwindow.h"
#include "dbfasade.h"
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

	_sdb = new DBFasade;

	_selectedDate = QDate::currentDate();
	
	_mainLayout = new QVBoxLayout;
	createMenu();
	createHorizontalLayout();
	createCalendarGroupBox();
	_mainLayout->addWidget(_calendarGroupBox, 1, Qt::AlignCenter);
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

	connect(monthEdit, SIGNAL(dateChanged(QDate)), this, SLOT(changeMonth(QDate)));

	layout->addWidget(monthEdit);

	_mainLayout->addLayout(layout);
}

void MainWindow::createCalendarGroupBox()
{
	QDate date(_selectedDate.year(), _selectedDate.month(), 1);

	_calendarGroupBox = new QGroupBox;
	QGridLayout *calendarLayout = new QGridLayout;
	calendarLayout->setVerticalSpacing(0);
	calendarLayout->setHorizontalSpacing(0);

	for (int weekDay = 0; weekDay < 7; ++weekDay) {
		QLabel *weekDayName = new QLabel(QString("%1").arg(QDate::longDayName(weekDay + 1)));
		calendarLayout->addWidget(weekDayName, 0, weekDay + 1);
	}

	int weekNum = 1;
	while (date.month() == _selectedDate.month()) {
		int weekDay = date.dayOfWeek();
		DayWidget *day = new DayWidget(date);

		connect(day, SIGNAL(clicked(QDate)), this, SLOT(makeChanges(QDate)));
		calendarLayout->addWidget(day, weekNum, weekDay);
		date = date.addDays(1);
		if (weekDay == 7 && date.month() == _selectedDate.month()) { weekNum++; }
	}

	_calendarGroupBox->setLayout(calendarLayout);
}

void MainWindow::changeMonth(QDate date_)
{
	_selectedDate = QDate(date_.year(), date_.month(), _selectedDate.day());
	reRenderCalendar();
}

void MainWindow::reRenderCalendar()
{
	QLayoutItem *item;
	item = _mainLayout->itemAt(1);
	_mainLayout->removeItem(item);
	_mainLayout->removeWidget(item->widget());
	delete item->widget();
	delete item;

	createCalendarGroupBox();

	_mainLayout->insertWidget(1, _calendarGroupBox);
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
		_sdb->updateDayWidgetData(date_, editform.getInComing(),
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