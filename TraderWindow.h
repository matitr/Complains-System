#ifndef TRADERWINDOW_H
#define TRADERWINDOW_H

#include <QMainWindow>

namespace Ui {
class TraderWindow;
}

class TraderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TraderWindow(int idAccount, QWidget *parent = nullptr);
    ~TraderWindow();

private slots:
    void on_setState_pushButton_clicked();

private:
    Ui::TraderWindow *ui;
    int idAccount;
};

#endif // TRADERWINDOW_H
