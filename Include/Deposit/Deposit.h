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
        void addTrain(const Regional_Train& t);
        void addTrain(const High_Speed_Train& t);
        void addTrain(const Super_High_Speed_Train& t);

        // ritorna e rimuove il treno (rendendolo temporaneamente generico) più veloce per non creare ingorghi nella ferrovia
        Train removeTrain();

        // cast esplicito del treno appena espulso dal deposito al suo tipo originale
        // auto getTrain();

    private:
        std::queue<Regional_Train> rq;
        std::queue<High_Speed_Train> hq;
        std::queue<Super_High_Speed_Train> sq;
};

#endif //ASSEGNAMENTO2_DEPOSIT_H

//Alessandro Trevisan 1221819