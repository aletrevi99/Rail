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
    
    /* La funzione add_to_Deposit() permette di aggiungere, usufruendo della funzione addTrain() della classe Deposit, un treno al deposito.
     * Nello specifico, se il treno viaggia dalla stazione di origine verso il capolinea, viene aggiunto al deposito d1,
     * altrimenti, viene aggiunto al deposito d2 (situato dopo la stazione se si procede da st. di origine a capolinea). */
    
    if(t.isDirection()){
        d1.addTrain(t);
    }else{
        d2.addTrain(t);
    }
}

Train Station::remove_from_Deposit(Train& t){
    
    /* La funzione remove_from_Deposit() permette di rimuovere un treno dal deposito.
     * Il treno t passato come parametro serve per sapere se rimuovere dal deposito d1 (dir.: origine - capolinea) oppure se
     * rimuovere dal deposito d2 (dir.: capolinea - origine).
     * La funzione restituisce, usufruendo della funzione removeTrain() della classe Deposit, il treno che ha più priorità presente
     * all'interno del singolo deposito. */
    
    if(t.isDirection()){
        return d1.removeTrain();
    }else{
        return d2.removeTrain();
    }
}