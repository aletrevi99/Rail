//Alessandro Trevisan 1221819

#include "Train.h"

Train::Train(int tc, int ms, bool dir)
        : trainCode{tc}, maxSpeed{ms}, direction{dir}, currSpeed{0}, distance{0}, delay{0}, binary{0}
{
    if (maxSpeed == 160) stopLocal = true;
    else stopLocal = false;
}

int Train::getTrainCode() const
{
    return trainCode;
}

int Train::getMaxSpeed() const
{
    return maxSpeed;
}

int Train::getCurrSpeed() const
{
    return currSpeed;
}

double Train::getDistance() const
{
    return distance;
}

bool Train::isStopLocal() const
{
    return stopLocal;
}

void Train::setCurrSpeed(int cs)
{
    if (cs > maxSpeed)
        currSpeed = maxSpeed;

    if (cs < 0)
        currSpeed = 0;

    currSpeed = cs;
}

void Train::setDistance(double d)
{
    if (d < 0)
        distance = 0;

    // if (d > maxDistance)
    //     d = maxDistance;

    distance = d;
}

double Train::getDelay() const
{
    return delay;
}

bool Train::isDirection() const
{
    return direction;
}

int Train::getBinary() const
{
    return binary;
}

void Train::setBinary(int bin)
{
    binary = bin;
}

bool operator<(const Train& t1, const Train& t2)
{
    return (int)t1.isStopLocal() < (int)t2.isStopLocal();
}

//Alessandro Trevisan 1221819