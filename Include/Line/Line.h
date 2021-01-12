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
        std::vector<Station> reverse_stations;          //vettore di oggetti di tipo Station contenente le stazioni della linea ferroviaria, rovesciate
        std::vector<Train> trains;                      //vettore di oggetti di tipo Train contenente i treni della linea ferroviaria
        std::vector<Train> active_trains;               //vettore di oggetti di tipo Train contenente i treni attualmente in viaggio sulla linea ferroviaria
        std::vector<int> principal_distances;           //vettore di int contenente le distanze tra le stazioni principali (dir.: da st. origine a capolinea)
        std::vector<int> reverse_principal_distances;   //vettore di int contenente le distanza tra le stazioni principali (dir.: da capolinea a st. origine)
        Data da;                                        //oggetto di tipo data
        int ns;                                         //numero di stazioni presenti nella linea ferroviaria
        int nt;                                         //numero di treni presenti nella linea ferroviaria
        int time;                                       //munero di cicli massimi che farà la funzione simulation, corrisponde all'orari di arrivo dell'ultimo treno
        double get_km(Train& t, double m);                                                      //calcola quanti km percorre un treno in m minuti
        void get_station_binary(Train& t, Station& s, int m, double d);                         //segnalazione di un treno ai -20km da una stazione
        void train_arrival(Train& t, Station& s, int m, double d);                              //arrivo di un treno in una stazione
        void train_departure(Train& t, Station& s, int m, int position_in_active_trains);       //partenza di un treno da una stazione
        void station_entry(Train& t, Station& s, int m, double d);                              //entrata di un treno nei binari di una stazione (-5km dalla stazione)
        void station_exit(Train& t, Station& s, int m, double d);                               //uscita di un treno dai binari di una stazione (+5km dalla stazione)
        void go_trought(Train& t, Station& s, int m);                                           //treno "passa oltre" una stazione (senza fermarsi)
        void finish(Train& t, Station& s, int m);                                               //un treno conclude la sua corsa
        void update_distance(Train& t);                                                         //aggiornamento delle distaamze percorse dai singoli treni
        void update_speed(Train& t);                                                            //aggiornamento delle velocità dei singoli treni
        int next_Principal_Station(Train& t);                                                   //indica la prossima stazione principale che un treno incontra
        bool distance_check(Train& t, int position_in_active_trains);                           //controlla che i treni non abbiano una distanza tra di loro inferiore ai 10km
        void check10km(Train& t);
};

#endif //ASSEGNAMENTO2_LINE_H