#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    pQWebEngineView1_1 = new QWebEngineView(this);
    pQWebEngineView1_1->load(QUrl(QStringLiteral("http://10.10.14.60:8080/?action=stream")));
    ui->verticalLayout1->addWidget(pQWebEngineView1_1);

    pQWebEngineView1_2 = new QWebEngineView(this);
    pQWebEngineView1_2->load(QUrl(QStringLiteral("http://10.10.14.48:8080/?action=stream")));
    ui->verticalLayout2->addWidget(pQWebEngineView1_2);

    pQWebEngineView1_3 = new QWebEngineView(this);
    pQWebEngineView1_3->load(QUrl(QStringLiteral("http://10.10.14.48:8080/?action=stream")));
    ui->verticalLayout3->addWidget(pQWebEngineView1_3);

    pQWebEngineView1_4 = new QWebEngineView(this);
    pQWebEngineView1_4->load(QUrl(QStringLiteral("http://10.10.14.48:8080/?action=stream")));
    ui->verticalLayout4->addWidget(pQWebEngineView1_4);

    pQWebEngineView2_1 = new QWebEngineView(this);
    pQWebEngineView2_1->load(QUrl(QStringLiteral("http://www.naver.com")));
    ui->verticalLayout5->addWidget(pQWebEngineView2_1);
}

MainWidget::~MainWidget()
{
    delete ui;
}

