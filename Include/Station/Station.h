/*
 * Studente: Ghiotto Andrea
 * Matricola: 1216363
 * Corso: Laboratorio di Programmazione
 * Anno: 2°
 * Scuola: Ing. Informatica - UniPd
 * Data di creazione: 29/12/2020
*/

#include <iostream>
#include "Train.h"
#include "Deposit.h"

#ifndef ASSEGNAMENTO_2_STATION_H
#define ASSEGNAMENTO_2_STATION_H

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
        
        void set_Station_distance(int d) {distance = d;};
        void set_stb1_status(bool s) {stb1 = s;};
        void set_stb2_status(bool s) {stb2 = s;};
        void set_stb3_status(bool s) {stb3 = s;};
        void set_stb4_status(bool s) {stb4 = s;};
        
        void add_to_Deposit(Train& t);
        Train remove_from_Deposit(Train& t);
    
    protected:
        Station(std::string n, int d, bool loc)
            : name {n}, distance {d}, is_Local {loc}, stb1 {true}, stb2 {true}, stb3 {true}, stb4 {true} {};
        //tolto il distruttore
    
    private:
        std::string name;
        int distance;
        bool is_Local;      //is_Local = true -> stazione locale (true = 1, false = 0)
        bool stb1;          //stb -> standard binary, true  = binario libero
        bool stb2;
        bool stb3;
        bool stb4;
        Deposit d1;         //deposito prima della stazione - direzione: verso capolinea
        Deposit d2;         //deposito prima della stazione - direzione: verso origine
    
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