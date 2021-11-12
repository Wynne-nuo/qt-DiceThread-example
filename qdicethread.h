#ifndef QDICETHREAD_H
#define QDICETHREAD_H

#include <QObject>
#include <QThread>

class QDiceThread : public QThread
{
    Q_OBJECT
public:
//    explicit QDiceThread(/*QObject *parent = nullptr*/);
private:
    int m_seq = 0;//投掷次数
    int m_diceValue;// 色子点数
    bool m_pause = true;//暂停
    bool m_stop = false;//停止

protected:
    void run() Q_DECL_OVERRIDE;

public:
    QDiceThread();
    void diceBegin();//开始掷色子
    void dicePause();//暂停掷色子
    void stopThread();//结束线程

signals:
    void signal_newValue(int seq, int diceValue);

};

#endif // QDICETHREAD_H
