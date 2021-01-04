//Alessandro Trevisan 1221819

#include "Train.h"
#include "Deposit.h"

// tre code code starnard specializzate
void Deposit::addTrain(Regional_Train *t)
{
    rq.push(t);
}

void Deposit::addTrain(High_Speed_Train *t)
{
    hq.push(t);
}

void Deposit::addTrain(Super_High_Speed_Train *t)
{
    sq.push(t);
}

// coda prioritaria
void Deposit::addATrain(Train *t)
{
    pq.push(t);
}

// coda prioritaria
Train *Deposit::deleteTrain()
{
    Train *tmp = pq.top();
    pq.pop();
    return tmp;
}

// tre code standard specializzate
Train *Deposit::removeTrain()
{
    if (sq.empty())
    {
        if (hq.empty())
        {
            Regional_Train *tmp = rq.front();
            rq.pop();
            return tmp;
        } else
        {
            High_Speed_Train *tmp = hq.front();
            hq.pop();
            return tmp;
        }
    } else
    {
        Super_High_Speed_Train *tmp = sq.front();
        sq.pop();
        return tmp;
    }
}

//Alessandro Trevisan 1221819