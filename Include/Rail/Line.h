/*
 * Studente: Ghiotto Andrea
 * Matricola: 1216363
 * Corso: Laboratorio di Programmazione
 * Anno: 2°
 * Scuola: Ing. Informatica - UniPd
 * Data di creazione: 30/12/2020
*/

#ifndef ASSEGNAMENTO_2_LINE_H
#define ASSEGNAMENTO_2_LINE_H

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

//#include "Station.h"
//#include "Train.h"
#include "Deposit.h"
#include "Data.h"

class Line{
    
    public:
        Line();                 //costruttore
        ~Line() = default;      //distruttore
        void simulation();      //funzione che simula il funzionamento giornaliero della linea ferroviaria
    
    private:
        std::vector<Station> stations;                  //vettore di oggetti di tipo Station contenente le stazioni della linea ferroviaria
        std::vector<Train> trains;                      //vettore di oggetti di tipo Train contenente i treni della linea ferroviaria
        std::vector<Train> active_trains;               //vettore di oggetti di tipo Train contenente i treni attualmente in viaggio sulla linea ferroviaria
        std::vector<int> principal_distances;           //vettore di int contenente le distanze tra le stazioni principali 
        std::vector<int> reverse_principal_distances;
        Data da;
        int ns;                                 //number of stations
        int nt;                                 //number of trains
        const int CROSSING_TIME = 4;            //tempo per fare 5 km a 80 km/h (approssimato)
        void change_v(Train& t, double v);         //cambia istantaneamente la velocità del treno
        int get_minutes(Train& t, double d);       //quanti minuti ci mette un treno per percorrere una certa distanza
        double get_km(Train& t, double m);            //quanti km percorre un treno in m minuti
        void get_station_binary(Train& t, Station& s, int m, double d);  //comunica al treno il binario in cui fermarsi
        void train_arrival(Train& t, Station& s, int m, double d);                              //velocità treno = 0
        void train_departure(Train& t, Station& s, int m, int position_in_active_trains);       //velocità treno = 80
        void station_entry(Train& t, Station& s, int m, double d);
        void station_exit(Train& t, Station& s, int m, double d);
        void go_trought(Train& t, Station& s, int m);
        void finish(Train& t, Station& s, int m);
        void update_distance(Train& t);
        void update_speed(Train& t);
        int next_Principal_Station(Train& t);
        bool distance_check(Train& t, int position_in_active_trains);
    
};

#endif //ASSEGNAMENTO2_LINE_H