#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QDate>

class QVBoxLayout;
class QGridLayout;

class MainWindow :public QDialog
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();
private slots:
	void changeMonth(QDate date_);
	void makeChanges(QDate date_);
	void aboutAction();
	void instructAction();

protected:
	void createMenu();
	void createHorizontalLayout();
	void createCalendarGroupBox();
	void reRenderCalendar();

	QDate _selectedDate;
	QGridLayout *_calendarLayout;
	QVBoxLayout *_mainLayout;
};
#endif // !MAINWINDOW_H
