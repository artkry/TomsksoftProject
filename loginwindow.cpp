#include "loginwindow.h"
#include "dbsingleton.h"
#include "registrationwindow.h"
#include "mainwindow.h"

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
	this->setGeometry(300, 100, 500, 330);
	this->setFixedSize(500, 330);

	//_sdb = DATABASE;

	_mainLayout = new QVBoxLayout;
	createHorizontalLayout();
	createFormLayout();
	setLayout(_mainLayout);

	setWindowTitle("Welcome!");
}

LoginWindow::~LoginWindow() {}

void LoginWindow::createHorizontalLayout() 
{
	QPixmap pix(":logo.png");

	QHBoxLayout *layout = new QHBoxLayout;

	QLabel *logoLabel = new QLabel;
	logoLabel->setPixmap(pix);
	layout->addWidget(logoLabel);

	_mainLayout->addLayout(layout);
}

void LoginWindow::createFormLayout() 
{
	_login = new QLineEdit;
	_pass = new QLineEdit;
	_pass->setEchoMode(QLineEdit::Password);

	QFormLayout *layout = new QFormLayout;
	layout->addRow(new QLabel(tr("Login: ")), _login);
	layout->addRow(new QLabel(tr("Password: ")), _pass);

	QPushButton *enterButton = new QPushButton(tr("Sign-IN"), this);
	QPushButton *registrButton = new QPushButton(tr("Create new User"), this);

	connect(enterButton, SIGNAL(clicked()), this, SLOT(on_enterButton_clicked()));
	connect(registrButton, SIGNAL(clicked()), this, SLOT(on_registrButton_clicked()));

	layout->addWidget(enterButton);
	layout->addWidget(registrButton);
	_mainLayout->addLayout(layout);
}

void LoginWindow::on_enterButton_clicked()
{
	if (!(this->_login->text() == "" || this->_pass->text() == "")) {
		//bool isCorrect = _sdb->authRequest(this->_login->text(), this->_pass->text());
		bool isCorrect = DATABASE.authRequest(this->_login->text(), this->_pass->text());


		if (!isCorrect) {
			qDebug() << "Auth is failed! Input correct data!";
		}
		else {
			qDebug() << "Auth is success!";
			this->close();
			MainWindow *mainWindow = new MainWindow;
			mainWindow->show();
		}
	}
	else {
		qDebug() << "ZAPOLNITE POLYA !";
	}
}

void LoginWindow::on_registrButton_clicked()
{
	this->close();
	_registrWindow = new RegistrationWindow;
	_registrWindow->show();
}