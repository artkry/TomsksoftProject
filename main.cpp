#include <QApplication>
#include "mainwindow.h"
#include "loginwindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	//���������������� ���:
	LoginWindow loginwindow;
	loginwindow.show();
	//

	//��������������� ���: 
	//MainWindow mainwindow;
	//mainwindow.show();
	//

    return app.exec();
}