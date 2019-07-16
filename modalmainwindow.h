#ifndef MODALMAINWINDOW_H
#define MODALMAINWINDOW_H

#include <QDialog>

class QPushButton;
class QLineEdit;
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

private:
	void createFormGroupBox();
	void createHorizontalGroupBox();

	QLineEdit *inComing;
	QLineEdit *expense;
	QLineEdit *surPlus;

	QPushButton *acceptButton;
	QPushButton *declineButton;

	QGroupBox *formGroupBox;
	QGroupBox *horizontalGroupBox;
};
#endif // !MODALMAINWINDOW_H
