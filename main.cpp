/*
 * Studente: Ghiotto Andrea
 * Matricola: 1216363
 * Corso: Laboratorio di Programmazione
 * Anno: 2°
 * Scuola: Ing. Informatica - UniPd
 * Data di creazione: 31/12/2020
*/

#include "Rail.h"

using namespace std;
int main(){
    /*
    //stazioni
    vector<Station> stations;
    
    Principal_Station s1 ("Verona Porta Nuova", 0);
    Principal_Station s2 ("Verona Porta Vescovo", 30);
    Local_Station s3 ("San Martino Buon Albergo", 70);
    Local_Station s4 ("Caldiero", 100);
    Principal_Station s5 ("San Bonifacio", 150);
    Local_Station s6 ("Lonigo", 190);
    Local_Station s7 ("Montebello", 230);
    Local_Station s8 ("Altavilla Tavernelle", 260);
    Principal_Station s9 ("Vicenza", 300);
    Local_Station s10 ("Lerino", 330);
    Local_Station s11 ("Grisignano Di Zocco", 360);
    Local_Station s12 ("Mestrino", 400);
    Principal_Station s13 ("Padova", 450);
    
    stations.push_back(s1);
    stations.push_back(s2);
    stations.push_back(s3);
    stations.push_back(s4);
    stations.push_back(s5);
    stations.push_back(s6);
    stations.push_back(s7);
    stations.push_back(s8);
    stations.push_back(s9);
    stations.push_back(s10);
    stations.push_back(s11);
    stations.push_back(s12);
    stations.push_back(s13);
    
    
    //treni
    vector<Train> trains;
    
    vector<int> ot1 = {0, 20, 50, 100};
    vector<int> ot2 = {0, 20, 50, 100};
    vector<int> ot3 = {0, 10};
    vector<int> ot4 = {0, 15};
    vector<int> ot5 = {0, 50};
    vector<int> ot6 = {80};
    vector<int> ot7 = {80};
    vector<int> ot8 = {100};
    vector<int> ot9 = {150};
    vector<int> ot10 = {160};
    
    Regional_Train t1 (1, true, ot1);
    Regional_Train t2 (2, false, ot2);
    High_Speed_Train t3 (3, true, ot3);
    Super_High_Speed_Train t4 (4, true, ot4);
    Regional_Train t5 (5, true, ot5);
    High_Speed_Train t6 (6, false, ot6);
    Regional_Train t7 (7, true, ot7);
    High_Speed_Train t8 (8, true, ot8);
    Super_High_Speed_Train t9 (9, false, ot9);
    Regional_Train t10 (10, false, ot10);
    
    trains.push_back(t1);
    trains.push_back(t2);
    trains.push_back(t3);
    trains.push_back(t4);
    trains.push_back(t5);
    trains.push_back(t6);
    trains.push_back(t7);
    trains.push_back(t8);
    trains.push_back(t9);
    trains.push_back(t10);
    
    
    
    Rail r (stations, trains);
    r.simulation(stations, trains);*/
    
    
    vector<Station> stations;
    vector<Train> trains;
    
    Principal_Station s1 ("Verona P.N.", 0);
    Local_Station s2 ("Verona P.V.", 30);
    Local_Station s3 ("S.M.B. Albergo", 60);
    Local_Station s4 ("Caldiero", 100);
    Principal_Station s5 ("San Bonifacio", 140);
    Local_Station s6 ("Lonigo", 180);
    Local_Station s7 ("Montebello", 220);
    Local_Station s8 ("Altavilla", 250);
    Principal_Station s9 ("Vicenza", 300);
    
    vector<int> ot1 = {0, 13, 31};
    vector<int> ot2 = {10, 26, 47, 71, 95, 119, 143, 164, 192};
    vector<int> ot3 = {0, 18, 36};
    
    High_Speed_Train t1 (1, true, ot1);
    Regional_Train t2 (2, true, ot2);
    High_Speed_Train t3 (3, false, ot3);
    
    stations.push_back(s1);
    stations.push_back(s2);
    stations.push_back(s3);
    stations.push_back(s4);
    stations.push_back(s5);
    stations.push_back(s6);
    stations.push_back(s7);
    stations.push_back(s8);
    stations.push_back(s9);
    
    trains.push_back(t1);
    trains.push_back(t2);
    trains.push_back(t3);
    
    Rail r (stations, trains);
    r.simulation(stations, trains);
    
    
    
    return 0;
}