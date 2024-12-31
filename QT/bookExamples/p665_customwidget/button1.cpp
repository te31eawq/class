#include <QApplication>
//#include <QPushButton>
#include "CustomWidget.h"
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
#if 0

    QPushButton *button = new QPushButton("Quit", 0);
    button->resize(80, 35); 		/* 위젯의 크기 설정 */
    button->move(300, 300);		/* 위젯의 위치 설정 */
    button->show(); 			/* 위젯의 화면 표시 */
    QObject::connect(button,SIGNAL(clicked()),&app,SLOT(quit()));
#endif

	CustomWidget *widget = new CustomWidget(0);
	QObject::connect(widget,SIGNAL(widgetClicked()),&app,SLOT(quit()));
	widget->show();

    return app.exec();
}
