#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include "mainwindow.h"
#include "dbfasade.h"

MainWindow::MainWindow()
{
	createMenu();

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->setMenuBar(menuBar);
	setLayout(mainLayout);

	setWindowTitle(tr("Home Accounting"));
}

MainWindow::~MainWindow() {}

void MainWindow::createMenu()
{
	menuBar = new QMenuBar;

	fileMenu = new QMenu(tr("&Programm"), this);
	exitAction = fileMenu->addAction(tr("&Exit"));
	menuBar->addMenu(fileMenu);

	connect(exitAction, &QAction::triggered, this, &QDialog::accept);

}
