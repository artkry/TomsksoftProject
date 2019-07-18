#include "registrationwindow.h"
#include "dbfasade.h"
#include "loginwindow.h"

#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QAction>
#include <QMenuBar>
#include <QMenu>

RegistrationWindow::RegistrationWindow()
{
	this->setGeometry(300, 100, 500, 500);

	_sdb = new DBFasade;

	_mainLayout = new QVBoxLayout;
	createHorizontalLayout();
	createFormLayout();
	setLayout(_mainLayout);

	setWindowTitle("Registration");
}

RegistrationWindow::~RegistrationWindow() {}

void RegistrationWindow::createHorizontalLayout()
{
	QPixmap pix("logo.png");

	QHBoxLayout *layout = new QHBoxLayout;

	QLabel *logoLabel = new QLabel;
	logoLabel->setPixmap(pix);
	layout->addWidget(logoLabel);

	_mainLayout->addLayout(layout);
}

void RegistrationWindow::createFormLayout()
{
	_login = new QLineEdit;
	_pass = new QLineEdit;
	_confirmPass = new QLineEdit;
	
	_pass->setEchoMode(QLineEdit::Password);
	_confirmPass->setEchoMode(QLineEdit::Password);

	QFormLayout *layout = new QFormLayout;
	layout->addRow(new QLabel(tr("Login: ")), _login);
	layout->addRow(new QLabel(tr("Password: ")), _pass);
	layout->addRow(new QLabel(tr("Confirm Password: ")), _confirmPass);

	QPushButton *enterButton = new QPushButton(tr("Registration"), this);
	QPushButton *loginButton = new QPushButton(tr("Back to Sign-In"), this);

	connect(enterButton, SIGNAL(clicked()), this, SLOT(on_enterButton_clicked()));
	connect(loginButton, SIGNAL(clicked()), this, SLOT(on_loginButton_clicked()));

	layout->addWidget(enterButton);
	layout->addWidget(loginButton);
	_mainLayout->addLayout(layout);
}

void RegistrationWindow::on_enterButton_clicked()
{
	if (this->_pass->text() == this->_confirmPass->text()) {

		bool isCorrect = _sdb->createUser(this->_login->text(), this->_pass->text());

		if (!isCorrect) {
			qDebug() << "Registration is failed! Input correct data!";
		}
		else {
			qDebug() << "Registration is success!";
		}

	}
	else {
		qDebug() << "Incorrect confirm password! Try again!";
	}
}

void RegistrationWindow::on_loginButton_clicked()
{
	this->close();
	_loginWindow = new LoginWindow;
	_loginWindow->show();
}
