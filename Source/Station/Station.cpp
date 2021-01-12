// Alessandro Trevisan 1221819

#include "Station.h"

// costruttori
Station::Station(std::string n, int d, bool loc)
        : nameStation{std::move(n)}, stationDistance{d}, type{loc}, stb1{true}, stb2{true}, stb3{true}, stb4{true}
{}

Principal_Station::Principal_Station(std::string n, int d) : Station(std::move(n), d, false)
{}

Local_Station::Local_Station(std::string n, int d) : Station(std::move(n), d, true)
{}

// getter functions
std::string Station::getStationName() const
{
    return nameStation;
}

int Station::getStationDistance() const
{
    return stationDistance;
}

bool Station::isLocal() const
{
    return type;
}

bool Station::isStb1Status() const
{
    return stb1;
}

bool Station::isStb2Status() const
{
    return stb2;
}

bool Station::isStb3Status() const
{
    return stb3;
}

bool Station::isStb4Status() const
{
    return stb4;
}

// setter functions
void Station::setStationDistance(int d)
{
    stationDistance = d;
}

void Station::setStb1Status(bool s)
{
    stb1 = s;
}

void Station::setStb2Status(bool s)
{
    stb2 = s;
}

void Station::setStb3Status(bool s)
{
    stb3 = s;
}

void Station::setStb4Status(bool s)
{
    stb4 = s;
}


void Station::addToDeposit(Train &t)
{
    if (t.isDirection())
        d1.addTrain(t);
    else
        d2.addTrain(t);
}

Train Station::removeFromDeposit(Train &t)
{
    if (t.isDirection())
        return d1.removeTrain();
    else
        return d2.removeTrain();
}

// Alessandro Trevisan 1221819