#ifndef DIALOG_H
#define DIALOG_H
#include "qdicethread.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT
private:
    QDiceThread threadA;
public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void slot_threadStart();
    void slot_threadStop();
    void slot_getNewValue(int, int);

    void on_startThread_clicked();

    void on_startDice_clicked();

    void on_pauseDice_clicked();

    void on_stopThread_clicked();

    void on_clean_clicked();

private:
    Ui::Dialog *ui;

protected:
    void closeEvent(QCloseEvent *);


};
#endif // DIALOG_H
