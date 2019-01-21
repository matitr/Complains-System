#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private slots:
    void on_sendCompain_pushButton_clicked();

private:
    Ui::ClientWindow *ui;
    QSqlDatabase db;
};

#endif // CLIENTWINDOW_H
