#ifndef INSTRUCTIONWINDOW_H
#define INSTRUCTIONWINDOW_H

#include <QDialog>

class QLabel;

class InstructionWindow : public QDialog
{
	Q_OBJECT
public:
	InstructionWindow(QDialog *parent);
	~InstructionWindow();
private:
	void fillInfo();

	QLabel *aboutInfo;
};
#endif // !INSTRUCTIONWINDOW_H