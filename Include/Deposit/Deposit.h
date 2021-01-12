//Alessandro Trevisan 1221819

#ifndef ASSEGNAMENTO2_DEPOSIT_H
#define ASSEGNAMENTO2_DEPOSIT_H

#include <queue>

#include "Train.h"

class Deposit
{
    public:
        // costruttore di default
        Deposit() = default;

        // utilizzando la coda prioritaria
        void addTrain(const Train& t);

        // ritorna e rimuove il puntatore al treno più veloce per non creare ingorghi nella ferrovia
        // utilizzando la priorità della coda prioritaria
        Train removeTrain();

    private:
        // gestisco con una coda prioritaria di puntatori di classe base.
        // La priorità è stata definita con l'overload dell'operatore < nella classe Train
        std::priority_queue<Train> pq;
};

#endif //ASSEGNAMENTO2_DEPOSIT_H

//Alessandro Trevisan 1221819