#ifndef MODALMAINWINDOW_H
#define MODALMAINWINDOW_H

#include <QDialog>

class QPushButton;
class QLineEdit;
class QAction;
class QGroupBox;

class ModalMainWindow :public QDialog
{
	Q_OBJECT

public:
	ModalMainWindow(QDialog *parent = 0);
	~ModalMainWindow();
	double getInComing() const;
	double getExpense() const;
	double getSurPlus() const;

private slots:
    void on_push_button_clicked();

private:
	void createFormGroupBox();
	void createHorizontalGroupBox();

	//QLineEdit *longDate;
	QLineEdit *inComing;
	QLineEdit *expense;
	QLineEdit *surPlus;

	QPushButton *acceptButton;
	QPushButton *declineButton;

	QGroupBox *formGroupBox;
	QGroupBox *horizontalGroupBox;
};
#endif // !MODALMAINWINDOW_H
