// Alessandro Trevisan 1221819

#ifndef ASSEGNAMENTO_2_STATION_H
#define ASSEGNAMENTO_2_STATION_H

#include <iostream>
#include <utility>

#include "Train.h"
#include "Deposit.h"

class Station
{
    public:
        // getter functions
        std::string getStationName() const;

        int getStationDistance() const;

        bool isLocal() const;

        bool isStb1Status() const;

        bool isStb2Status() const;

        bool isStb3Status() const;

        bool isStb4Status() const;

        // setter functions
        void setStationDistance(int d);

        void setStb1Status(bool s);

        void setStb2Status(bool s);

        void setStb3Status(bool s);

        void setStb4Status(bool s);

        // aggiunge il treno t al deposito
        void addToDeposit(Train &t);

        // rimuove un treno dal deposito
        Train removeFromDeposit(Train &t);

    protected:
        // costruttore
        Station(std::string n, int d, bool loc);

    private:
        // nome della stzione
        std::string nameStation;
        // distanza della stazione dall'origine
        int stationDistance;
        // tipo della stazione, type = true -> stazione locale, altrimenti è una stazione principale
        bool type;
        // stb -> standard binary, true = binario libero, altrimenti il binario è occupato. Direzone: da st. origine a capolinea
        bool stb1;
        // stb -> standard binary, true = binario libero, altrimenti il binario è occupato. Direzone: da st. origine a capolinea
        bool stb2;
        // stb -> standard binary, true = binario libero, altrimenti il binario è occupato. Direzone: da capolinea a st. origine
        bool stb3;
        // stb -> standard binary, true = binario libero, altrimenti il binario è occupato. Direzone: da capolinea a st. origine
        bool stb4;
        // deposito prima della stazione - direzione: da stazione di origine a capolinea
        Deposit d1;
        // deposito prima della stazione - direzione: da capolinea a stazione di origine
        Deposit d2;
};


// classi Station derivate
class Principal_Station : public Station
{
    public:
        Principal_Station(std::string n, int d);
};

class Local_Station : public Station
{
    public:
        Local_Station(std::string n, int d);
};

#endif //ASSEGNAMENTO_2_STATIONS_H

// Alessandro Trevisan 1221819