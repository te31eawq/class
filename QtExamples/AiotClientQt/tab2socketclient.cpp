#include "tab2socketclient.h"
#include "ui_tab2socketclient.h"

tab2socketclient::tab2socketclient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tab2socketclient)
{
    ui->setupUi(this);
    pSocketCLient = new SocketClient(this);
    ui->pPBsendButton->setEnabled(false);
}

tab2socketclient::~tab2socketclient()
{
    delete ui;
}

void tab2socketclient::on_pPBservConnect_clicked(bool checked)
{
    bool bOK;
    if(checked)
    {
        pSocketCLient->slotConnectToServer(bOK);
        if(bOK)
        {
            ui->pPBservConnect->setText("서버 해제");
            ui->pPBsendButton->setEnabled(true);
        }
    }
    else
    {
        pSocketCLient->slotClosedByServer();
        ui->pPBservConnect->setText("서버 연결");
        ui->pPBsendButton->setEnabled(false);
    }
}
