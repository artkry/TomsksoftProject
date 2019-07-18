#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QDialog>

class DBFasade;
class QLineEdit;
class QVBoxLayout;
class LoginWindow;

class RegistrationWindow : public QDialog
{
	Q_OBJECT

public:
	RegistrationWindow();
	~RegistrationWindow();

private slots:
	void on_enterButton_clicked();
	void on_loginButton_clicked();

private:
	void createHorizontalLayout();
	void createFormLayout();

	QVBoxLayout *_mainLayout;
	QLineEdit *_login;
	QLineEdit *_pass;
	QLineEdit *_confirmPass;

	DBFasade *_sdb;
	LoginWindow *_loginWindow;
};
#endif // !REGISTRATIONWINDOW_H