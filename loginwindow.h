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

class LoginWindow : public QDialog
{
	Q_OBJECT

public:
	LoginWindow();
	~LoginWindow();

private slots:
    void authRequest();

private:
	void createFormGroupBox();
	void createMenu();
	void createHorizontalGroupBox();

	QMenuBar *menuBar;
	QGroupBox *formGroupBox;
	QGroupBox *horizontalGroupBox;

	QMenu *fileMenu;
	QAction *exitAction;
};

#endif // !LOGINWINDOW_H
