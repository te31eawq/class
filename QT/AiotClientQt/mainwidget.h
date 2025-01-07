#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "tab1devcontrol.h"
#include "tab2socketclient.h"
#include "tab3controlpannel.h"
#include "tab4chartplot.h"
#include "tab5database.h"
#include "tab6webcamera.h"
#include "tab7camsecurity.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainwidget; }
QT_END_NAMESPACE

class mainwidget : public QWidget
{
    Q_OBJECT

public:
    mainwidget(QWidget *parent = nullptr);
    ~mainwidget();

private:
    Ui::mainwidget *ui;
    Tab1DevControl *pTabDevControl;
    Tab2SocketClient *pTabSocketClient;
    Tab3ControlPannel *pTabControlPannel;
    Tab4ChartPlot *pTabChartPlot;
    Tab5Database *pTab5Database;
    Tab6WebCamera *pTab6WebCamera;
    Tab7CamSecurity *pTab7CamSecurity;
};
#endif // MAINWIDGET_H
