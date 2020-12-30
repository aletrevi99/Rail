/*
 * @author Giacomo Checchini
 * n.m. 1216347
 */
#include<iostream>
#include<queue>
#include<fstream>
#ifndef ASSEGNAMENTO_2_SCHEDULE_H
#define ASSEGNAMENTO_2_SCHEDULE_H

class Schedule {
   
   public:
   //class constructor
   Schedule(); //controlla la validità dei dati e riempie la coda dei treni con i dati di time tables txt

   void print(); //stampa il contenuto della timetable corretta
   queue<Train> getQueue(); //restituisce la coda dei treni che partono in giornata
   
   private:
   std::queue<Train> q //struttura dati che contiene le varie partenze 
   int size; //quantità di treni in partenza
   bool validityCheck(std::string s); //controlla la validità del percorso del treno 

}

#endif //ASSEGNAMENTO_2_SCHEDULE_H