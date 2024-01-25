#include <QCoreApplication>
#include "producer.h"
#include "consumer.h"
#include <QMutex>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    char buffer[4] = {'_', '_', '_', '\0'};
    QMutex mutex;
    int maleCount = 0;
    int femaleCount = 0;
    QWaitCondition condition;
    bool finished = false;

    Producer producer(buffer, &mutex, maleCount, femaleCount, condition, finished);
    Consumer consumer(buffer, &mutex, maleCount, femaleCount, condition, finished);

    producer.start();
    consumer.start();

    QThread::sleep(10); // Simula durante 10 segundos
    mutex.lock();
    finished = true;
    mutex.unlock();

    condition.wakeAll();

    producer.wait();
    consumer.wait();

    return a.exec();
}
