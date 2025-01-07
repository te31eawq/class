#include "tab5database.h"
#include "ui_tab5database.h"

Tab5Database::Tab5Database(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab5Database)
{
    ui->setupUi(this);
    qSqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    qSqlDatabase.setDatabaseName("aiot.db");
    if(qSqlDatabase.open())
        qDebug() << "succcess DB connection\n";
    else
        qDebug() << "fail DB connection\n";

//    QString strQuery = "CREATE TABLE sensor_tb ("
                    "name VARCHAR(10),"
                    "date DATETIME primary key,"
                    "illu VARCHAR(10))";
    QString strQuery = "CREATE TABLE sensor_tsb ("
                    "name VARCHAR(10),"
                    "date DATETIME primary key,"
                    "illu VARCHAR(10),"
                    "temp VARCHAR(10),"
                    "humi VARCHAR(10))";
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(strQuery))
        ;
    else
        qDebug() << "create table\n";

    illuLine = new QLineSeries(this);
    illuLine->setName("조도");
    tempLine = new QLineSeries(this);
    tempLine->setName("온도");
    humiLine = new QLineSeries(this);
    humiLine->setName("습도");

    QPen pen;
    pen.setWidth(2);
    pen.setBrush(Qt::red);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    illuLine->setPen(pen);
    chart = new QChart();
//   chart->legend()->hide();
    chart->addSeries(illuLine);

    QPen pen2;
    pen2.setWidth(2);
    pen2.setBrush(Qt::blue);
    pen2.setCapStyle(Qt::FlatCap);
    pen2.setJoinStyle(Qt::MiterJoin);
    tempLine->setPen(pen2);
//   chart->legend()->hide();
    chart->addSeries(tempLine);

    QPen pen3;
    pen3.setWidth(2);
    pen3.setBrush(Qt::green);
    pen3.setCapStyle(Qt::FlatCap);
    pen3.setJoinStyle(Qt::MiterJoin);
    humiLine->setPen(pen3);
//   chart->legend()->hide();
    chart->addSeries(humiLine);

//    chart->setTitle("illumination chart");
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, 100);
//    chart->axes(Qt::Horizontal).first()->setRange(0, 24);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->pChartViewLayout->layout()->addWidget(chartView);

    axisX = new QDateTimeAxis;
//    axisX->setFormat("MM-dd hh:mm");
    axisX->setFormat("hh:mm");

    updateLastDateTimeSql(0);

    chartView->chart()->setAxisX(axisX,illuLine);
    chartView->chart()->setAxisX(axisX,tempLine);
    chartView->chart()->setAxisX(axisX,humiLine);

    connect(ui->pPBsearchDb,SIGNAL(clicked()), this, SLOT(searchDbSlot()));
    connect(ui->pPBdeleteDb,SIGNAL(clicked()), this, SLOT(deleteDbSlot()));
}
void Tab5Database::updateLastDateTime(int)
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    firstDate.setDate(date);
    firstDate.setTime(time);

    lastDate.setDate(date);
    QTime tempTime = time.addSecs(60*10);
    lastDate.setTime(tempTime);
    axisX->setRange(firstDate,lastDate);
}
void Tab5Database::updateLastDateTimeSql(int)
{
    int row_count = 0;
    QDateTime from_dateTime = ui->pDateTimeEditFrom->dateTime();
    QString from_strDateTime = from_dateTime.toString("yyyy/MM/dd hh:mm:ss");
    QDateTime to_dateTime = ui->pDateTimeEditTo->dateTime();
    QString to_strDateTime = to_dateTime.toString("yyyy/MM/dd hh:mm:ss");

    QString strQuery = "select * from sensor_tb where date > '" + from_strDateTime + "' AND date < '" + to_strDateTime + "'";
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(strQuery)){

    } else {
//        qDebug() << "select query ok";
        sqlQuery.first();
        firstDate = QDateTime::fromString(sqlQuery.value("date").toString(), "yyyy/MM/dd hh:mm:ss");
        sqlQuery.last();
        lastDate = QDateTime::fromString(sqlQuery.value("date").toString(), "yyyy/MM/dd hh:mm:ss");
    }
    if(!firstDate.isValid())
        firstDate = QDateTime::fromString(from_strDateTime, "yyyy/MM/dd hh:mm:ss");
    if(!lastDate.isValid())
        lastDate = QDateTime::fromString(to_strDateTime, "yyyy/MM/dd hh:mm:ss");
