/*
 * Studente: Ghiotto Andrea
 * Matricola: 1216363
 * Corso: Laboratorio di Programmazione
 * Anno: 2°
 * Scuola: Ing. Informatica - UniPd
 * Data di creazione: 30/12/2020
*/

#include <iostream>
#include <vector>
#include <queue>

//#include "Station.h"
//#include "Train.h"
#include "Deposit.h"
#include "Data.h"

class Rail{
    
    public:
        Rail();
        ~Rail() = default;
        void simulation();
    
    private:
        std::vector<Station> stations;
        std::vector<Train> trains;
        std::vector<Train> active_trains;
        Data da;
        int ns;                                 //number of stations
        int nt;                                 //number of trains
        const int CROSSING_TIME = 4;            //tempo per fare 5 km a 80 km/h (approssimato)
        void change_v(Train& t, int v);         //cambia istantaneamente la velocità del treno
        int get_minutes(Train& t, double d);       //quanti minuti ci mette un treno per percorrere una certa distanza
        double get_km(Train& t, double m);            //quanti km percorre un treno in m minuti
        void get_station_binary(Train& t, Station& s, int m, int d);  //comunica al treno il binario in cui fermarsi
        void train_arrival(Train& t, Station& s, int m, int d);           //velocità treno = 0
        void train_departure(Train& t, Station& s, int m);                //velocità treno = 80
        void station_entry(Train& t, Station& s, int m, int d);
        void station_exit(Train& t, Station& s, int m, int d);
        void go_trought(Train& t, Station& s, int m);
        void finish(Train& t, Station& s, int m);
        void update_distance(Train& t);
        void update_speed(Train& t);
        int next_Principal_Station(Train& t);
    
};