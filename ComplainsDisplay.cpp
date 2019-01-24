#include "ComplainsDisplay.h"
#include "ui_complainsdisplay.h"

#include <QItemSelectionModel>
#include <QSqlQuery>
#include <QTimer>

ComplainsDisplay::ComplainsDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComplainsDisplay)
{

    ui->setupUi(this);
    int columnWidth = 60;
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Custom);
    ui->tableWidget->setColumnWidth(0, columnWidth);
    ui->tableWidget->setColumnWidth(1, columnWidth);
    ui->tableWidget->setColumnWidth(2, columnWidth);
    ui->tableWidget->setColumnWidth(3, columnWidth * 3);
    ui->tableWidget->setColumnWidth(4, columnWidth * 2);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    timer = new QTimer(parent);
    QObject::connect(timer, &QTimer::timeout, this, [this]{ updateTable(); });
    timer->start(5000); // ms

    updateTable();

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->verticalHeader()->hide();
    //QObject::connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), SLOT(selectedRowChanged(int)));
    QObject::connect(ui->tableWidget->selectionModel(), SIGNAL(ui->tableWidget->selectionModel()->currentRowChanged(const QModelIndex &, const QModelIndex &)),
                     this, SLOT(selectedRowChanged(const QModelIndex &, const QModelIndex &)));
}

ComplainsDisplay::~ComplainsDisplay()
{
    delete ui;
}

void ComplainsDisplay::updateTable(){
    QSqlQuery query;

    query.exec("SELECT count(*) FROM information_schema.columns WHERE table_name = 'complains'");
    if (!query.next()){
        return;
    }

    int columnsNumber = query.value(0).toInt();

    QString queryStr = showAllForId ? "  select * from complains where nr_client = "
                                      + QString::number(idAccount) + " order by date"
              : "  select * from complains where state = '" + complainStatus + "' order by date";

    if (newestFirst)
        queryStr += " desc";

    bool queryExec = query.exec(queryStr);

    ui->tableWidget->setRowCount(query.size());
    int row = 0;

    while (query.next()) {
        for (int col = 0; col < columnsNumber; col++){
            QTableWidgetItem* tableItem = new QTableWidgetItem();
            //tableItem->setFlags(~(Qt::ItemIsEditable));
            ui->tableWidget->setItem(row, col, tableItem);
            ui->tableWidget->item(row, col)->setText(query.value(col).toString());
        }
        row++;
    }
}

void ComplainsDisplay::updateDisplay(){
    QSqlQuery query;
    if (!query.exec("select C.name, C.last_name, C.bank_account_number, "
                    "P.code, P.name, P.price, P.weight, "
                    "Complain.state, Complain.description "
                    "from clients C, products P, complains Complain "
                    "where C.id_account = Complain.nr_client and P.id = Complain.nr_product and "
                    "Complain.id = " + QString::number(selectedComplainId))){

        return;
    }

    if (!query.next())
        return;

    ui->clientName_label->setText(query.value(0).toString());
    ui->clientLastName_label->setText(query.value(1).toString());
    ui->clientBankNumber_label->setText(query.value(2).toString());
    ui->productCode_label->setText(query.value(3).toString());
    ui->productName_label->setText(query.value(4).toString());
    ui->productPrice_label->setText(query.value(5).toString());
    ui->productWeight_label->setText(query.value(6).toString());
    ui->state_label->setText(query.value(7).toString());
    ui->description_textEdit->setText(query.value(8).toString());
}

void ComplainsDisplay::on_tableWidget_itemSelectionChanged()
{
    int row = ui->tableWidget->selectedItems().at(0)->row();
    ui->tableWidget->selectRow(row);
    selectedComplainId = ui->tableWidget->item(row, 0)->text().toInt();
    updateDisplay();
}
