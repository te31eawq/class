#include "keyled.h"


KeyLed::KeyLed(QWidget *parent) :
    QWidget(parent)
{
    pFile = new QFile("/dev/ledkey_dev");
    if(!pFile->open(QFile::ReadWrite | QFile::Unbuffered))
    {
        QMessageBox::information(this,"open","open fail : /dev/ledkey_dev");
    }
    keyledFd = pFile->handle(); //file descripter value return
    pKeyLedNotifier = new QSocketNotifier(keyledFd,QSocketNotifier::Read,this); //QSocketNorifier::Read => static value
    connect(pKeyLedNotifier,SIGNAL(activated(int)),this,SLOT(readKeyData(int)));    //Read Event accur call Slot
    writeLedData(0);
}
void KeyLed::readKeyData(int)
{
    char no = 0;
    int ret = pFile->read(&no,sizeof(no));
    if(ret > 0)
        emit updateKeydataSig(int(no));
}

void KeyLed::writeLedData(int no)
{
    char led = (char)no;
    pFile->write(&led, sizeof(led));
}

KeyLed::~KeyLed()
{

}
