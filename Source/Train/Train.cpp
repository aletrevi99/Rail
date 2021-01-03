//Alessandro Trevisan 1221819

#include "Train.h"


Train::Train(int tc, bool dir, const std::vector<int>& p)
        : trainCode{tc}, direction{dir}, path{p}, currSpeed{0}, distance{0}, delay{0}, binary{0}
{ }

Regional_Train::Regional_Train(int tc, bool dir, const std::vector<int>& p) : Train(tc, dir, p)
{
    maxSpeed = 160;
    stopLocal = true;
    type = 1;
}

High_Speed_Train::High_Speed_Train(int tc, bool dir, const std::vector<int>& p) : Train(tc, dir, p)
{
    maxSpeed = 240;
    type = 2;
}

Super_High_Speed_Train::Super_High_Speed_Train(int tc, bool dir, const std::vector<int>& p) : Train(tc, dir, p)
{
    maxSpeed = 300;
    type = 3;
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

int Train::getType() const
{
    return type;
}

const std::vector<int> &Train::getPath() const
{
    return path;
}

void Train::setPath(const std::vector<int> &p)
{
    path = p;
}

bool operator<(const Train& t1, const Train& t2)
{
    return t1.getType() < t2.getType();
}

//Alessandro Trevisan 1221819