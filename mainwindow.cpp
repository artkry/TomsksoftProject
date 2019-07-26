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
#include <QPainter>

MainWindow::MainWindow() 
{
	this->setGeometry(300, 100, 700, 500);

	_selectedDate = QDate::currentDate();
	
	_mainLayout = new QVBoxLayout(this);
	createMenu();
	createMonthMenu();
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

void MainWindow::createMonthMenu() 
{
	QHBoxLayout *layout = new QHBoxLayout;
	_currentDateLabel = new QLabel(_selectedDate.toString("MMMM yyyy"));
	_currentDateLabel->setAlignment(Qt::AlignCenter);

	QPixmap l_Icon(":ArrowLeft.png");
	QPixmap r_Icon(":ArrowRight.png");

	QPushButton *nextMonth = new QPushButton;
	QPushButton *previosMonth = new QPushButton;
	nextMonth->setIcon(QIcon(r_Icon));
	nextMonth->setIconSize(r_Icon.size());
	nextMonth->setFixedSize(85, 50);
	previosMonth->setIcon(QIcon(l_Icon));
	previosMonth->setIconSize(l_Icon.size());
	previosMonth->setFixedSize(85, 50);

	connect(nextMonth, SIGNAL(clicked()), this, SLOT(addMonth()));
	connect(previosMonth, SIGNAL(clicked()), this, SLOT(subMonth()));

	layout->addWidget(previosMonth);
	layout->addStretch();
	layout->addWidget(_currentDateLabel, Qt::AlignCenter);
	layout->addStretch();
	layout->addWidget(nextMonth);

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

void MainWindow::addMonth() 
{
	_selectedDate = _selectedDate.addMonths(1);
	_currentDateLabel->setText(_selectedDate.toString("MMMM yyyy"));
	reRenderCalendar();
}

void MainWindow::subMonth() 
{
	_selectedDate = _selectedDate.addMonths(-1);
	_currentDateLabel->setText(_selectedDate.toString("MMMM yyyy"));
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