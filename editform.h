#ifndef EDITFORM_H
#define EDITFORM_H

#include <QDialog>
#include <QDate>

class QLineEdit;
class QVBoxLayout;

class EditForm : public QDialog
{
	Q_OBJECT
public:
	EditForm(QDate date_, QDialog *parent = 0);
	~EditForm();
	void setValues(double inComing_, double expense_, double surplus_);
	
	double getInComing() const;
	double getExpense() const;
	double getSurPlus() const;

signals:
	void acceptChanges();

private slots:
    void recalcInComing(const QString &txt);
	void recalcExpense(const QString &txt);

protected:
	void createVerticalLayout(QDate date_);
	void createHorizontalLayout();
	void getDateData(QDate date_);

	QLineEdit *_inComing;
	QLineEdit *_expense;
	QLineEdit *_surPlus;
	QVBoxLayout *_mainLayout;
	QDate _buferDate;
};
#endif // !EDITFORM_H
