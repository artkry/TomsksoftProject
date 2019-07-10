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
class ModalMainWindow;

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
	void makeChanges();

private:
	void createMenu();
	void createHorizontalGroupBox();
	void createHorizontalButtonBox();
	void calendar();
	void calendar1();

	QDate selectedDate;
	QTextBrowser *editor;
	QGroupBox *horizontalGroupBox;
	QGroupBox *horizontalButtonBox;

	
	QMenuBar *menuBar;
	QMenu *fileMenu;
	QAction *exitAction;
};
#endif // !MAINWINDOW_H
