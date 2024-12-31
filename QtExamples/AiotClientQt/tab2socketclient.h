#ifndef TAB2SOCKETCLIENT_H
#define TAB2SOCKETCLIENT_H

#include <QWidget>
#include "socketclient.h"

namespace Ui {
class tab2socketclient;
}

class tab2socketclient : public QWidget
{
    Q_OBJECT

public:
    explicit tab2socketclient(QWidget *parent = nullptr);
    ~tab2socketclient();

private slots:
    void on_pPBservConnect_clicked(bool checked);

private:
    Ui::tab2socketclient *ui;
    SocketClient *pSocketCLient;
};

#endif // TAB2SOCKETCLIENT_H
