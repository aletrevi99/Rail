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

        // sovraccarico la funzione per aggiungere diversi treni alle diverse code con una singola funzione
        // serve differenziare o venendo tutti da un unico vettore di Train* è inutile?
        // void addTrain(Regional_Train t);

        // void addTrain(High_Speed_Train t);

        // void addTrain(Super_High_Speed_Train t);

        // utilizzando la coda prioritaria
        void addTrain(const Train& t);

        // ritorna e rimuove il puntatore al treno più veloce per non creare ingorghi nella ferrovia
        // definendo la priorità in base alle tre code standard specializzate
        // Train deleteTrain();

        // ritorna e rimuove il puntatore al treno più veloce per non creare ingorghi nella ferrovia
        // utilizzando la priorità della coda prioritaria
        Train removeTrain();


        // distruttore di defult
        ~Deposit() = default;

    private:
        // gestisco il deposito con tre code normali specializzate per tipologia di treno
        // std::queue<Regional_Train> rq;
        // std::queue<High_Speed_Train> hq;
        // std::queue<Super_High_Speed_Train> sq;
        // gestisco con una coda prioritaria di puntatori di classe base.
        // La priorità è stata definita con l'overload dell'operatore < nella classe Train
        std::priority_queue<Train> pq;
};

#endif //ASSEGNAMENTO2_DEPOSIT_H

//Alessandro Trevisan 1221819