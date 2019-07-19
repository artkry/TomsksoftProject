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
	mainLayout->addWidget(_aboutInfo, 0, Qt::AlignCenter);
	mainLayout->addWidget(acceptButton, 0, Qt::AlignBottom | Qt::AlignRight);

	setLayout(mainLayout);
}

AboutWindow::~AboutWindow() {}

void AboutWindow::fillInfo() 
{
	_aboutInfo = new QLabel(tr("��������:\n\t ��������� ��� ������� � �����������"
		"��������������� ������� ����� �� ��������� ����� ������.\n"
		"������: \n\t -����� ��������;\n\t"
	"-�������� �����;\n\t"
	"-����� ����������� � �����������;\n\t"
	"-����������� ����� ����� ������;\n\t"
	"-���� � �����������;\n\t"
	"-���� About.\n"
	"������-������: \n\t"
	"���������, � ������� ������� ������� �������(����� ������� �� ����� ���� �������),\n"
	"�������(����� ������� �� ����� ���� �������), \n"
	"�����������(����� ������� �� ����� ���� �������), \n"
	"� ��� ��� ����������, ��� ����� ����������� ������ �������� ���� ������."));
}