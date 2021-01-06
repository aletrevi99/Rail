/*
 * Studente: Ghiotto Andrea
 * Matricola: 1216363
 * Corso: Laboratorio di Programmazione
 * Anno: 2°
 * Scuola: Ing. Informatica - UniPd
 * Data di creazione: 29/12/2020
*/

#ifndef ASSEGNAMENTO_2_STATION_H
#define ASSEGNAMENTO_2_STATION_H

#include <iostream>
#include <utility>

class Station{
    
    public:
        //non messo costruttore ed assegnamento di copia
        
        std::string get_Station_name() const {return name;};
        int get_Station_distance() const {return distance;};
        bool get_Station_type() const {return is_Local;};
        bool get_stb1_status() const {return stb1;};
        bool get_stb2_status() const {return stb2;};
        bool get_stb3_status() const {return stb3;};
        bool get_stb4_status() const {return stb4;};
        
        void set_Station_distance(int d) { distance = d;};
        void set_stb1_status(bool s) { stb1 = s;};
        void set_stb2_status(bool s) { stb2 = s;};
        void set_stb3_status(bool s) { stb3 = s;};
        void set_stb4_status(bool s) { stb4 = s;};
    
    protected:
        Station(std::string n, int d, bool loc)
            : name {std::move(n)}, distance {d}, is_Local {loc}, stb1 {true}, stb2 {true}, stb3 {true}, stb4 {true} {};
        //tolto il distruttore
    
    private:
        std::string name;
        int distance;
        bool is_Local;      //is_Local = true -> stazione locale (true = 1, false = 0)
        bool stb1;          //stb -> standard binary, ture  = binario libero
        bool stb2;
        bool stb3;
        bool stb4;
    
};

class Principal_Station : public Station{
    
    public:
        Principal_Station(std::string n, int d)
            : Station(std::move(n), d, false){}
    
};

class Local_Station : public Station{
    
    public:
        Local_Station(std::string n, int d)
            : Station(std::move(n), d, true){}
    
};

#endif //ASSEGNAMENTO_2_STATIONS_H