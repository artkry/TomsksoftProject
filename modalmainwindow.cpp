#include "modalmainwindow.h"

#include <QBoxLayout>
#include <QAction>
#include <QGroupBox>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>

ModalMainWindow::ModalMainWindow(QDialog *parent) : QDialog(parent)
{
	this->setGeometry(400, 150, 250, 170);
	createFormGroupBox();
	createHorizontalGroupBox();

	QVBoxLayout *mainlayout = new QVBoxLayout;

	mainlayout->addWidget(formGroupBox);
	mainlayout->addWidget(horizontalGroupBox);
	setLayout(mainlayout);

}

ModalMainWindow::~ModalMainWindow() {}

void ModalMainWindow::createFormGroupBox()
{
	formGroupBox = new QGroupBox(tr("Input your data: "));

	QFormLayout *layout = new QFormLayout;

	longDate = new QLineEdit;
	date = new QLineEdit;
	inComing = new QLineEdit;
	expense = new QLineEdit;
	surPlus = new QLineEdit;

	layout->addRow(new QLabel(tr("How many days?: ")), longDate);
	layout->addRow(new QLabel(tr("Date: ")), date);
	layout->addRow(new QLabel(tr("Prihod: ")), inComing);
	layout->addRow(new QLabel(tr("Rashod: ")), expense);
	layout->addRow(new QLabel(tr("Ostatok: ")), surPlus);

	formGroupBox->setLayout(layout);
}

void ModalMainWindow::createHorizontalGroupBox()
{
	horizontalGroupBox = new QGroupBox;
	QHBoxLayout *layout = new QHBoxLayout;

	acceptButton = new QPushButton(tr("OK"));
	declineButton = new QPushButton(tr("Decline"));


	//connect(acceptButton, SIGNAL(clicked()), this, SLOT());
	connect(declineButton, SIGNAL(clicked()), this, SLOT(reject()));

	layout->addWidget(declineButton);
	layout->addSpacing(150);
	layout->addWidget(acceptButton);

	horizontalGroupBox->setLayout(layout);
}
