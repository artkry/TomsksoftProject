#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QDate>

class DBFasade;
class QVBoxLayout;
class QGroupBox;

class MainWindow :public QDialog
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();
private slots:
	void changeMonth(QDate date_);
	void makeChanges(QDate date_);

protected:
	void createMenu();
	void createHorizontalLayout();
	void createCalendarGroupBox();
	void reRenderCalendar();

	QDate _selectedDate;

	QVBoxLayout *_mainLayout;
	QGroupBox *_calendarGroupBox;
	DBFasade *_sdb;
};
#endif // !MAINWINDOW_H
