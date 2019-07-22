#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

class QLineEdit;
class QVBoxLayout;
class RegistrationWindow;

class LoginWindow : public QDialog
{
	Q_OBJECT

public:
	LoginWindow();
	~LoginWindow();

private slots:
	void on_enterButton_clicked();
	void on_registrButton_clicked();

private:
	void createHorizontalLayout();
	void createFormLayout();

	QVBoxLayout *_mainLayout;
	QLineEdit *_login;
	QLineEdit *_pass;

	RegistrationWindow *_registrWindow;
};
#endif // !LOGINWINDOW_H
