#ifndef CONSUMER_H
#define CONSUMER_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class Consumer : public QThread {
public:
    Consumer(char *buffer, QMutex *mutex, int &maleCount, int &femaleCount,
             QWaitCondition &condition, bool &finished);

protected:
    void run() override;

private:
    char *buffer;
    QMutex *mutex;
    int &maleCount;
    int &femaleCount;
    QWaitCondition &condition;
    bool &finished;
};

#endif // CONSUMER_H
