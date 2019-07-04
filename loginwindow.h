#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "database.h"

class QAction;
class QLabel;
class QGroupBox;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QMenu;
class QMenuBar;

class LoginWindow : public QDialog, Database
{
	Q_OBJECT

public:
	LoginWindow();
	~LoginWindow();

private slots:
    void on_enterButton_clicked();

private:
	void createFormGroupBox();
	void createMenu();
	void createHorizontalGroupBox();

	QMenuBar *menuBar;
	QGroupBox *formGroupBox;
	QGroupBox *horizontalGroupBox;
	QLineEdit *login;
	QLineEdit *password;

	QMenu *fileMenu;
	QAction *exitAction;
	Database *database;
};

#endif // !LOGINWINDOW_H
