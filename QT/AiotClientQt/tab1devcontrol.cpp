#include "tab1devcontrol.h"
#include "ui_tab1devcontrol.h"

Tab1DevControl::Tab1DevControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab1DevControl)
{
    ui->setupUi(this);
    arrCnt = sizeof(pQCheckBoxArray)/sizeof(pQCheckBoxArray[0]);
    itemCnt = arrCnt-1;
    pKeyLed = new KeyLed(this);
    pQTimer = new QTimer(this);

    pQButtonGroup = new QButtonGroup(this);
    for(int i=0;i<ui->pGridLayoutKey->rowCount();i++)
    {
        for(int j=0;j<ui->pGridLayoutKey->columnCount();j++)
        {
            pQCheckBoxArray[itemCnt--] = dynamic_cast<QCheckBox*>(ui->pGridLayoutKey->itemAtPosition(i,j)->widget());
        }
    }
    for(int i =0;i<8;i++)
    {
        pQButtonGroup->addButton(pQCheckBoxArray[i],0x01 << i);
    }
    pQButtonGroup->setExclusive(false);
    connect(pQButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(keyCheckKeyboardSlot(int)));
    connect(pQTimer, SIGNAL(timeout()), this, SLOT(setValueDialSlot()));
    connect(ui->pDialLed,SIGNAL(valueChanged(int)),pKeyLed, SLOT(writeLedData(int)));
    connect(pKeyLed,SIGNAL(updateKeydataSig(int)),this,SLOT(keyCheckBoxSlot(int)));


}

Tab1DevControl::~Tab1DevControl()
{
//    ui->pDialLed->setValue(0);
    pKeyLed->writeLedData(0);
    delete ui;
}

void Tab1DevControl::on_pPBQuit_clicked()
{
    qApp->quit();
}

void Tab1DevControl::on_pPBtimerStart_clicked(bool checked)
{
    if(checked)
    {
        QString strValue = ui->pCBtimerValue->currentText();
        pQTimer->start(strValue.toInt());
        ui->pPBtimerStart->setText("TimerStop");
    }
    else
    {
        ui->pPBtimerStart->setText("TimerStart");
        pQTimer->stop();

    }
}

void Tab1DevControl::setValueDialSlot()
{
    int dialValue = ui->pDialLed->value();
    if(dialValue >= ui->pDialLed->maximum())
        dialValue = 0;
    else
        dialValue++;
    ui->pDialLed->setValue(dialValue);
}

void Tab1DevControl::on_pCBtimerValue_currentTextChanged(const QString &arg1)
{
    if(pQTimer->isActive())
    {
        pQTimer->stop();
        pQTimer->start(arg1.toInt());
    }
}

void Tab1DevControl::keyCheckBoxSlot(int key)
{
//    qDebug() << "key : " << key;
    lcdData ^= key;
    ui->pLcdNumberKey->display(lcdData);
    pKeyLed->writeLedData(lcdData);


//    QCheckBox *pQCheckBox[8] ={ui->pCBKey1,ui->pCBKey2,ui->pCBKey3,ui->pCBKey4,ui->pCBKey5,ui->pCBKey6,ui->pCBKey7,ui->pCBKey8};

    for(int i=0;i<arrCnt;i++)
    {
        if(key == 0x01 << i)
        {
            if(pQCheckBoxArray[i]->isChecked())
                pQCheckBoxArray[i]->setChecked(false);
            else
                pQCheckBoxArray[i]->setChecked(true);
        }
    }
}

void Tab1DevControl::keyCheckKeyboardSlot(int keyno)
{
//    qDebug() << "keyno : " << keyno;
    lcdData ^= keyno;
    ui->pLcdNumberKey->display(lcdData);
    pKeyLed->writeLedData(lcdData);
}
