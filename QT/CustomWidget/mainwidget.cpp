#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
//    , ui(new Ui::MainWidget)
{
    QPushButton *button = new QPushButton("Quit", this);
//    ui->setupUi(this);
    this->resize(220,400);
    this->move(300,300);
    button->resize(120,35);
    button->move(30,30);

    connect(button, SIGNAL(clicked()), qApp,SLOT(quit()));
}

MainWidget::~MainWidget()
{
}

