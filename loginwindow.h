#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "clientwindow.h"
#include <QtSql/QSqlDatabase>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::LoginWindow *ui;
    std::vector<QMainWindow*> windows;
    QSqlDatabase db;
};

#endif // LOGINWINDOW_H
