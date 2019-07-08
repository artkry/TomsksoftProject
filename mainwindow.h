#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

class QAction;
class QDialogButtonBox;
class QMenu;
class QMenuBar;
class QPushButton;
class DBFasade;

class MainWindow : public QDialog
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();

private:
	void createMenu();

	enum {January = 31, February = 28, 
	      March = 31, April = 30, May = 31,
	      June = 30, July = 31, August = 31,
	      September = 30, October = 31,
	      November = 30, December = 31};

	QMenuBar *menuBar;
	QDialogButtonBox *buttonBox;

	QMenu *fileMenu;
	QAction *exitAction;
};


#endif // !MAINWINDOW_H
