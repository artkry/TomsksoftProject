#include "mainwindow.h"
#include "modalmainwindow.h"
#include "daywidget.h"
#include "dbfasade.h"

#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QTextBrowser>
#include <QGroupBox>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QTextTableCell>
#include <QMessageBox>

MainWindow::MainWindow()
{
	this->setGeometry(300, 100, 800, 600);
	sdb = new DBFasade;

	selectedDate = QDate::currentDate();

	createMenu();
	createHorizontalGroupBox();
	createHorizontalButtonBox();

	bool isCorrect = sdb->pullUserData();

	if (isCorrect) {
		qDebug() << "request ok (mainwdw)";
	}
	else {
		qDebug() << "bad request (mainwdw)";
	}

	calendar();
	
	windowLayout = new QVBoxLayout;
	windowLayout->setMenuBar(menuBar);
	windowLayout->addWidget(horizontalGroupBox);
	windowLayout->addWidget(calendarGridGroupBox, 1, Qt::AlignCenter);
	windowLayout->addWidget(horizontalButtonBox);
	setLayout(windowLayout);

	setWindowTitle(tr("Home Accounting"));
}

MainWindow::~MainWindow() {}

void MainWindow::createMenu()
{
	menuBar = new QMenuBar;

	fileMenu = new QMenu(tr("&Menu"), this);

	QAction *instructAction = fileMenu->addAction(tr("&Instruction"));
	QAction *aboutAction = fileMenu->addAction(tr("&About"));
	exitAction = fileMenu->addAction(tr("&Exit"));
	
	
	menuBar->addMenu(fileMenu);
	
	connect(instructAction, &QAction::triggered, this, &MainWindow::instructAction);
	connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutAction);
	connect(exitAction, &QAction::triggered, this, &QDialog::accept);
	
}

void MainWindow::createHorizontalGroupBox()
{
	horizontalGroupBox = new QGroupBox;

	QDateTimeEdit *monthEdit = new QDateTimeEdit;
	monthEdit->setDisplayFormat("MMMM yyyy");
	monthEdit->setDateRange(QDate(2010, 1, 1), QDate(2030, 1 , 1));
	monthEdit->setDate(selectedDate);

	connect(monthEdit, SIGNAL(dateChanged(QDate)), this, SLOT(changeMonth(QDate)));

	QHBoxLayout *hlayout = new QHBoxLayout;
	hlayout->addWidget(monthEdit);


	horizontalGroupBox->setLayout(hlayout);
}

void MainWindow::createHorizontalButtonBox()
{
	horizontalButtonBox = new QGroupBox;
	QHBoxLayout *layout = new QHBoxLayout;

	//название кнопок изменю позже, пока так, для наглядности
	QPushButton *pull = new QPushButton(tr("Pull Data"));
	QPushButton *push = new QPushButton(tr("Push Data"));

	connect(pull, SIGNAL(clicked()), this, SLOT(pullChanges()));
	connect(push, SIGNAL(clicked()), this, SLOT(pushChanges()));

	layout->addWidget(pull);
	layout->addSpacing(150);
	layout->addWidget(push);

	horizontalButtonBox->setLayout(layout);
}

void MainWindow::calendar()
{
	QDate date(selectedDate.year(), selectedDate.month(), 1);

	calendarGridGroupBox = new QGroupBox;
	QGridLayout *mainLayout = new QGridLayout;
	//mainLayout->setSpacing(0);
	mainLayout->setVerticalSpacing(0);
	mainLayout->setHorizontalSpacing(0);
	//дни недели
	for(int weekDay = 0; weekDay < 7; ++weekDay){
		QLabel *weekDayName = new QLabel(QString("%1").arg(QDate::longDayName(weekDay + 1)));
		mainLayout->addWidget(weekDayName, 0, weekDay);
	}

	
	//недели
	int weekNum = 1;
	while (date.month() == selectedDate.month()) {
		int weekDay = date.dayOfWeek();
		DayWidget *day = new DayWidget(date.toString("dd.MM.yyyy"), 0.0, 0.0, 0.0);
		sdb->fillDayWidgetFromBufer(*day);

		connect(day, SIGNAL(clicked(QString)), this, SLOT(makeChanges(QString)));
		mainLayout->addWidget(day, weekNum, weekDay - 1);
		date = date.addDays(1);
		if (weekDay == 7 && date.month() == selectedDate.month()) {
			weekNum++;
		}
	}

	calendarGridGroupBox->setLayout(mainLayout);
}

