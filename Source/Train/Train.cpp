//Alessandro Trevisan 1221819

#include "Train.h"

// cosrtuttori
Train::Train(int tc, bool dir, const std::vector<int> &p)
        : trainCode{tc}, direction{dir}, path{p}, currSpeed{0}, distance{0}, minutes{0}, delay{0}, binary{0}
{}

Regional_Train::Regional_Train(int tc, bool dir, const std::vector<int> &p) : Train(tc, dir, p)
{
    maxSpeed = 160;
    stopLocal = true;
    type = 1;
}

High_Speed_Train::High_Speed_Train(int tc, bool dir, const std::vector<int> &p) : Train(tc, dir, p)
{
    maxSpeed = 240;
    type = 2;
}

Super_High_Speed_Train::Super_High_Speed_Train(int tc, bool dir, const std::vector<int> &p) : Train(tc, dir, p)
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

// getter functions
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

int Train::getType() const
{
    return type;
}

const std::vector<int> &Train::getPath() const
{
    return path;
}

int Train::getMinutes() const
{
    return minutes;
}

bool Train::isDeposit() const
{
    return deposit;
}

int Train::getPassedStations() const
{
    return passedStations;
}

// setter functions
void Train::setBinary(int bin)
{
    if (bin < 1 || bin > 4)
        throw std::length_error("Binanario non esitente.\n");
    else
        binary = bin;
}

void Train::setPath(const std::vector<int> &p)
{
    if (p.empty())
        throw std::invalid_argument("Vettore degli orari di arrivo vuoto.\n");
    else
        path = p;
}

void Train::setMinutes(int min)
{
    if (min < 0)
    minutes = min;
}

void Train::setDeposit(bool dep)
{
    deposit = dep;
}

void Train::setPassedStations(int ps)
{
    passedStations = ps;
}


bool operator<(const Train &t1, const Train &t2)
{
    return t1.getType() < t2.getType();
}

std::ostream &operator<<(std::ostream &os, const Train &obj)
{
    os << "Il treno ";
    if (obj.getType() == 1) os << "Regionale ";
    if (obj.getType() == 2) os << "Alta Velocità ";
    if (obj.getType() == 3) os << "Super Alta Velocità ";
    os << obj.getTrainCode() << "partito da " << obj.getMinutes() << "  minuti ";
    if (obj.isDirection())
        os << "dalla stazione di Origine (distante " << obj.getDistance() << "m) diretto al Capolinea, ";
    if (!obj.isDirection())
        os << "dalla stazione di Capolinea (distante " << obj.getDistance() << "m) diretto all'Origine, ";
    if (obj.isDeposit()) os << "si trova nel deposito ";
    if (obj.getBinary() == 1 || obj.getBinary() == 3) os << "viaggia a " << obj.getCurrSpeed() << "km/h nel binario 1 ";
    if (obj.getBinary() == 2 || obj.getBinary() == 4) os << "viaggia a " << obj.getCurrSpeed() << "km/h nel binario 2 ";
    if (obj.getDelay() >= 0) os << "è in ritardo di " << obj.getDelay() << " minuti.";
    if (obj.getDelay() == 0) os << "è in orario.";

    return os;
}

//Alessandro Trevisan 1221819