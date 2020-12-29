/*
 * Studente: Ghiotto Andrea
 * Matricola: 1216363
 * Corso: Laboratorio di Programmazione
 * Anno: 2°
 * Scuola: Ing. Informatica - UniPd
 * Data di creazione: 29/12/2020
*/


#include <iostream>

#ifndef ASSEGNAMENTO_2_STATION_H
#define ASSEGNAMENTO_2_STATION_H

class Station{
    
    public:
        Station(const Station&) = delete;
        Station& operator =(const Station&) = delete;
    
    protected:
        Station(std::string n, int d);
        ~Station();
    
    private:
        std::string name;
        int distance;
    
};

#endif //ASSEGNAMENTO_2_STATIONS_H