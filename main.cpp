#include <QApplication>
#include "mainwindow.h"
#include "loginwindow.h"
#include "database.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	//������������� ��, �������� ������� ������
	
	
	LoginWindow loginwindow;
	loginwindow.show();
	
    return app.exec();
}

