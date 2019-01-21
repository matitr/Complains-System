#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QDateTime>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    ui->idGood_lineEdit->setValidator( new QIntValidator(0, 1000000, this) );
    ui->clientNumber_lineEdit->setValidator( new QIntValidator(0, 1000000, this) );

    db = QSqlDatabase::addDatabase("QMYSQL");
    bool v = db.isValid();
    db.setHostName("127.0.0.1");
    db.setDatabaseName("returns_database");
    db.setUserName("user");
    db.setPassword("user");
    db.setPort(3306);
    bool o = db.open();
    QSqlError localLastError = db.lastError();

    if (db.open())
        ui->statusbar->showMessage("Database is open", 3000);
    else
        ui->statusbar->showMessage("Database error!", 3000);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::on_sendCompain_pushButton_clicked()
{
    if (!db.open()){
        ui->statusbar->showMessage("Database error!");
        return;
    }

    QDate date = QDate::currentDate();
    QString dateStr = date.toString("yyyy-MM-dd");

    QSqlQuery query;
    query.prepare("insert into complains (`nr_client`, `nr_good`, `date`, `condition`, `description`) "
                            "values (:nr_client, :nr_good, :date, :condition, :description)");

    query.bindValue(":nr_client", ui->clientNumber_lineEdit->text().toInt());
    query.bindValue(":nr_good", ui->idGood_lineEdit->text().toInt());
    query.bindValue(":date", dateStr);
    query.bindValue(":condition", ui->condition_lineEdit->text());
    query.bindValue(":description", ui->description_textEdit->toPlainText());

    if (query.exec()){
        ui->statusbar->showMessage("Complain has been sent", 4000);
    }
    else
        ui->statusbar->showMessage("Can not send complain", 4000);
}
