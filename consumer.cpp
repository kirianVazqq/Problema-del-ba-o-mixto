#include "consumer.h"
#include <iostream>

Consumer::Consumer(char *buffer, QMutex *mutex, int &maleCount, int &femaleCount,
                   QWaitCondition &condition, bool &finished)
    : buffer(buffer), mutex(mutex), maleCount(maleCount), femaleCount(femaleCount),
    condition(condition), finished(finished) {}

void Consumer::run() {
    while (true) {
        mutex->lock();
        if (finished) {
            mutex->unlock();
            break;
        }

        for (int i = 0; i < 3; ++i) {
            if (buffer[i] != '_') {
                char gender = buffer[i];
                buffer[i] = '_';

                if (gender == 'H') --maleCount;
                else --femaleCount;

                std::cout << "SALE UN/A: " << gender << " [Lavabo: " << buffer << "]" << std::endl;
                break;
            }
        }

        mutex->unlock();
        condition.wakeAll();
    }
}
