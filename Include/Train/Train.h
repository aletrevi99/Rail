//Alessandro Trevisan 1221819

#ifndef ASSEGNAMENTO_2_TRAIN_H
#define ASSEGNAMENTO_2_TRAIN_H

#include <iostream>
#include <vector>

// classe Treno base
class Train
{
    public:
        // getter functions
        int getTrainCode() const;

        int getMaxSpeed() const;

        double getCurrSpeed() const;

        double getDistance() const;

        double getDelay() const;

        bool isDirection() const;

        int getBinary() const;

        bool isStopLocal() const;

        int getType() const;

        std::vector<int> getPath() const;

        int getMinutes() const;

        bool isDeposit() const;

        int getPassedStations() const;

        int getStatus() const;

        int getNextBinary() const;


        // setter functions
        void setCurrSpeed(double cs);

        void setDistance(double d);

        void setBinary(int bin);

        void setPath(std::vector<int> &path);

        void setMinutes(int minutes);

        void setDeposit(bool deposit);

        void setPassedStations(int passedStations);

        void setStatus(int status);

        void setNextBinary(int nextBinary);

        // controlla se questo treno parte prima di t
        bool isFirst(Train& t);

    protected:
        // costruttore
        Train(int tc, bool dir, std::vector<int> p);

        // codice del treno
        int trainCode;
        // velocità di crociera
        double currSpeed;
        // distanza dalla stazione
        double distance;
        // tempo trascorso dalla partenza
        int minutes;
        // ritardo accumulato dal treno
        double delay;
        // true se va da origine a termine, false se va da termine a origine
        bool direction;
        // binario in entrata stazione. 0 se fuori da stazione. 1 a 4 se binari
        int binary;
        // velocità massima del treno: 160km\h regionale; 240km\h alta velocità; 300km\h super alta velocità
        int maxSpeed = 0;
        // variabile per indicare se si ferma nelle stazioni locali (solo i treni regionali)
        bool stopLocal = false;
        // tipologia treno. 1 regionale, 2 alta velocità, 3 super alta velocità
        int type = 0;
        // variabile per indicare se un treno è nel deposito o no
        bool deposit = false;
        // numero stazioni attraversate
        int passedStations = 0;
        // 0 se treno deve partire/arrivare al binario , 1 se deve lasciare il binario, 2 se deve uscire ai 5km, 3 se deve segnalare, 4 se deve entrare ai 5km
        // 5 se treno è arriavto
        int status = 0;
        // vettore degli orari di arrivo
        std::vector<int> path;
        // utile a gestire il caso di due stazioni distanti 20km
        int nextBinary = 0;
};

// overload operatore < per confrontare i treni a seconda della loro velcità
bool operator<(const Train &, const Train &);

// overload operatore << per stampare un treno
std::ostream &operator<<(std::ostream &, const Train &);

// classi Treno derivate
class Regional_Train : public Train
{
    public:
        Regional_Train(int tc, bool dir, const std::vector<int> &p);
};

class High_Speed_Train : public Train
{
    public:
        High_Speed_Train(int tc, bool dir, const std::vector<int> &p);
};

class Super_High_Speed_Train : public Train
{
    public:
        Super_High_Speed_Train(int tc, bool dir, const std::vector<int> &p);
};

#endif //ASSEGNAMENTO_2_TRAIN_H

//Alessandro Trevisan 1221819