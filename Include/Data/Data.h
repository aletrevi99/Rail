/*
 * @author Giacomo Checchini
 * n.m. 1216347
 */

#ifndef ASSEGNAMENTO_2_DATA_H
#define ASSEGNAMENTO_2_DATA_H

#include <vector>
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <iterator>
#include <algorithm>

#include "Train.h"
#include "Station.h"

class Data
{
    public:
        //class constructor
        Data(); //controlla la validità dei dati e riempie i contenitori con i treni e le stazioni

        void print(); //stampa il contenuto della timetable corretta
        //std::vector<Train*> getTrainsReference() const; //restituisce la dei treni che partono in giornata
        //std::vector<Station*> getStationsReference() const; //restituisce un vettore con le stazioni
        std::vector<Train> getTrains() const;

        std::vector<Station> getStation() const;

        std::vector<int> getDistances(bool reverse) const;

        std::vector<int> getPrincipalDistances(bool reverse) const;

    private:
        std::vector<Train> tr; //struttura dati che contiene i treni in partenza
        std::vector<Station> st; //struttura dati che contiene le stazioni
        int number_of_principal_stations;
        int number_of_local_stations;
        int number_of_regional_trains;
        int number_of_highspeed_trains;
        int number_of_superhighspeed_trains;
        std::vector<int> distances;
        std::vector<int> principal_distances;
        bool flag;

        void readStations(); //legge le stazioni dal file line_description.txt e le salva in st
        void readTrains();  //legge i treni dal file timetables.txt e li salva in tr
        void pathChecker(std::vector<int> &p, int t, int dir);
};

#endif //ASSEGNAMENTO_2_DATA_H