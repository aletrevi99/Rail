//Alessandro Trevisan 1221819

#include "Train.h"

Train::Train(int tc, int ms)
        : trainCode{tc}, maxSpeed{ms}
{
    if (maxSpeed == 160) stopLocal = true;
    else stopLocal = false;

    currSpeed = 0;
    distance = 0;
    delay = 0;
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

//Alessandro Trevisan 1221819