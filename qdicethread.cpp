#include "qdicethread.h"
#include <QTime>

//QDiceThread::QDiceThread(/*QObject *parent*/) : QThread(parent)
//{

//}

QDiceThread::QDiceThread(){

}

void QDiceThread::run()
{
    m_stop = false;
    m_seq = 0;
    qsrand(QTime::currentTime().msec());
    while (!m_stop) {
        if(!m_pause){
            m_diceValue = qrand();
            m_diceValue = (m_diceValue % 6) + 1;
            m_seq++;
            emit signal_newValue(m_seq, m_diceValue);
        }
        msleep(1000);
    }
    quit();
}

void QDiceThread::diceBegin()
{
    m_pause = false;
}

void QDiceThread::dicePause()
{
    m_pause = true;
}

void QDiceThread::stopThread()
{
    m_stop = true;
}