void MainWindow::changeMonth(QDate date)
{
	selectedDate = QDate(date.year(), date.month(), selectedDate.day());
	reRenderCalendar();
}

void MainWindow::makeChanges(QString date_) 
{
	//QString date_ = date.toString("dd.MM.yyyy");
	qDebug() << date_;
	
	ModalMainWindow modalmainwindow(this);
	//connect(&modalmainwindow, SIGNAL(applied()), SLOT(onApplied()));
	switch (modalmainwindow.exec())
	{
	case QDialog::Rejected:
		//qDebug() << "Decline changes";
		break;
	case QDialog::Accepted:
		//qDebug() << "acccept changes";
		sdb->calculateChanges(date_, modalmainwindow.getInComing(),
			modalmainwindow.getExpense(), modalmainwindow.getSurPlus());
		reRenderCalendar();
		break;
	default:
		break;
	}
}

void MainWindow::pushChanges() 
{
	QMessageBox msgBox;
	msgBox.setInformativeText("Are you sure you want to save change?");
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);

	int ret = msgBox.exec();

	switch (ret)
	{
	case QMessageBox::Save:
		sdb->removeUserData();
		sdb->pushData();
		break;
	case QMessageBox::Cancel:
		break;
	default:
		break;
	}
}

void MainWindow::pullChanges() 
{
	QMessageBox msgBox;
	msgBox.setInformativeText("Are you sure you want to delete your changes?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Yes);

	int ret = msgBox.exec();
	bool isCorrect;

	switch (ret)
	{
	case QMessageBox::Yes:
		sdb->clearBufer();
		isCorrect = sdb->pullUserData();

		if (isCorrect) {
			qDebug() << "request ok (mainwdw)";
		}
		else {
			qDebug() << "bad request (mainwdw)";
		}

		reRenderCalendar();
		break;
	case QMessageBox::Cancel:
		break;
	default:
		break;
	}
}

void MainWindow::reRenderCalendar()
{
	QLayoutItem *item;
	item = windowLayout->itemAt(1);
	windowLayout->removeItem(item);
	windowLayout->removeWidget(item->widget());
	delete item->widget();
	delete item;

	calendar();

	windowLayout->insertWidget(1, calendarGridGroupBox);
	windowLayout->update();
}

void MainWindow::aboutAction() 
{
	QMessageBox msgBox;
	/*msgBox.setInformativeText("\tОписание: Программа для расчета и отображения" 
		"предполагаемого остатка денег на некоторое время вперед.\n"
	"Состав:\n\t -Экран заставка (показываем при старте приложения в течение 3х секунд);\n\t"
	"-Основная форма;\n\t"
	"-Подчиненная форма ввода данных;\n\t"
	"-Окно с инструкцией, поясняющей как пользоваться программой;\n\t"
	"-Окно About.\n"
	"Бизнес-логика:\n\t"
	"интерфейс, в который заносим текущий остаток (когда заходим, на какой захотим день)," 
		"расходы (когда захотим и на какой захотим день), поступления (когда захотим и на какой захотим день), "
		"а оно нам отображает что будет происходить дальше примерно на месяц вперед.\n\n");*/
	msgBox.setInformativeText(QObject::trUtf8("\tОписание: Программа для расчета и отображения" 
		"предполагаемого остатка денег на некоторое время вперед.\n"
	"Состав:\n\t -Экран заставка (показываем при старте приложения в течение 3х секунд);\n\t"
	"-Основная форма;\n\t"
	"-Подчиненная форма ввода данных;\n\t"
	"-Окно с инструкцией, поясняющей как пользоваться программой;\n\t"
	"-Окно About.\n"
	"Бизнес-логика:\n\t"
	"интерфейс, в который заносим текущий остаток (когда заходим, на какой захотим день)," 
		"расходы (когда захотим и на какой захотим день), поступления (когда захотим и на какой захотим день), "
		"а оно нам отображает что будет происходить дальше примерно на месяц вперед.\n\n"));
	msgBox.setStandardButtons(QMessageBox::Ok);

	int ret = msgBox.exec();

	switch (ret)
	{
	case QMessageBox::Ok:
		break;
	default:
		break;
	}
}

void MainWindow::instructAction() 
{
	QMessageBox msgBox;
	msgBox.setInformativeText(QObject::trUtf8("Здесь должна быть инструкция."));
	msgBox.setStandardButtons(QMessageBox::Ok);

	int ret = msgBox.exec();

	switch (ret)
	{
	case QMessageBox::Ok:
		break;
	default:
		break;
	}
}
