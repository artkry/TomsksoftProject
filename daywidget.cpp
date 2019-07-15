#include "daywidget.h"

#include <QLabel>
#include <QDate>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFormLayout>

DayWidget::DayWidget(QString date_, double inComing_, double expense_, double surPlus_)
{
	setDate(date_);

	this->inComing = inComing_;
	this->expense = expense_;
	this->surPlus = surPlus_;

	createFormGroupBox();

	mainLayout = new QVBoxLayout;
	mainLayout->addWidget(formGroupBox);
	setLayout(mainLayout);
}

DayWidget::~DayWidget() 
{
	//delete &date;
	delete formGroupBox;
}

void DayWidget::createFormGroupBox()
{
	QLabel *inComLabel = new QLabel;
	inComLabel->setText(QString::number(this->inComing, 'f', 1));
	QLabel *expenseLabel = new QLabel;
	expenseLabel->setText(QString::number(this->expense, 'f', 1));
	QLabel *surPlusLabel = new QLabel;
	surPlusLabel->setText(QString::number(this->surPlus, 'f', 1));

	
	formGroupBox = new QGroupBox;
	QFormLayout *layout = new QFormLayout;

	layout->addRow(new QLabel(tr("Date: ")), new QLabel(this->date));
	layout->addRow(new QLabel(tr("Prihod: ")), inComLabel);
	layout->addRow(new QLabel(tr("Rashod: ")), expenseLabel);
	layout->addRow(new QLabel(tr("Ostatok: ")), surPlusLabel);

	formGroupBox->setLayout(layout);
}

void DayWidget::mousePressEvent(QMouseEvent *event) { emit clicked(this->date); }

void DayWidget::setDate(QString date_) { this->date = date_; }

void DayWidget::setInComing(double inComing_) 
{ 
	this->inComing = inComing_;
	mainLayout->removeWidget(formGroupBox);
	delete formGroupBox;
	mainLayout->update();
	createFormGroupBox();
	mainLayout->insertWidget(0, formGroupBox);
	mainLayout->update();
}

void DayWidget::setExpense(double expense_) 
{ 
	this->expense = expense_; 
	mainLayout->removeWidget(formGroupBox);
	delete formGroupBox;
	mainLayout->update();
	createFormGroupBox();
	mainLayout->insertWidget(0, formGroupBox);
	mainLayout->update();
}

void DayWidget::setSurPlus(double surPlus_) 
{ 
	this->surPlus = surPlus_; 
	mainLayout->removeWidget(formGroupBox);
	delete formGroupBox;
	mainLayout->update();
	createFormGroupBox();
	mainLayout->insertWidget(0, formGroupBox);
	mainLayout->update();
}

QString DayWidget::getDate() const { return this->date; }
double DayWidget::getInComing() const { return this->inComing; }
double DayWidget::getExpense() const { return this->expense; }
double DayWidget::getSurPlus() const { return this->surPlus; }

