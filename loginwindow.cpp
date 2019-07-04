#include "loginwindow.h"
#include "database.h"

#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QAction>
#include <QMenuBar>
#include <QMenu>

LoginWindow::LoginWindow()
{
	createMenu();
	createFormGroupBox();
	createHorizontalGroupBox();

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->setMenuBar(menuBar);
	mainLayout->addWidget(horizontalGroupBox);
	mainLayout->addWidget(formGroupBox);
	setLayout(mainLayout);

	setWindowTitle("Welcome!");
}

void LoginWindow::createMenu()
{
	//вынести меню отдельным классом
	menuBar = new QMenuBar;

	fileMenu = new QMenu(tr("&Menu"), this);
	exitAction = fileMenu->addAction(tr("&Exit"));
	menuBar->addMenu(fileMenu);

	connect(exitAction, &QAction::triggered, this, &QDialog::accept);
}

void LoginWindow::createFormGroupBox()
{
	formGroupBox = new QGroupBox(tr("Authorization:"));
	login = new QLineEdit;
	password = new QLineEdit;

	QFormLayout *layout = new QFormLayout;
	layout->addRow(new QLabel(tr("Login: ")), login);
	layout->addRow(new QLabel(tr("Password: ")), password);

	QPushButton *enterButton = new QPushButton(tr("Sign-IN"), this);
	connect(enterButton, SIGNAL(clicked()), this, SLOT(on_enterButton_clicked()));
	//enterButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
	layout->addWidget(enterButton);

	formGroupBox->setLayout(layout);
}

void LoginWindow::createHorizontalGroupBox()
{
	//слой шапки
	horizontalGroupBox = new QGroupBox;
	QHBoxLayout *layout = new QHBoxLayout;

	horizontalGroupBox->setLayout(layout);
}

void LoginWindow::on_enterButton_clicked()
{
	//все qDebug выводы только для информативности в debug консоле
	QString log = this->login->text();
	QString pass = this->password->text();

	database = new Database;

	QSqlQuery a_query(database->sdb);
	QString str;
	bool isCorrect;

	QString str_ = "SELECT passwd FROM Users WHERE Users.profile_name LIKE '%1';";
	str = str_.arg(log);

	isCorrect = a_query.exec(str);
	if (!isCorrect) {
		qDebug() << "Request not completed!";
	}
	else {
		qDebug() << "Request complited!";
	}
	
	QSqlRecord rec = a_query.record();
	QString pw = "";

	while (a_query.next()) {
		pw = a_query.value(rec.indexOf("passwd")).toString();
	}

	if (pass != pw) {
		qDebug() << "Incorrect password, pls try again!";
	}
	else {
		//некорректно с pw, доработать
		if (pw == "") {
			qDebug() << "Profile with this name isn't exists";
		}
		else {
			qDebug() << "Success!";
			//вызов коннекта на основную форму, авторизация прошла
		}
	}
}

LoginWindow::~LoginWindow() {}