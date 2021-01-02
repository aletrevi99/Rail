//Alessandro Trevisan 1221819

#include "Train.h"
#include "Deposit.h"


void Deposit::addTrain(const Regional_Train& t)
{
    rq.push(t);
}

void Deposit::addTrain(const High_Speed_Train& t)
{
    hq.push(t);
}

void Deposit::addTrain(const Super_High_Speed_Train& t)
{
    sq.push(t);
}


Train Deposit::removeTrain() // -> decltype(rq.front())
{
    if ( sq.empty() )
    {
        if ( hq.empty() )
        {
            Regional_Train tmp = rq.front();
            rq.pop();
            return (Train)tmp;
        }
        else
        {
            High_Speed_Train tmp = hq.front();
            hq.pop();
            return (Train)tmp;
        }
    }
    else
    {
        Super_High_Speed_Train tmp = sq.front();
        sq.pop();
        return (Train)tmp;
    }
}

// probabilmente si può implememtare fuori da deposit o tramite costruttore passando un train
auto Deposit::getTrain() // -> decltype(removeTrain()).
{
    Train tmp = removeTrain();
    if ( tmp.getType() == 1)
    {
        Regional_Train
    }
    if ( tmp.getType() == 2) return (High_Speed_Train)tmp;
    if ( tmp.getType() == 3) return (Super_High_Speed_Train)tmp;
}

//Alessandro Trevisan 1221819