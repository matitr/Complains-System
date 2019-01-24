#include "LoginWindow.h"
#include "QualityEmployeeWindow.h"
#include "TraderWindow.h"
#include "ui_loginwindow.h"
#include <QtSql/QSqlError>
#include <QSqlQuery>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

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
        ui->statusBar->showMessage("Database is open", 3000);
    else
        ui->statusBar->showMessage("Database error!", 3000);

    QMainWindow *window = new TraderWindow(4);
    window->show();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    bool queryExec = query.exec("select id from accounts where binary login = '" + ui->login_lineEdit->text()
               + "' and binary password = '" + ui->password_lineEdit->text() + "'");

    if (!queryExec){
        ui->statusBar->showMessage("Connection error", 4000);
        return;
    }
    else if (!query.size()){
        ui->statusBar->showMessage("Incorrect login or password", 4000);
        return;
    }

    query.next();
    QString idAccount = query.value(0).toString();

    bool queryExecFindPermission = query.exec("select * from permissions where id_account = "
                   + idAccount + " and permission = '" + ui->userType_comboBox->currentText() + "'");

    if (!queryExecFindPermission){
        ui->statusBar->showMessage("Connection error", 4000);
        return;
    }
    else if (!query.size()){
        ui->statusBar->showMessage("You do not have permission to this group!", 4000);
        return;
    }

    QMainWindow* subWindow = nullptr;
    if (ui->userType_comboBox->currentText() == "Client"){
        subWindow = new ClientWindow(idAccount.toInt());
    }
    else if (ui->userType_comboBox->currentText() == "Trader"){
        subWindow = new TraderWindow(idAccount.toInt());
    }
    else if (ui->userType_comboBox->currentText() == "Quality employee"){
        subWindow = new QualityEmployeeWindow(idAccount.toInt());
    }

    subWindow->show();
    windows.push_back(subWindow);
}
