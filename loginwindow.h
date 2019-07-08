#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

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
class RegistrationWindow;
class MainWindow;

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
	void createFormGroupBox();
	void createMenu();
	void createHorizontalGroupBox();

	QMenuBar *menuBar;
	QGroupBox *formGroupBox;
	QGroupBox *horizontalGroupBox;
	QLineEdit *login;
	QLineEdit *pass;
	
	RegistrationWindow *registrWindow;
	MainWindow *mainWindow;

	QMenu *fileMenu;
	QAction *exitAction;

	DBFasade *sdb;
};

#endif // !LOGINWINDOW_H
