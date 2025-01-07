#include "tab6webcam.h"
#include "ui_tab6webcam.h"

Tab6WebCam::Tab6WebCam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab6WebCam)
{
    ui->setupUi(this);
}

Tab6WebCam::~Tab6WebCam()
{
    delete ui;
}
