#include <QApplication>
#include "loginwindow.h"
#include "mainwindow.h"

#include <QDate>
int main(int argc, char *argv[]) 
{
	QApplication app(argc, argv);

	LoginWindow loginwindow;
	loginwindow.show();

	//MainWindow mainwindow;
	//mainwindow.show();

	return app.exec();
}