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

	editor = new QTextBrowser;
	//calendar();
	calendar1();
	
	windowLayout = new QVBoxLayout;
	windowLayout->setMenuBar(menuBar);
	windowLayout->addWidget(horizontalGroupBox);
	//mainLayout->addWidget(editor, 1);
	windowLayout->addWidget(calendarGridGroupBox);
	windowLayout->addWidget(horizontalButtonBox);
	setLayout(windowLayout);

	setWindowTitle(tr("Home Accounting"));
}

MainWindow::~MainWindow() {}

void MainWindow::createMenu()
{
	menuBar = new QMenuBar;

	fileMenu = new QMenu(tr("&Menu"), this);
	exitAction = fileMenu->addAction(tr("&Exit"));
	menuBar->addMenu(fileMenu);

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
	QPushButton *change = new QPushButton(tr("Make Change"));
	QPushButton *pull = new QPushButton(tr("Pull Data"));
	QPushButton *push = new QPushButton(tr("Push Data"));

	//connect(change, SIGNAL(clicked()), this, SLOT(makeChanges()));
	//connect(pull, SIGNAL(clicked()), this, SLOT(pullChanges()));
	//connect(push, SIGNAL(clicked()), this, SLOT(pushChanges()));

	layout->addWidget(change);
	layout->addSpacing(150);
	layout->addWidget(pull);
	layout->addSpacing(150);
	layout->addWidget(push);

	horizontalButtonBox->setLayout(layout);
}


void MainWindow::calendar()
{
	editor->clear();
	QTextCursor cursor = editor->textCursor();
	cursor.beginEditBlock();

	QDate date(selectedDate.year(), selectedDate.month(), 1);

	QTextTableFormat tableFormat;
	tableFormat.setAlignment(Qt::AlignCenter);
	//tableFormat.setBackground(QColor("FDDCFF"));
	tableFormat.setCellPadding(4);
	tableFormat.setCellSpacing(0);
	QVector <QTextLength> constraints;
	constraints << QTextLength(QTextLength::PercentageLength, 15)
		<< QTextLength(QTextLength::PercentageLength, 15)
		<< QTextLength(QTextLength::PercentageLength, 15)
		<< QTextLength(QTextLength::PercentageLength, 15)
		<< QTextLength(QTextLength::PercentageLength, 15)
		<< QTextLength(QTextLength::PercentageLength, 15)
		<< QTextLength(QTextLength::PercentageLength, 15);
	
	tableFormat.setColumnWidthConstraints(constraints);
	QTextTable *table = cursor.insertTable(1, 7, tableFormat);

	//QTextCharFormat format = cursor.charFormat();

	QTextBlockFormat centerAlignment;
	centerAlignment.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	QTextBlockFormat leftAlignment;
	leftAlignment.setAlignment(Qt::AlignLeft);

	for (int weekDay = 0; weekDay < 7; ++weekDay) {
		QTextTableCell cell = table->cellAt(0, weekDay);
		QTextCursor cellCursor = cell.firstCursorPosition();
		cellCursor.setBlockFormat(centerAlignment);
		cellCursor.insertText(QString("%1").arg(QDate::longDayName(weekDay + 1)));
	}
	table->insertRows(table->rows(), 1);

	while (date.month() == selectedDate.month()) {
		int weekDay = date.dayOfWeek();
		QTextTableCell cell = table->cellAt(table->rows() - 1, weekDay - 1);
		QTextCursor cellCursor = cell.firstCursorPosition();
		cellCursor.setBlockFormat(leftAlignment);
		//здесь будут вноситься аргументы, перегружу метод
		cellCursor.insertText(QString("%1\nPrihod: %2\nRashod: %3\nOstatok: %4").arg(date.day()).arg("0").arg("0").arg("0"));
		date = date.addDays(1);
		if (weekDay == 7 && date.month() == selectedDate.month()) {
			table->insertRows(table->rows(), 1);
		}
	}

	cursor.endEditBlock();

}

void MainWindow::calendar1()
{
	QDate date(selectedDate.year(), selectedDate.month(), 1);

	calendarGridGroupBox = new QGroupBox;
	QGridLayout *mainLayout = new QGridLayout;
	//mainLayout->setSpacing(0);
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
	
		qDebug() << day->getDate() << "m";
		qDebug() << day->getInComing() << "m";
		qDebug() << day->getExpense() << "m";
		qDebug() << day->getSurPlus() << "m";
		connect(day, SIGNAL(clicked(QString)), this, SLOT(makeChanges(QString)));
		mainLayout->addWidget(day, weekNum, weekDay - 1);
		date = date.addDays(1);
		if (weekDay == 7 && date.month() == selectedDate.month()) {
			weekNum++;
		}
	}
	//mainLayout->setVerticalSpacing(0);
	//mainLayout->setHorizontalSpacing(0);
	calendarGridGroupBox->setLayout(mainLayout);
}

void MainWindow::changeMonth(QDate date)
{
	selectedDate = QDate(date.year(), date.month(), selectedDate.day());
	QLayoutItem *item;
	while ((item = windowLayout->itemAt(2))) {
		windowLayout->removeItem(item);
		windowLayout->removeWidget(item->widget());
		delete item->widget();
		delete item;
		windowLayout->update();
	}
	//windowLayout->removeWidget(calendarGridGroupBox);
	//delete calendarGridGroupBox;
	calendar1();
	//windowLayout->removeWidget(calendarGridGroupBox);
	windowLayout->insertWidget(1, calendarGridGroupBox);
	windowLayout->update();
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
		calendar1();
		break;
	default:
		break;
	}
}

void MainWindow::pushChanges() {}

void MainWindow::pullChanges() {}