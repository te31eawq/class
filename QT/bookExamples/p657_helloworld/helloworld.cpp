#include <QApplication>
#include <QLabel>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QLabel *hello = new QLabel("<font color=blue>Hello <i>World!</i></font>", 0);

	hello->resize(880,135);			/* widget size setting */
	hello->move(300,300);			/* widget location setting */ 
	hello->show();					/* widget screen display */

	return app.exec();				/* Qt event loop start */
}