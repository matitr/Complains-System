#ifndef COMPLAINSDISPLAY_H
#define COMPLAINSDISPLAY_H

#include <QTableWidget>
#include <QWidget>

namespace Ui {
class ComplainsDisplay;
}

class ComplainsDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit ComplainsDisplay(QWidget *parent = nullptr);
    ~ComplainsDisplay();

    void setComplainStatus(QString status) { complainStatus = status; updateTable(); }
    void setShowAllForIdAccont(int id) { idAccount = id; showAllForId = true; updateTable(); }
    void setNewestFirst(bool n) { newestFirst = n; updateTable(); }
    int getSelectedComplainId() { return selectedComplainId; }

    void updateDisplay();

private slots:
    void on_tableWidget_itemSelectionChanged();

private:
    Ui::ComplainsDisplay *ui;

    QString complainStatus;
    int idAccount = -1;
    bool showAllForId = false;
    bool newestFirst = false;

    int selectedComplainId = -1;

    QTimer *timer = nullptr;

    void updateTable();
};

#endif // COMPLAINSDISPLAY_H
