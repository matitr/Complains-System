#ifndef QUALITYEMPLOYEEWINDOW_H
#define QUALITYEMPLOYEEWINDOW_H

#include <QMainWindow>

namespace Ui {
class QualityEmployeeWindow;
}

class QualityEmployeeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QualityEmployeeWindow(int idAccount, QWidget *parent = nullptr);
    ~QualityEmployeeWindow();

private slots:
    void on_setState_pushButton_clicked();

private:
    Ui::QualityEmployeeWindow *ui;
    int idAccount;
};

#endif // QUALITYEMPLOYEEWINDOW_H
