#ifndef TAB3CONTROLPANNEL_H
#define TAB3CONTROLPANNEL_H

#include <QWidget>
#include <QPalette>

namespace Ui {
class Tab3ControlPannel;
}

class Tab3ControlPannel : public QWidget
{
    Q_OBJECT

public:
    explicit Tab3ControlPannel(QWidget *parent = nullptr);
    ~Tab3ControlPannel();

signals:
    void socketSendDataSig(QString);

private slots:
    void on_pPBLamp_clicked(bool checked);
    void on_pPBPlug_clicked(bool checked);
    void tab3RecvDataSlot(QString);

private:
    Ui::Tab3ControlPannel *ui;
    QPalette paletteColorOn;
    QPalette paletteColorOff;
};

#endif // TAB3CONTROLPANNEL_H
