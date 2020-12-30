//Alessandro Trevisan 1221819

#include <Train.h>
#include "Deposit.h"

Deposit::Deposit() = default;

void Deposit::addTrain(const Regional_Train& t)
{
    pq.push(t);
}

Regional_Train Deposit::removeTrain() const
{
    //oppure fare tre code distinte o anche una per i regionali e l'altra per gli alta velocità
    return pq.top();
}
