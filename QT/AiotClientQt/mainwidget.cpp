#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    pTab1DevControl = new Tab1DevControl(ui->pTab1);
    ui->pTab1->setLayout(pTab1DevControl->layout()); // adjust size

    pTab2SocketClient = new tab2socketclient(ui->pTab2);
    ui->pTab2->setLayout(pTab2SocketClient->layout());

    ui->pTabWidget->setCurrentIndex(1);

}

MainWidget::~MainWidget()
{
    delete ui;
}
