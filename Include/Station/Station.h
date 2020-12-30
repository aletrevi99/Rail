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
        
        std::string get_Station_name() const {return name;};
        int get_Station_distance() const {return distance;};
        bool get_Station_type() const {return is_Local;};
        
    
    protected:
        Station(std::string n, int d, bool loc)
            : name {n}, distance {d}, is_Local {loc}, st1 {true}, st2 {true}, st3 {true}, st4 {true} {}
        ~Station() = default;
    
    private:
        std::string name;
        int distance;
        bool is_Local;      //is_Local = true -> stazione locale (true = 1, false = 0)
        bool st1;
        bool st2;
        bool st3;
        bool st4;
    
};

class Principal_Station : public Station{
    
    public:
        Principal_Station(std::string n, int d)
            : Station(n, d, false){}
    
};

class Local_Station : public Station{
    
    public:
        Local_Station(std::string n, int d)
            : Station(n, d, true){}
    
};

#endif //ASSEGNAMENTO_2_STATIONS_H