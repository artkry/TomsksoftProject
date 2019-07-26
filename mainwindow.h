#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QDate>

class QVBoxLayout;
class QGridLayout;
class QLabel;

class MainWindow :public QDialog
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();
private slots:
	void makeChanges(QDate date_);
	void aboutAction();
	void instructAction();

	void addMonth();
	void subMonth();

protected:
	void createMenu();
	void createCalendarGroupBox();
	void reRenderCalendar();

	void createMonthMenu();

	QDate _selectedDate;
	QGridLayout *_calendarLayout;
	QLabel *_currentDateLabel;
	QVBoxLayout *_mainLayout;
};
#endif // !MAINWINDOW_H
