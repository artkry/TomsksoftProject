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
	aboutInfo = new QLabel(tr("\t��������: ��������� ��� ������� � �����������" 
		"��������������� ������� ����� �� ��������� ����� ������.\n"
	"������:\n\t -����� �������� (���������� ��� ������ ���������� � ������� 3� ������);\n\t"
	"-�������� �����;\n\t"
	"-����������� ����� ����� ������;\n\t"
	"-���� � �����������, ���������� ��� ������������ ����������;\n\t"
	"-���� About.\n"
	"������-������:\n\t"
	"���������, � ������� ������� ������� ������� (����� �������, �� ����� ������� ����),\n" 
		"������� (����� ������� � �� ����� ������� ����), ����������� (����� ������� � �� ����� ������� ����),\n "
		"� ��� ��� ���������� ��� ����� ����������� ������ �������� �� ����� ������.\n\n"));

	aboutInfo->setGeometry(20, 20, 250, 250);
}