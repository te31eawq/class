#include "mainwidget.h"
#include "ui_mainwidget.h"

mainwidget::mainwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainwidget)
{
    ui->setupUi(this);
    pTabDevControl = new Tab1DevControl(ui->ptab1);
    ui->ptab1->setLayout(pTabDevControl->layout());

    pTabSocketClient = new Tab2SocketClient(ui->ptab2);
    ui->ptab2->setLayout(pTabSocketClient->layout());

    pTabControlPannel = new Tab3ControlPannel(ui->ptab3);
    ui->ptab3->setLayout(pTabControlPannel->layout());

    pTabChartPlot = new Tab4ChartPlot(ui->ptab4);
    ui->ptab4->setLayout(pTabChartPlot->layout());

    pTab5Database = new Tab5Database(ui->ptab5);
    ui->ptab5->setLayout(pTab5Database->layout());

    pTab6WebCamera = new Tab6WebCamera(ui->ptab6);
    ui->ptab6->setLayout(pTab6WebCamera->layout());

    pTab7CamSecurity = new Tab7CamSecurity(ui->ptab7);
    ui->ptab7->setLayout(pTab7CamSecurity->layout());

    ui->pTabWidget->setCurrentIndex(4);

    connect(pTabSocketClient, SIGNAL(ledWriteSig(int)), pTabDevControl->getpKeyLed(), SLOT(writeLedData(int)));
    connect(pTabDevControl, SIGNAL(timeoutDialSignal(int)), pTabSocketClient, SLOT(slotSocketSendDataDial(int)));
    connect(pTabSocketClient, SIGNAL(setDialValueSig(int)), pTabDevControl->getpQDial(), SLOT(setValue(int)));
    connect(pTabControlPannel,SIGNAL(socketSendDataSig(QString)), pTabSocketClient->getpSocketClient(),SLOT(slotSocketSendData(QString)));
    connect(pTabSocketClient, SIGNAL(tab3RecvDataSig(QString)), pTabControlPannel,SLOT(tab3RecvDataSlot(QString)));
    connect(pTabSocketClient, SIGNAL(tab4RecvDataSig(QString)), pTabChartPlot,SLOT(tab4RecvDataSlot(QString)));

    connect(pTabSocketClient, SIGNAL(tab5RecvDataSig(QString)), pTab5Database,SLOT(tab5RecvDataSlot(QString)));

    connect(pTab7CamSecurity->pGetCameracapture(),SIGNAL(sigSocketSendData(QString)),pTabSocketClient->getpSocketClient(),SLOT(slotSocketSendData(QString)));
}

mainwidget::~mainwidget()
{
    delete ui;
}

