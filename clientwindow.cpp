#include "ClientWindow.h"
#include "ui_clientwindow.h"
#include <QDateTime>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

ClientWindow::ClientWindow(int idAccount_, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow),
    idAccount(idAccount_)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    ui->stackedWidget->setCurrentIndex(0);
    tableAddWidth = 780 - ui->stackedWidget->size().width();
    tableAddHeight = 360 - ui->stackedWidget->size().height();
    ui->stackedWidget->setFixedHeight(460);
    ui->stackedWidget->setFixedWidth(780);

    ui->complainsDisplay->setNewestFirst(true);
    ui->complainsDisplay->setShowAllForIdAccont(idAccount);

    updateProductsCodes();
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::updateProductsCodes(){
    ui->productCode_comboBox->clear();

    QSqlQuery query;
    if (!query.exec("select code from products order by code"))
        return;
    else {
        while (query.next()){
            ui->productCode_comboBox->addItem(query.value(0).toString());
        }
    }
}

void ClientWindow::on_sendCompain_pushButton_clicked()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString dateTime = date.toString("yyyy-MM-dd") + " " + time.toString("hh:mm:ss");

    QSqlQuery query;

    int productId = 0;
    if (!query.exec("select id from products where code = '" + ui->productCode_comboBox->currentText() + "'")) {
        ui->statusbar->showMessage("Can not send complain", 4000);
        return;
    }
    if (!query.next()){
        ui->statusbar->showMessage("Type correct product code", 4000);
        return;
    }
    productId = query.value(0).toInt();

    query.prepare("insert into complains (`nr_client`, `nr_product`, `date`, `state`, `description`) "
                            "values (:nr_client, :nr_good, :date, :state, :description)");

    query.bindValue(":nr_client", idAccount);
    query.bindValue(":nr_good", productId);
    query.bindValue(":date", dateTime);
    query.bindValue(":state", "awaiting");
    query.bindValue(":description", ui->description_textEdit->toPlainText());

    if (!query.exec()){
        ui->statusbar->showMessage("Can not send complain", 4000);
    }
    else {
        query.exec("select * from clients where id_account = " + QString::number(idAccount));

        if (!query.size()){
            ui->statusbar->showMessage("Complite your informations!", 4000);
        }
        else {
            ui->statusbar->showMessage("Complain has been sent", 4000);
        }
    }
}

void ClientWindow::on_infoPage_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

    QSqlQuery query;
    bool queryExec = query.exec("select name, last_name, bank_account_number from clients where id_account = "
                                + QString::number(idAccount));

    if (!queryExec){
        ui->statusbar->showMessage("Connection error", 4000);
        return;
    }
    else if (!query.size()){
        ui->statusbar->showMessage("No informations", 4000);
        ui->name_lineEdit->setText("");
        ui->lastName_lineEdit->setText("");
        ui->bankAccount_lineEdit->setText("");
        return;
    }

    query.next();
    ui->name_lineEdit->setText(query.value(0).toString());
    ui->lastName_lineEdit->setText(query.value(1).toString());
    ui->bankAccount_lineEdit->setText(query.value(2).toString());
}

void ClientWindow::on_cancelChanges_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void ClientWindow::on_applyChanges_pushButton_clicked()
{
    QString name = ui->name_lineEdit->text();
    QString lastName = ui->lastName_lineEdit->text();
    QString bankAccount = ui->bankAccount_lineEdit->text();

    QSqlQuery query;
    bool queryExec = query.exec("replace into clients (`id_account`, `name`, `last_name`, `bank_account_number`) values ("
                                + QString::number(idAccount)
                                + ", '" + name + "', '" + lastName + "', '" + bankAccount + "')");

    if (!queryExec){
        ui->statusbar->showMessage("Connection error", 4000);
        return;
    }
    else if (!query.size()){
        ui->statusbar->showMessage("Can not change informations", 4000);
        return;
    }

    ui->statusbar->showMessage("Informations have been changed", 4000);
    ui->stackedWidget->setCurrentIndex(0);
}

void ClientWindow::on_showComplains_pushButton_clicked(){
    this->setFixedWidth(this->size().width() + tableAddWidth);
    this->setFixedHeight(this->size().height() + tableAddHeight);
    ui->stackedWidget->setCurrentIndex(2);
}

void ClientWindow::on_showComplainsBack_pushButton_clicked(){
    this->setFixedWidth(this->size().width() - tableAddWidth);
    this->setFixedHeight(this->size().height() - tableAddHeight);
    ui->stackedWidget->setCurrentIndex(0);
}
