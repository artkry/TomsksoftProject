#include "aboutwindow.h"

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

AboutWindow::AboutWindow(QDialog *parent) : QDialog(parent)
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

AboutWindow::~AboutWindow() 
{
	delete aboutInfo;
}

void AboutWindow::fillInfo() 
{
	aboutInfo = new QLabel(tr("\tОписание: Программа для расчета и отображения" 
		"предполагаемого остатка денег на некоторое время вперед.\n"
	"Состав:\n\t -Экран заставка (показываем при старте приложения в течение 3х секунд);\n\t"
	"-Основная форма;\n\t"
	"-Подчиненная форма ввода данных;\n\t"
	"-Окно с инструкцией, поясняющей как пользоваться программой;\n\t"
	"-Окно About.\n"
	"Бизнес-логика:\n\t"
	"интерфейс, в который заносим текущий остаток (когда заходим, на какой захотим день),\n" 
		"расходы (когда захотим и на какой захотим день), поступления (когда захотим и на какой захотим день),\n "
		"а оно нам отображает что будет происходить дальше примерно на месяц вперед.\n\n"));

	aboutInfo->setGeometry(20, 20, 250, 250);
}