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
	QFormLayout *layout = new QFormLayout;
	layout->addRow(new QLabel(tr("Login: ")), new QLineEdit);
	layout->addRow(new QLabel(tr("Password: ")), new QLineEdit);

	QPushButton *enterButton = new QPushButton(tr("Sign-IN"), this);
	connect(enterButton, SIGNAL(released()), this, SLOT(authRequest()));
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

void LoginWindow::authRequest()
{}

LoginWindow::~LoginWindow() {}