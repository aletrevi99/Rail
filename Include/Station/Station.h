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
        
        std::string get_Station_name() const {return name;};        //fornisce il nome della stazione
        int get_Station_distance() const {return distance;};        //fornisce la distanza della stazione dalla stazione di origine
        bool get_Station_type() const {return is_Local;};           //fornisce il tipo di una stazione
        bool get_stb1_status() const {return stb1;};                //fornisce lo stato del binario 1
        bool get_stb2_status() const {return stb2;};                //fornisce lo stato del binario 2
        bool get_stb3_status() const {return stb3;};                //fornisce lo stato del binario 3
        bool get_stb4_status() const {return stb4;};                //fornisce lo stato del binario 4
        
        void set_Station_distance(int d) {distance = d;};           //permette di settare la distanza di una stazione
        void set_stb1_status(bool s) {stb1 = s;};                   //permette di settare lo stato del binario 1
        void set_stb2_status(bool s) {stb2 = s;};                   //permette di settare lo stato del binario 2
        void set_stb3_status(bool s) {stb3 = s;};                   //permette di settare lo stato del binario 3
        void set_stb4_status(bool s) {stb4 = s;};                   //permette di settare lo stato del binario 4
        
        void add_to_Deposit(Train& t);                              //aggiunge il treno t al deposito
        Train remove_from_Deposit(Train& t);                        //rimuove un treno dal deposito
    
    protected:
        //costruttore
        Station(std::string n, int d, bool loc)
            : name {n}, distance {d}, is_Local {loc}, stb1 {true}, stb2 {true}, stb3 {true}, stb4 {true} {};
    
    private:
        std::string name;       //nome della stzione
        int distance;           //distanza della stazione dall'origine
        bool is_Local;          //tipo della stazione, is_Local = true -> stazione locale, altrimenti è una stazione principale
        bool stb1;              //stb -> standard binary, true = binario libero, altrimenti il binario è occupato. Direzone: da st. origine a capolinea
        bool stb2;              //stb -> standard binary, true = binario libero, altrimenti il binario è occupato. Direzone: da st. origine a capolinea
        bool stb3;              //stb -> standard binary, true = binario libero, altrimenti il binario è occupato. Direzone: da capolinea a st. origine
        bool stb4;              //stb -> standard binary, true = binario libero, altrimenti il binario è occupato. Direzone: da capolinea a st. origine
        Deposit d1;             //deposito prima della stazione - direzione: da stazione di origine a capolinea
        Deposit d2;             //deposito prima della stazione - direzione: da capolinea a stazione di origine
    
};


//classi derivate della classe Station e rispettivi costruttori

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