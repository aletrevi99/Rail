//Alessandro Trevisan 1221819

#ifndef ASSEGNAMENTO2_DEPOSIT_H
#define ASSEGNAMENTO2_DEPOSIT_H

#include <queue>

class Deposit
{
    public:
        Deposit() = default;
        ~Deposit() = default;

        // sovraccarico la funzione per aggiungere diversi treni alle diverse code con una singola funzione
        // serve differenziare o venendo tutti da un unico vettore di Train* è inutile?
        void addTrain(Regional_Train* t);
        void addTrain(High_Speed_Train* t);
        void addTrain(Super_High_Speed_Train* t);
        // utilizzando la coda prioritaria
        void addATrain(Train *t);

        // ritorna e rimuove il puntatore al treno più veloce per non creare ingorghi nella ferrovia
        // definendo la priorità in base alle tre code
        Train* removeTrain();
        // ritorna e rimuove il puntatore al treno più veloce per non creare ingorghi nella ferrovia
        // utilizzando la priorità della coda prioritaria
        Train* deleteTrain();

    private:
        // gestisco con tre code normali
        std::queue<Regional_Train*> rq;
        std::queue<High_Speed_Train*> hq;
        std::queue<Super_High_Speed_Train*> sq;
        // gestisco con una coda prioritaria
        std::priority_queue<Train*> pq;
};

#endif //ASSEGNAMENTO2_DEPOSIT_H

//Alessandro Trevisan 1221819