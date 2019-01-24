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
    explicit ClientWindow(int idAccount, QWidget *parent = nullptr);
    ~ClientWindow();

private slots:
    void on_sendCompain_pushButton_clicked();

    void on_infoPage_pushButton_clicked();

    void on_cancelChanges_pushButton_clicked();

    void on_applyChanges_pushButton_clicked();

    void on_showComplains_pushButton_clicked();

    void on_showComplainsBack_pushButton_clicked();

private:
    Ui::ClientWindow *ui;
    int idAccount;
    int tableAddWidth;
    int tableAddHeight;

    void updateProductsCodes();
};

#endif // CLIENTWINDOW_H
