//Alessandro Trevisan 1221819

#include "Train.h"

#include <utility>

// cosrtuttori
Train::Train(int tc, bool dir, std::vector<int> p)
        : trainCode{tc}, direction{dir}, path{std::move(p)}, currSpeed{0.0}, distance{0.0}, minutes{0}, delay{0.0}, binary{0}
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

std::vector<int> Train::getPath() const
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

int Train::getTrainCode() const
{
    return trainCode;
}

int Train::getMaxSpeed() const
{
    return maxSpeed;
}

double Train::getCurrSpeed() const
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

int Train::getStatus() const
{
    return status;
}

int Train::getNextBinary() const
{
    return nextBinary;
}

int Train::getStops() const
{
    return stops;
}

double Train::getNextSpeed() const
{
    return nextSpeed;
}

// setter functions
void Train::setCurrSpeed(double cs)
{
    if (cs < 0)
        throw std::length_error("La velocita' di crociera non puo' essere negativa. Imposta un valore positivo.\n");
    else if (cs > maxSpeed)
        throw std::length_error(
                "La velocita' di crociera non puo' essere maggiore di quella massima. Imposta un valore coerente con il tipo di treno.\n");
    else
        currSpeed = cs;
}

void Train::setDistance(double d)
{
    if (d < 0)
        throw std::length_error(
                "La distanza del treno dalla stazione d'origine non puo' essere negativa. Imposta un valore positivo.\n");
    else
        distance = d;
}

void Train::setBinary(int bin)
{
    if (bin < 0 || bin > 5)
        throw std::length_error("Il binario selezionato non esiste. Imposta un binario fra 0 e 5, estremi compresi.\n");
    else
        binary = bin;
}

void Train::setPath(std::vector<int> &p)
{
    if (p.empty())
        throw std::invalid_argument("Il vettore degli orari di arrivo risulta vuoto. Riempilo.\n");
    else
        path = p;
}

void Train::setMinutes(int min)
{
    if (min < 0)
        throw std::length_error(
                "Il tempo trascorso dalla partenza non puo' essere negativo. Imposta un valore positivo.\n");
    else
        minutes = min;
}

void Train::setDeposit(bool dep)
{
    deposit = dep;
}

void Train::setPassedStations(int ps)
{
    if (ps < 0)
        throw std::length_error("Il numero della stazioni passate non puo' essere negativo. Imposta un valore positivo.\n");
    else
        passedStations = ps;
}

void Train::setStatus(int st)
{
    if (st < 0 || st > 6)
        throw std::length_error("Lo stato del treno immesso non esiste. Imposta lo stato da 0 a 6, estremi compresi.\n");
    status = st;
}

void Train::setNextBinary(int nb)
{
    nextBinary = nb;
}

void Train::setNextSpeed(double ns)
{
    nextSpeed = ns;
}

void Train::setStops(int s)
{
    stops = s;
}


bool Train::isFirst(Train& t)
{
    return ((path[0]) < (t.getPath()[0]));
}

// overload operatori
bool operator<(const Train &t1, const Train &t2)
{
    return t1.getType() < t2.getType();
}

std::ostream &operator<<(std::ostream &os, const Train &obj)
{
   os << obj.getTrainCode()<<" ";
   int dir = 0;
   if(!obj.isDirection())
      dir = 1;
   os << dir << " ";
   os << obj.getType() <<" ";
   std::vector<int> tmp = obj.getPath();
   for(int i : tmp)
      os << i <<" ";
   
   
   /*
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
    if (obj.getDelay() == 0) os << "è in orario.\n";
   */
    return os;
}

//Alessandro Trevisan 1221819