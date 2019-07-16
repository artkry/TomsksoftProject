#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

class QLabel;

class AboutWindow : public QDialog
{
	Q_OBJECT

public:
	AboutWindow(QDialog *parent);
	~AboutWindow();
private:
	void fillInfo();

	QLabel *aboutInfo;
};
#endif // !ABOUTWINDOW_H
