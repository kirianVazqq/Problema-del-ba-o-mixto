#include "producer.h"
#include <iostream>
#include <QRandomGenerator>

Producer::Producer(char *buffer, QMutex *mutex, int &maleCount, int &femaleCount,
                   QWaitCondition &condition, bool &finished)
    : buffer(buffer), mutex(mutex), maleCount(maleCount), femaleCount(femaleCount),
    condition(condition), finished(finished) {}

void Producer::run() {
    while (true) {
        mutex->lock();
        if (finished) {
            mutex->unlock();
            break;
        }

        char gender = "HM"[QRandomGenerator::global()->bounded(2)];

        // Espera si el baño está lleno para el género seleccionado
        while ((gender == 'H' && maleCount >= 2) || (gender == 'M' && femaleCount >= 2)) {
            condition.wait(mutex);
        }

        // Encuentra un espacio vacío en el buffer
        for (int i = 0; i < 3; ++i) {
            if (buffer[i] == '_') {
                buffer[i] = gender;
                if (gender == 'H') ++maleCount;
                else ++femaleCount;
                break;
            }
        }

        std::cout << "ENTRA UN/A: " << gender << " [Lavabo: " << buffer << "]" << std::endl;

        mutex->unlock();
        condition.wakeAll();
    }
}
