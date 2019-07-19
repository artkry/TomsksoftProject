#include "editform.h"
#include "dbfasade.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

EditForm::EditForm(QDate date_, QDialog *parent) : QDialog(parent)
{
	this->setGeometry(400, 150, 250, 170);
	_sdb = new DBFasade;
	_buferDate = date_;

	_inComing = new QLineEdit;
	_expense = new QLineEdit;
	_surPlus = new QLineEdit;
	getDateData(date_);

	connect(_inComing, &QLineEdit::textChanged, this, &EditForm::recalcInComing);
	connect(_expense, &QLineEdit::textChanged, this, &EditForm::recalcExpense);

	_mainLayout = new QVBoxLayout;
	createVerticalLayout(date_);
	createHorizontalLayout();
	
	setLayout(_mainLayout);
}

EditForm::~EditForm() {}

void EditForm::createVerticalLayout(QDate date_) 
{
	QFormLayout *layout = new QFormLayout;

	layout->addRow(new QLabel(tr("Date: ")), new QLabel(date_.toString("dd.MM.yyyy")));
	layout->addRow(new QLabel(tr("Prihod: ")), _inComing);
	layout->addRow(new QLabel(tr("Rashod: ")), _expense);
	layout->addRow(new QLabel(tr("Ostatok: ")), _surPlus);

	_mainLayout->addLayout(layout);
}

void EditForm::createHorizontalLayout()
{
	QHBoxLayout *layout = new QHBoxLayout;

	QPushButton *acceptButton = new QPushButton(tr("OK"));
	QPushButton *declineButton = new QPushButton(tr("Decline"));

	connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(declineButton, SIGNAL(clicked()), this, SLOT(reject()));

	layout->addWidget(acceptButton, Qt::AlignBottom | Qt::AlignRight);
	layout->addWidget(declineButton, Qt::AlignBottom | Qt::AlignRight);

	_mainLayout->addLayout(layout);
}

void EditForm::getDateData(QDate date_) 
{
	_sdb->getCurrentDateData(date_, *this);
}

void EditForm::setValues(double inComing_, double expense_, double surplus_)
{
	QString inComing = QString::number(inComing_);
	QString expense = QString::number(expense_);
	QString surPlus = QString::number(surplus_);

	_inComing->insert(inComing);
	_expense->insert(expense);
	_surPlus->insert(surPlus);
}

double EditForm::getInComing() const { return this->_inComing->text().toDouble(); }

double EditForm::getExpense() const { return this->_expense->text().toDouble(); }

double EditForm::getSurPlus() const { return this->_surPlus->text().toDouble(); }

void EditForm::recalcInComing(const QString &txt)
{
	double yesterdaySurplus = _sdb->getYesterdaySurplus(_buferDate);
	double inc = txt.toDouble();
	double exp = this->_expense->text().toDouble();
	double result = inc - exp + yesterdaySurplus;
	QString surPlus = QString::number(result);

	_surPlus->clear();
	_surPlus->insert(surPlus);
}

void EditForm::recalcExpense(const QString &txt)
{
	double yesterdaySurplus = _sdb->getYesterdaySurplus(_buferDate);
	double exp = txt.toDouble();
	double inc = this->_inComing->text().toDouble();
	double result = inc - exp + yesterdaySurplus;
	QString surPlus = QString::number(result);

	_surPlus->clear();
	_surPlus->insert(surPlus);
}