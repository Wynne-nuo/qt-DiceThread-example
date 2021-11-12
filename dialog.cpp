#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Dice");
    connect(&threadA, SIGNAL(started()),this,SLOT(slot_threadStart()));
    connect(&threadA,SIGNAL(finished()),this, SLOT(slot_threadStop()));
    connect(&threadA,SIGNAL(signal_newValue(int,int)),this, SLOT(slot_getNewValue(int,int)));
}

Dialog::~Dialog()
{
    delete ui;
}

//开始线程
void Dialog::slot_threadStart()
{
    ui->label->setText("Thread状态: thread start");
}

//停止线程
void Dialog::slot_threadStop()
{
    ui->label->setText("Thread状态: thread stop");
}

//接收到新色子值，显示在plaintext内
void Dialog::slot_getNewValue(int seq, int value)
{
    QString str = QString::asprintf("第%d次掷色子，点数为：%d",seq,value);
    ui->plainTextEdit->appendPlainText(str);
}

////启动线程按钮
//void Dialog::on_pushButton_clicked()
//{
//    threadA.start();

//}

//启动线程按钮
void Dialog::on_startThread_clicked()
{
    threadA.start();
    ui->startThread->setEnabled(false);
    ui->stopThread->setEnabled(true);
    ui->startDice->setEnabled(true);
    ui->pauseDice->setEnabled(false);
}

//开始按钮
void Dialog::on_startDice_clicked()
{
    threadA.diceBegin();
    ui->startThread->setEnabled(false);
    ui->stopThread->setEnabled(false);
    ui->startDice->setEnabled(false);
    ui->pauseDice->setEnabled(true);
}

//暂停色子
void Dialog::on_pauseDice_clicked()
{
    threadA.dicePause();
    ui->startThread->setEnabled(false);
    ui->stopThread->setEnabled(true);
    ui->startDice->setEnabled(true);
    ui->pauseDice->setEnabled(false);
}

//停止线程
void Dialog::on_stopThread_clicked()
{
    threadA.stopThread();
    threadA.wait();
    ui->startThread->setEnabled(true);
    ui->stopThread->setEnabled(false);
    ui->startDice->setEnabled(false);
    ui->pauseDice->setEnabled(false);
}

//清空文本
void Dialog::on_clean_clicked()
{
    ui->plainTextEdit->clear();
}

//重写关闭按钮，确保窗口关闭后线程停止
void Dialog::closeEvent(QCloseEvent *e)
{
    if(threadA.isRunning()){
        threadA.stopThread();
        threadA.wait();
    }
    e->accept();
}
