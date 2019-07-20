#include "daywidget.h"
#include "dbfasade.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>

DayWidget::DayWidget(QDate date_)
{
	_sdb = new DBFasade;
	this->_date = date_;

	_sdb->fillDayWidget(date_, _inComing, _expense, _surPlus);

	_mainLayout = new QVBoxLayout;
	createFormLayout();
	setLayout(_mainLayout);
}

DayWidget::~DayWidget() 
{
	delete _sdb;
}

void DayWidget::createFormLayout()
{
	QLabel *inComLabel = new QLabel;
	inComLabel->setText(QString::number(this->_inComing, 'f', 1));
	QLabel *expenseLabel = new QLabel;
	expenseLabel->setText(QString::number(this->_expense, 'f', 1));
	QLabel *surPlusLabel = new QLabel;
	surPlusLabel->setText(QString::number(this->_surPlus, 'f', 1));

	QFormLayout *layout = new QFormLayout;
	
	layout->addRow(new QLabel(tr("Date: ")), new QLabel(this->_date.toString("dd.MM.yyyy")));
	layout->addRow(new QLabel(tr("Prihod: ")), inComLabel);
	layout->addRow(new QLabel(tr("Rashod: ")), expenseLabel);
	layout->addRow(new QLabel(tr("Ostatok: ")), surPlusLabel);

	_mainLayout->addLayout(layout);
}

void DayWidget::mousePressEvent(QMouseEvent *event) { emit clicked(this->_date); }

void DayWidget::setDate(QDate date_) { this->_date = date_; }
void DayWidget::setInComing(double inComing_) { this->_inComing = inComing_; }
void DayWidget::setExpense(double expense_) { this->_expense = expense_; }
void DayWidget::setSurPlus(double surPlus_) { this->_surPlus = surPlus_; }

QDate DayWidget::getDate() const { return this->_date; }
double DayWidget::getInComing() const { return this->_inComing; }
double DayWidget::getExpense() const { return this->_expense; }
double DayWidget::getSurPlus() const { return this->_surPlus; }
