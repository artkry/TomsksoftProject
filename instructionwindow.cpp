#include "instructionwindow.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>


InstructionWindow::InstructionWindow(QDialog *parent) : QDialog(parent)
{
	this->setGeometry(400, 150, 400, 300);
	//this->setFixedSize(400, 300);
	fillInfo();

	QPushButton *acceptButton = new QPushButton(tr("OK"));

	connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(_aboutInfo, 0, Qt::AlignCenter);
	mainLayout->addWidget(acceptButton, 0, Qt::AlignBottom | Qt::AlignRight);

	setLayout(mainLayout);
}

InstructionWindow::~InstructionWindow() {}

void InstructionWindow::fillInfo()
{
	_aboutInfo = new QLabel(QObject::trUtf8("Здесь должна быть инфтрукция!"));
}