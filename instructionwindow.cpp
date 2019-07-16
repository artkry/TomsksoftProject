#include "instructionwindow.h"

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

InstructionWindow::InstructionWindow(QDialog *parent) : QDialog(parent)
{
	this->setGeometry(400, 150, 300, 250);

	fillInfo();

	QPushButton *acceptButton = new QPushButton(tr("OK"));

	connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(aboutInfo);
	mainLayout->addWidget(acceptButton);

	setLayout(mainLayout);
}

InstructionWindow::~InstructionWindow()
{
	delete aboutInfo;
}

void InstructionWindow::fillInfo()
{
	aboutInfo = new QLabel(tr("Здесь должна быть инструкция, но я ее потерял :)"));
}