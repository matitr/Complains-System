#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QtSql/QSqlError>

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

    int d=0;
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_clicked()
{
    if (ui->userType_comboBox->currentText() == "Client"){
        QMainWindow* subWindow = new ClientWindow();
        subWindow->show();
        windows.push_back(subWindow);
    }
}

void LoginWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Client"){
        ui->login_lineEdit->setEnabled(false);
        ui->password_lineEdit->setEnabled(false);
    }
    else{
        ui->login_lineEdit->setEnabled(true);
        ui->password_lineEdit->setEnabled(true);
    }
}
