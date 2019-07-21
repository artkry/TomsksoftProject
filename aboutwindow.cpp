#include "aboutwindow.h"

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

AboutWindow::AboutWindow(QDialog *parent) : QDialog(parent)
{
	this->setGeometry(400, 150, 500, 300);

	fillInfo();

	QPushButton *acceptButton = new QPushButton(tr("OK"));

	connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addWidget(_aboutInfo, 0, Qt::AlignCenter);
	mainLayout->addWidget(acceptButton, 0, Qt::AlignBottom | Qt::AlignRight);

	setLayout(mainLayout);
}

AboutWindow::~AboutWindow() {}

void AboutWindow::fillInfo() 
{
	_aboutInfo = new QLabel(QObject::trUtf8("Описание:\n\t Программа для расчета и отображения"
		"предполагаемого остатка денег на некоторое время вперед.\n"
		"Состав: \n\t -Экран заставка;\n\t"
	"-Основная форма;\n\t"
	"-Формы авторизации и регистрации;\n\t"
	"-Подчиненная форма ввода данных;\n\t"
	"-Окно с инструкцией;\n\t"
	"-Окно About.\n"
	"Бизнес-логика: \n\t"
	"Интерфейс, в который заносим текущий остаток(когда захотим на какой день захотим),\n"
	"расходы(когда захотим на какой день захотим), \n"
	"поступления(когда захотим на какой день захотим), \n"
	"а оно нам отображает, что будет происходить дальше согласно всем данным."));

	_aboutInfo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}