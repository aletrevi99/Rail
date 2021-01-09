/*
 * @author Giacomo Checchini
 * n.m. 1216347
 */

#include <vector>
#include <stdexcept>
#include <string>
#include <sstream> 
#include <fstream>
#include <cmath>
#include <algorithm>
#include "Train.h"
#include "Station.h"
#ifndef ASSEGNAMENTO_2_DATA_H
#define ASSEGNAMENTO_2_DATA_H

class Data {
   
   public:
   //class constructor
   Data(); //controlla la validità dei dati e riempie i vettori da usare nella classe Rail con i treni e le stazioni prese dai file input

   void print(); //stampa il contenuto della timetable corretta
   
   std::vector<Train>& getTrains();
   std::vector<Station>& getStation();
   std::vector<Station>& get_reversed_Station();
   
   
   private:
   std::vector<Train> tr; //struttura dati che contiene i treni in partenza
   std::vector<Station> st; //struttura dati che contiene le stazioni
   std::vector<Station> rev_st; //struttura dati che contiene le stazioni in ordine invertito
   int number_of_principal_stations;
   int number_of_local_stations;
   int number_of_regional_trains;
   int number_of_highspeed_trains;
   int number_of_superhighspeed_trains;
   std::vector<int> distances;  //vettore contenente le distanze tra le stazioni
   std::vector<int> principal_distances;  //vettore contenente le distanze tra le stazioni principali
   
   bool flag;  //variabile che indica se timetable ha subito modifche
   
   void readStations(); //legge le stazioni dal file line_description.txt e le salva in st
   void readTrains();  //legge i treni dal file timetables.txt e li salva in tr con gli orari corretti
   void pathChecker(std::vector<int>& p, int t,int dir); //funzione che controlla la veridicità del percorso da inserire
   void sort();  //funzione che ordina il vector tr a seconda dell'orario di partenza dei treni. da sx a dx si hanno orari crescenti.
};

#endif //ASSEGNAMENTO_2_DATA_H