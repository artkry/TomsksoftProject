#include "daywidget.h"

#include <QLabel>
#include <QDate>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFormLayout>

DayWidget::DayWidget(QDate date_, double inComing_, double expense_, double surPlus_)
{
	setInComing(inComing_);
	setExpense(expense_);
	setSurPlus(surPlus_);
	setDate(date_);

	createFormGroupBox();

	QVBoxLayout *mainlayout = new QVBoxLayout;
	mainlayout->addWidget(formGroupBox);
	setLayout(mainlayout);
}

DayWidget::~DayWidget() 
{
	//delete &date;
	delete formGroupBox;
}

void DayWidget::createFormGroupBox()
{
	QLabel *inComLabel = new QLabel;
	inComLabel->setText(QString::number(this->inComing, 'f', 3));
	QLabel *expenseLabel = new QLabel;
	expenseLabel->setText(QString::number(this->expense, 'f', 3));
	QLabel *surPlusLabel = new QLabel;
	surPlusLabel->setText(QString::number(this->surPlus, 'f', 3));

	
	formGroupBox = new QGroupBox;
	QFormLayout *layout = new QFormLayout;

	layout->addRow(new QLabel(tr("Date: ")), new QLabel(this->date.toString()));
	layout->addRow(new QLabel(tr("Prihod: ")), inComLabel);
	layout->addRow(new QLabel(tr("Rashod: ")), expenseLabel);
	layout->addRow(new QLabel(tr("Ostatok: ")), surPlusLabel);

	formGroupBox->setLayout(layout);
}

void DayWidget::mousePressEvent(QMouseEvent *event) { emit clicked(); }

void DayWidget::setDate(QDate date_) { this->date = date_; }
void DayWidget::setInComing(double inComing_) { this->inComing = inComing_; }
void DayWidget::setExpense(double expense_) { this->expense = expense_; }
void DayWidget::setSurPlus(double surPlus_) { this->surPlus = surPlus_; }

QDate DayWidget::getDate() const { return this->date; }
double DayWidget::getInComing() const { return this->inComing; }
double DayWidget::getExpense() const { return this->expense; }
double DayWidget::getSurPlus() const { return this->surPlus; }
