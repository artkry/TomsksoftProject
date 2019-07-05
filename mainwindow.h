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

	QMenuBar *menuBar;
	QDialogButtonBox *buttonBox;

	QMenu *fileMenu;
	QAction *exitAction;
	DBFasade *sdb;
};


#endif // !MAINWINDOW_H
