#include "tab1devcontrol.h"
#include "ui_tab1devcontrol.h"

Tab1DevControl::Tab1DevControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab1DevControl)
{
    ui->setupUi(this);
    pKeyLed = new KeyLed(this);

    connect(ui->pDialLed,SIGNAL(valueChanged(int)),pKeyLed, SLOT(writeLedData(int)));
}

Tab1DevControl::~Tab1DevControl()
{
    delete ui;
}
