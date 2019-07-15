#include <QApplication>
#include "mainwindow.h"
#include "loginwindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	//раскомментируйте это:
	LoginWindow loginwindow;
	loginwindow.show();
	//

	//закомментируйте это: 
	//MainWindow mainwindow;
	//mainwindow.show();
	//

    return app.exec();
}