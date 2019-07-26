#include <QApplication>
#include <QPainter>
#include <QTime>
#include <QSplashScreen>
#include <QLabel>

#include "loginwindow.h"
#include "dbsingleton.h"

static const int  LOAD_TIME_MSEC = 3 * 1000;
static const int  PROGRESS_X_PX = 262;
static const int  PROGRESS_Y_PX = 399;
static const int  PROGRESS_WIDTH_PX = 316;
static const int  PROGRESS_HEIGHT_PX = 44;

int main(int argc, char *argv[]) 
{
	QApplication app(argc, argv);

	QPixmap pix(":loadScreen.png");
	QSplashScreen *splashScreen = new QSplashScreen(pix);
	splashScreen->show();

	app.processEvents();

	QTime time;
	time.start();

	while (time.elapsed() < LOAD_TIME_MSEC) {
		const int progress = static_cast<double>(time.elapsed()) / LOAD_TIME_MSEC * 100.0;
		splashScreen->showMessage(QObject::trUtf8("Loaded: %1%").arg(progress), Qt::AlignBottom | Qt::AlignRight);


		QPainter painter;
		painter.begin(&pix);

		painter.fillRect(PROGRESS_X_PX, PROGRESS_Y_PX,
			progress / 100.0 * PROGRESS_WIDTH_PX,
			PROGRESS_HEIGHT_PX, Qt::red);


		painter.end();

		splashScreen->setPixmap(pix);
		app.processEvents();
	}

	LoginWindow loginwindow;
	loginwindow.show();

	splashScreen->finish(&loginwindow);

	return app.exec();
}