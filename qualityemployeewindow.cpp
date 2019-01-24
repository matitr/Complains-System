#include "QualityEmployeeWindow.h"
#include "ui_qualityemployeewindow.h"

#include <QSqlQuery>

QualityEmployeeWindow::QualityEmployeeWindow(int idAccount_, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QualityEmployeeWindow),
    idAccount(idAccount_)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    ui->complainsDisplay->setComplainStatus("in progress");
}

QualityEmployeeWindow::~QualityEmployeeWindow()
{
    delete ui;
}

void QualityEmployeeWindow::on_setState_pushButton_clicked(){
    int complainId = ui->complainsDisplay->getSelectedComplainId();

    QSqlQuery query;
    if (!query.exec("select notes from complains where id = " + QString::number(complainId))){
        ui->statusbar->showMessage("Database connection error", 4000);
    }

    if (query.next()){
        QString notes = query.value(0).toString() + "\n" + ui->notes_textEdit->toPlainText();
        if (!query.exec("update complains set state = '" + ui->state_comboBox->currentText()
                        + "', notes = '" + notes + "' where id = " + QString::number(complainId))){

            ui->statusbar->showMessage("Can not set state", 4000);
        }
    }
    else {
        ui->statusbar->showMessage("Complain does not exists", 4000);
    }

    ui->complainsDisplay->updateDisplay();
}
