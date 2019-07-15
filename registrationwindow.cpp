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
	//setAttribute(Qt::WA_DeleteOnClose);
	this->setGeometry(300, 100, 500, 500);
	createMenu();
	createHorizontalGroupBox();
	createFormGroupBox();

	sdb = new DBFasade;

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->setMenuBar(menuBar);
	mainLayout->addWidget(horizontalGroupBox);
	mainLayout->addWidget(formGroupBox);
	setLayout(mainLayout);

	setWindowTitle("Welcome!");

}

RegistrationWindow::~RegistrationWindow()
{
	//delete sdb;
	
	delete menuBar;
	delete horizontalGroupBox;
	delete formGroupBox;
	delete login;
	delete pass;
	delete fileMenu;
	delete exitAction;
}

void RegistrationWindow::createHorizontalGroupBox() 
{
	//слой шапки
	horizontalGroupBox = new QGroupBox;
	QHBoxLayout *layout = new QHBoxLayout;

	horizontalGroupBox->setLayout(layout);
}

void RegistrationWindow::createFormGroupBox() 
{
	formGroupBox = new QGroupBox(tr("Registration: "));
	login = new QLineEdit;
	pass = new QLineEdit;
	confirmPass = new QLineEdit;
	pass->setEchoMode(QLineEdit::Password);
	confirmPass->setEchoMode(QLineEdit::Password);
	
	QFormLayout *layout = new QFormLayout;
	layout->addRow(new QLabel(tr("Login: ")), login);
	layout->addRow(new QLabel(tr("Password: ")), pass);
	layout->addRow(new QLabel(tr("Confirm password: ")), confirmPass);

	QPushButton *enterButton = new QPushButton(tr("Registration"), this);
	QPushButton *gotologin = new QPushButton(tr("Return to log-in"), this);
	connect(enterButton, SIGNAL(clicked()), this, SLOT(on_enterButton_clicked()));
	connect(gotologin, SIGNAL(clicked()), this, SLOT(go_to_loginwindow()));
	layout->addWidget(enterButton);
	layout->addWidget(gotologin);

	formGroupBox->setLayout(layout);


}

void RegistrationWindow::createMenu() 
{
	menuBar = new QMenuBar;

	fileMenu = new QMenu(tr("&Menu"), this);
	exitAction = fileMenu->addAction(tr("&Exit"));
	menuBar->addMenu(fileMenu);

	connect(exitAction, &QAction::triggered, this, &QDialog::accept);
}

void RegistrationWindow::on_enterButton_clicked() 
{
	if (this->pass->text() == this->confirmPass->text()) {

		bool isCorrect = sdb->createUser(this->login->text(), this->pass->text());

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

void RegistrationWindow::go_to_loginwindow()
{
	this->close();
	loginWindow = new LoginWindow;
	loginWindow->show();
}