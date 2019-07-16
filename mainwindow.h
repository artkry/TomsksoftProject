#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QDate>

class QAction;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextBrowser;
class QGroupBox;
class QVBoxLayout;
class DBFasade;

class MainWindow : public QDialog
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();

public slots:
	void changeMonth(QDate date);
	void pushChanges();
	void pullChanges();
	void makeChanges(QString date_);
	void aboutAction();
	void instructAction();

private:
	void createMenu();
	void createHorizontalGroupBox();
	void createHorizontalButtonBox();
	void calendar();
	void reRenderCalendar();

	QDate selectedDate;
	QVBoxLayout *windowLayout;
	QGroupBox *horizontalGroupBox;
	QGroupBox *horizontalButtonBox;
	QGroupBox *calendarGridGroupBox;
	
	QMenuBar *menuBar;
	QMenu *fileMenu;
	QAction *exitAction;

	DBFasade *sdb;
};
#endif // !MAINWINDOW_H