//    qDebug() << firstDate;
//    qDebug() << lastDate;
    axisX->setRange(firstDate,lastDate);
}
void Tab5Database::tab5RecvDataSlot(QString recvData)
{
    qDebug() << "Tab5 " << recvData;
    QDateTime dateTime = QDateTime::currentDateTime();
    QStringList qlist = recvData.split("@");
    QString name = qlist[1];        //id
    QString illu = qlist[3];        //조도
    QString temp = qlist[4];        //온도
    QString humi = qlist[5];        //습도

    QString strQuery = "insert into sensor_tb(name, date,illu,temp,humi) values('" + name + "', '" + dateTime.toString("yyyy/MM/dd hh:mm:ss") + "' , '" + illu +"','" + temp +"','" + humi +"')";
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(strQuery)){
        ;
    } else {
        qDebug() << "insert query ok";
    }
}
void Tab5Database::searchDbSlot()
{
    int row_count = 0;
    QDateTime from_dateTime = ui->pDateTimeEditFrom->dateTime();
    QString from_strDateTime = from_dateTime.toString("yyyy/MM/dd hh:mm:ss");
    QDateTime to_dateTime = ui->pDateTimeEditTo->dateTime();
    QString to_strDateTime = to_dateTime.toString("yyyy/MM/dd hh:mm:ss");

    ui->pTBSensor->clearContents();
    illuLine->clear();
    tempLine->clear();
    humiLine->clear();
    updateLastDateTimeSql(0);

    QString strQuery = "select * from sensor_tb where date > '" + from_strDateTime + "' AND date < '" + to_strDateTime + "'";
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(strQuery)){
        ;
    } else {
//        qDebug() << "select query ok";

        while(sqlQuery.next()) {
            row_count++;
            ui->pTBSensor->setRowCount(row_count);
            QTableWidgetItem * pQTableWidgetItemId = new QTableWidgetItem();
            QTableWidgetItem * pQTableWidgetItemDate = new QTableWidgetItem();
            QTableWidgetItem * pQTableWidgetItemIllu = new QTableWidgetItem();
            QTableWidgetItem * pQTableWidgetItemtemp = new QTableWidgetItem();
            QTableWidgetItem * pQTableWidgetItemhumi = new QTableWidgetItem();

            pQTableWidgetItemId->setText(sqlQuery.value("name").toString());
            pQTableWidgetItemDate->setText(sqlQuery.value("date").toString());
            pQTableWidgetItemIllu->setText(sqlQuery.value("illu").toString());
            pQTableWidgetItemtemp->setText(sqlQuery.value("temp").toString());
            pQTableWidgetItemhumi->setText(sqlQuery.value("humi").toString());

            ui->pTBSensor->setItem(row_count-1,0, pQTableWidgetItemId);
            ui->pTBSensor->setItem(row_count-1,1, pQTableWidgetItemDate);
            ui->pTBSensor->setItem(row_count-1,2, pQTableWidgetItemIllu);
            ui->pTBSensor->setItem(row_count-1,3, pQTableWidgetItemtemp);
            ui->pTBSensor->setItem(row_count-1,4, pQTableWidgetItemhumi);

            QDateTime xValue = QDateTime::fromString(pQTableWidgetItemDate->text(), "yyyy/MM/dd hh:mm:ss");
            illuLine->append(xValue.toMSecsSinceEpoch(),pQTableWidgetItemIllu->text().toInt());
            tempLine->append(xValue.toMSecsSinceEpoch(),pQTableWidgetItemtemp->text().toInt());
            humiLine->append(xValue.toMSecsSinceEpoch(),pQTableWidgetItemhumi->text().toInt());
//            qDebug() << "illu " << pQTableWidgetItemIllu->text().toInt();
        }
        ui->pTBSensor->resizeColumnToContents(0);
        ui->pTBSensor->resizeColumnToContents(1);
        ui->pTBSensor->resizeColumnToContents(2);
        ui->pTBSensor->resizeColumnToContents(3);
        ui->pTBSensor->resizeColumnToContents(4);
    }
}
void Tab5Database::deleteDbSlot()
{
    QDateTime from_dateTime = ui->pDateTimeEditFrom->dateTime();
    QString from_strDateTime = from_dateTime.toString("yyyy/MM/dd hh:mm:ss");
    QDateTime to_dateTime = ui->pDateTimeEditTo->dateTime();
    QString to_strDateTime = to_dateTime.toString("yyyy/MM/dd hh:mm:ss");

    QString strQuery = "delete from sensor_tb where date > '" + from_strDateTime + "' AND date < '" + to_strDateTime + "'";
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(strQuery)){
        ;
    } else {
        qDebug() << "delete query ok";
    }
    ui->pTBSensor->clearContents();
    illuLine->clear();
    tempLine->clear();
    humiLine->clear();

}
Tab5Database::~Tab5Database()
{
    delete ui;
}
