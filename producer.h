#ifndef PRODUCER_H
#define PRODUCER_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class Producer : public QThread {
public:
    Producer(char *buffer, QMutex *mutex, int &maleCount, int &femaleCount,
             QWaitCondition &condition, bool &finished);

protected:
    void run() override;

private:
    char *buffer; // Asegúrate de que esta declaración esté aquí
    QMutex *mutex;
    int &maleCount;
    int &femaleCount;
    QWaitCondition &condition;
    bool &finished;
};

#endif // PRODUCER_H
