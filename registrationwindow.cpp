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
	delete sdb;

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
	
	QFormLayout *layout = new QFormLayout;
	layout->addRow(new QLabel(tr("Login: ")), login);
	layout->addRow(new QLabel(tr("Password: ")), pass);

	QPushButton *enterButton = new QPushButton(tr("Registration"), this);
	connect(enterButton, SIGNAL(clicked()), this, SLOT(on_enterButton_clicked()));
	layout->addWidget(enterButton);

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
	bool isCorrect = sdb->createUser(this->login->text(), this->pass->text());

	if (!isCorrect) {
		qDebug() << "Registration is failed! Input correct data!";
	}
	else {
		qDebug() << "Registration is success!";
		//connect(isCorrect, SIGNAL(true), this, SLOT(go_to_loginwindow()));
		LoginWindow loginwindow;
		loginwindow.show();
		this->hide();
	}
}

void RegistrationWindow::go_to_loginwindow()
{}