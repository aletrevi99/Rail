/*
 * Studente: Ghiotto Andrea
 * Matricola: 1216363
 * Corso: Laboratorio di Programmazione
 * Anno: 2°
 * Scuola: Ing. Informatica - UniPd
 * Data di creazione: 30/12/2020
*/

#ifndef ASSEGNAMENTO_2_RAIL_H
#define ASSEGNAMENTO_2_RAIL_H

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iterator>
#include <algorithm>

#include "Station.h"
#include "Train.h"
#include "Deposit.h"
#include "Data.h"

class Rail{
    
    public:
        Rail(std::vector<Station> s, std::vector<Train> t);
        ~Rail() = default;
        void simulation(std::vector<Station>& st, std::vector<Train>& t);
    
    private:
        int ns;                                 //number of stations
        int nt;                                 //number of trains
        const int CROSSING_TIME = 4;            //tempo per fare 5 km a 80 km/h (approssimato)
        void change_v(Train& t, int v);         //cambia istantaneamente la velocità del treno
        int get_minutes(Train& t, double d);       //quanti minuti ci mette un treno per percorrere una certa distanza
        int get_km(Train& t, double m);            //quanti km percorre un treno in m minuti
        void get_station_binary(Train& t, Station& s);  //comunica al treno il binario in cui fermarsi
        void train_arrival(Train& t, Station& s);           //velocità treno = 0
        void train_departure(Train& t);         //velocità treno = 80
        void station_entry(Train& t, Station& s);
        void station_exit(Train& t, Station& s);
};

#endif //ASSEGNAMENTO_2_RAIL_H