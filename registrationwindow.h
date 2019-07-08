#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QDialog>

class QAction;
class QLabel;
class QGroupBox;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QMenu;
class QMenuBar;
class DBFasade;
class LoginWindow;

class RegistrationWindow : public QDialog
{
	Q_OBJECT

public:
	RegistrationWindow();
	~RegistrationWindow();

private slots:
    void on_enterButton_clicked();
	void go_to_loginwindow();



private:
	void createHorizontalGroupBox();
	void createMenu();
	void createFormGroupBox();

	QMenuBar *menuBar;
	QGroupBox *horizontalGroupBox;
	QGroupBox *formGroupBox;
	QLineEdit *login;
	QLineEdit *pass;
	LoginWindow *loginwindow;
	QMenu *fileMenu;
	QAction *exitAction;
	DBFasade *sdb;
};
#endif // !REGISTRATIONWINDOW_H
