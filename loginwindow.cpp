#include "loginwindow.h"
#include "dbfasade.h"
#include "registrationwindow.h"

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

	sdb = new DBFasade;

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
	pass = new QLineEdit;

	QFormLayout *layout = new QFormLayout;
	layout->addRow(new QLabel(tr("Login: ")), login);
	layout->addRow(new QLabel(tr("Password: ")), pass);

	QPushButton *enterButton = new QPushButton(tr("Sign-IN"), this);
	QPushButton *registrButton = new QPushButton(tr("Create new User"), this);
	connect(enterButton, SIGNAL(clicked()), this, SLOT(on_enterButton_clicked()));
	connect(registrButton, SIGNAL(clicked()), this, SLOT(on_registrButton_clicked()));
	//enterButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
	layout->addWidget(enterButton);
	layout->addWidget(registrButton);

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
	bool isCorrect = sdb->authRequest(this->login->text(), this->pass->text());

	if (!isCorrect) {
		qDebug() << "Auth is failed! Input correct data!";
	}
	else {
		qDebug() << "Auth is success!";
		//переход на main форму
	}
}

void LoginWindow::on_registrButton_clicked()
{
	this->close();
	registrwindow = new RegistrationWindow;
	registrwindow->show();

}

LoginWindow::~LoginWindow() {
	
	
	delete sdb;

	delete menuBar;
	delete formGroupBox;
	delete horizontalGroupBox;
	delete login;
	delete pass;
	delete fileMenu;
	delete exitAction;
}