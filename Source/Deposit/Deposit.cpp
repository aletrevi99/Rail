//Alessandro Trevisan 1221819

#include "Deposit.h"

// coda prioritaria
void Deposit::addTrain(const Train& t)
{
    pq.push(t);
}

// coda prioritaria
Train Deposit::removeTrain()
{
    Train tmp = pq.top();
    pq.pop();
    return tmp;
}

//Alessandro Trevisan 1221819