#include "tab7camsecurity.h"
#include "ui_tab7camsecurity.h"

Tab7CamSecurity::Tab7CamSecurity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab7CamSecurity)
{
    ui->setupUi(this);
    pCameracapture = new Cameracapture(this);
    pCameracapture->pTLcamView = ui->pTLcamView;
    connect(ui->pPBCamView,SIGNAL(clicked(bool)),this, SLOT(slotCamView(bool)));
    connect(ui->pPBsnapShot,SIGNAL(clicked()), this, SLOT(slotSnapShot()));
    connect(ui->pCBsecurityMode,SIGNAL(clicked(bool)), this, SLOT(slotSecurityMode(bool)));
    connect(ui->pCBColorMode,SIGNAL(clicked(bool)), this, SLOT(slotColorMode(bool)));
}

Tab7CamSecurity::~Tab7CamSecurity()
{
    delete ui;
}

void Tab7CamSecurity::slotCamView(bool check)
{
    if(check)       //cam on
    {
        slotSecurityMode(ui->pCBsecurityMode->isChecked());
        ui->pPBCamView->setText("영상 정지");
        if(!pCameracapture->getCamFlag())
        {
            pCameracapture->setCamFlag(true);
            pCameracapture->start();
        }
    }
    else
    {
        pCameracapture->camTimerStartStop(false);
        ui->pPBCamView->setText("영상 보기");
        pCameracapture->setCamFlag(false);
    }
}
void Tab7CamSecurity::slotSnapShot()
{
    if(ui->pPBCamView->isChecked())
        pCameracapture->camSnapshot();
}
void Tab7CamSecurity::slotSecurityMode(bool check)
{
    pCameracapture->camTimerStartStop(check);
}

void Tab7CamSecurity::slotColorMode(bool bCheck)
{
    pCameracapture->colorMode = bCheck;
}
Cameracapture* Tab7CamSecurity::pGetCameracapture()
{
    return pCameracapture;
}
