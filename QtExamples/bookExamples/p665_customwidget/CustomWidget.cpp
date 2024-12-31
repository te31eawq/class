#include <QApplication>
#include <QPushButton>
#include "CustomWidget.h"

CustomWidget::CustomWidget(QWidget* parent) : QWidget(parent)
{
	QPushButton *button = new QPushButton("Quit", this);
	button->resize(120,35);
	button->move(180,250);

	this->resize(300,300);
	move(300,300);

	//connect(button,SIGNAL(clicked()),qApp, SLOT(quit()));
//	connect(button,SIGNAL(clicked()),SIGNAL(widgetClicked()));
	connect(button,SIGNAL(clicked()),this,SLOT(processClick()));

}

void CustomWidget::processClick()
{
	emit widgetClicked();
}

