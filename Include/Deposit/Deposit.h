//Alessandro Trevisan 1221819

#ifndef ASSEGNAMENTO2_DEPOSIT_H
#define ASSEGNAMENTO2_DEPOSIT_H

#include <queue>

class Deposit
{
    public:
        Deposit();
        ~Deposit() = default;

        void addTrain(const Regional_Train& t); // oppure fare una funzione template per i tre treni.
        Regional_Train removeTrain() const; // oppure fare una funzione template per i tre treni.
        std::priority_queue<Regional_Train> pq;
    private:

};

#endif //ASSEGNAMENTO2_DEPOSIT_H

//Alessandro Trevisan 1221819
