#ifndef KEYLED_H
#define KEYLED_H

#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <QSocketNotifier>

class KeyLed : public QWidget
{
    Q_OBJECT

public:
    explicit KeyLed(QWidget *parent = nullptr);     // explicit: 형을 지정하지 않고 자동으로 형 변환하는 명령어
    ~KeyLed();

private:
    QFile * pFile;
    int keyledFd;
    QSocketNotifier * pKeyLedNotifier;
private slots:
    void readKeyData(int);
public slots:
    void writeLedData(int);

signals:
    void updateKeydataSig(int);
};

#endif // KEYLED_H
