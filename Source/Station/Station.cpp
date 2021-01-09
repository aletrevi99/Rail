/*
 * Studente: Ghiotto Andrea
 * Matricola: 1216363
 * Corso: Laboratorio di Programmazione
 * Anno: 2°
 * Scuola: Ing. Informatica - UniPd
 * Data di creazione: 07/01/2020
*/

#include "Station.h"

void Station::add_to_Deposit(Train& t){
    if(t.isDirection()){
        d1.addTrain(t);
    }else{
        d2.addTrain(t);
    }
}

Train Station::remove_from_Deposit(Train& t){
    if(t.isDirection()){
        return d1.removeTrain();
    }else{
        return d2.removeTrain();
    }
}