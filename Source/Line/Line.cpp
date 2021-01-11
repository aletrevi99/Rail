/*
 * Studente: Ghiotto Andrea
 * Matricola: 1216363
 * Corso: Laboratorio di Programmazione
 * Anno: 2°
 * Scuola: Ing. Informatica - UniPd
 * Data di creazione: 30/12/2020
*/

#include "Line.h"

using namespace std;

Line::Line(){
    
    /* Costruttore della linea ferroviaria.
     * Vengono utilizzate le funzioni getStation() e getTrains() della classe Data per salvare stazioni e treni letti dai file timetables.txt e 
     * line_description.txt nelle variabili stations e trains. Vengono settate ns e nt alle dimensioni rispettivamente di stations e trains.
     * Vengono inoltre riempiti principal_distances e reverse_principal_distances con i valori della distanze tra le varie stazioni. */
    
    stations = da.getStation();
    trains = da.getTrains();
    
    ns = stations.size();
    nt = trains.size();
    
    principal_distances = da.getPrincipalDistances();
    reverse_principal_distances = principal_distances;
    reverse(reverse_principal_distances.begin(), reverse_principal_distances.end());
    
}

double Line::get_km(Train& t, double m){
    
    /* La funzione get_km() calcola quanti km percorre un treno, alla sua attuale velocità di crociera, in un dato intervallo
     * di tempo, identificato dal parametro m che viene fornito. */
    
    double k;
    k = (t.getCurrSpeed()*(m/60));
    return k;
}

void Line::get_station_binary(Train& t, Station& s, int m, double d){
    
    /* La funzione get_station_binary() gestisce la segnalazione che un treno fa alla stazione successiva quando si trova a -20km di distanza da essa.
     * Se lo stato del treno è 3 (ovvero coerente con la prossima azione che il treno deve "compiere", la segnalazione appunto) e se il treno si
     * trova ai -20km dalla stazione, la stazione gestisce la richiesta inviatagli dal treno indicando ad esso il binario su cui transitare e fermarsi,
     * oppure lo avvisa che sarà necessario sostare nel deposito nel caso i binari siano già occupati.
     * Il parametro m che viene passato indica il minuto in cui viene chiamata la funzione, mentre d indica la distanza percorsa dal treno fino al minuto
     * precedente e viene usata, confrontandola con la distanza attuale, per verificare se il treno si trova alla distanza giusta da cui segnalare. */
    
    bool p = false;
    if(((s.get_Station_distance() - d) >= 20) && ((s.get_Station_distance() - t.getDistance()) <= 20)){
        p = true;
    }
    if(t.getStatus() == 3 && (p || (t.getDistance() == 0))){
        
        /* Se il treno non è un treno regionale e la stazione è una stazione locale, il treno non entra nei binari di quella stazione, continua a viaggiare
         * nei binari di transito e non si ferma in quella stazione. */
         
        if((!(t.isStopLocal())) && (s.get_Station_type())){
            t.setBinary(0);
            go_trought(t, s, m);
        }else{
            
            /* Se il treno viaggia dalla stazione di origine verso il capolinea, viene verificata la disponibilità dei binari 1 e 2. Se uno dei due binari è
             * libero, viene comunicato al treno come binario su cui fermarsi, altrimenti il treno dovrà entra nel deposito d1. */
            
            if(t.isDirection()){
                if(s.get_stb1_status()){
                    t.setBinary(1);
                }else{
                    if(s.get_stb2_status()){
                        t.setBinary(2);
                    }else{
                        t.setBinary(5);     //binari occupati, al deposito!
                        s.add_to_Deposit(t);
                    }
                }
            }else{
                
                /* Se il treno viaggia dal capolinea verso la stazione di origine, viene verificata la disponibilità dei binari 3 e 4. Se uno dei due binari è
                 * libero, viene comunicato al treno come binario su cui fermarsi, altrimenti il treno dovrà entra nel deposito d2. */
                 
                if(s.get_stb3_status()){
                    t.setBinary(3);
                }else{
                    if(s.get_stb4_status()){
                        t.setBinary(4);
                    }else{
                        t.setBinary(5);     //binari occupati, al deposito!
                        s.add_to_Deposit(t);
                    }
                }
            }
            cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " avvisa la stazione di " << s.get_Station_name() << ". Bin.: " << t.getBinary() << ".\n";
            t.setStatus(4);         //next step: entrare nei binari di una stazione (ai -5km da essa)
        }
    }
}

void Line::train_arrival(Train& t, Station& s, int m, double d){
    
    /* La funzione train_arrival() gestisce l'arrivo di un treno in una stazione.
     * Se lo stato del treno è 0 (ovvero coerente con la prossima azione che il treno deve "compiere", l'arrivo in una stazione appunto) e se il treno è
     * arrivato alla stazione, esso si ferma alla stazione per la salita/discesa dei passeggeri.
     * Il parametro m che viene passato indica il minuto in cui viene chiamata la funzione, mentre d indica la distanza percorsa dal treno fino al minuto
     * precedente e viene usata, confrontandola con la distanza attuale, per verificare se il treno è effettivamente arrivato alla stazione. */ 
    
    bool p = false;
    if(s.get_Station_distance() - d >= 0 && s.get_Station_distance() - t.getDistance() <= 0){
        p = true;
    }
    if(t.getStatus() == 0 && p){
        
        //Se il treno è arrivato alla stazione, viene aggiornata la distanza che ha percorso ponendola uguale alla distanza della stazione.
        t.setDistance(s.get_Station_distance());
        
        /* Se il treno deve ancora partire, viene "virtualmente" fatto arrivare al binario della stazione e segnala alla stazione la sua partenza,
         * chiedendo il binario da cui deve partire. */
        if(t.getPassedStations() == 0){
            t.setStatus(3);
            get_station_binary(t, s, m, 0);
        }
        cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " arriva al binario " << t.getBinary() << " della stazione di " << s.get_Station_name() << ".\n";
        
        /* Se il treno arriva alla stazione dopo rispetto all'orario indicato nella rispettiva timetable, tale differenza di orario viene identificata come
         * ritardo con cui il treno arriva alla stazione. */
        
        if(t.getPassedStations() != 0){
            if (t.getType() == 1){
                if((m - t.getPath()[t.getPassedStations()]) > 0){
                    cout << "Il treno " << t.getTrainCode() << " segnala che ha un ritardo di " << m - t.getPath()[t.getPassedStations()] << " min" << endl;
                }
            }else{
                if((m - t.getPath()[t.getStops() + 1]) > 0){
                    cout << "Il treno " << t.getTrainCode() << " segnala che ha un ritardo di " << m - t.getPath()[t.getStops() + 1] << " min" << endl;
                } 
            }
        }
        
        //Se il treno è arrivato all'ultima stazione della linea ferroviaria, termina la sua corsa.
        
        if(stations[ns-1].get_Station_distance() == s.get_Station_distance()){
            t.setStatus(5);
        }
        if(t.getStatus() == 5){
            finish(t, s, m);
            return;
        }
        
        /* Se la prossima stazione si trova esattamente a 20km di distanza da quella in cui è arrivato il treno, esso, contemporaneamente al suo arrivo
         * deve avvisare la stazione successiva, chiedendo un binario nel caso si debba fermare o avvisando del suo passaggio. */
        
        int g = t.getBinary();          //viene salvato il binario attuale del treno
        vector<Station> st = stations;
        if(!t.isDirection()){
            st = da.get_reversed_Station();
        }
        if((st[t.getPassedStations()+1].get_Station_distance() - s.get_Station_distance()) == 20){
            t.setStatus(3);
            get_station_binary(t, st[t.getPassedStations()+1], m, t.getDistance());
            int l = t.getBinary();      //binario in cui il treno dovrà fermarsi nella prossima stazione
            t.setNextBinary(l);
            t.setBinary(g);             //viene ri-settato il binario su cui è attualment il treno
        }
        
        t.setMinutes(m);                //viene salvato il minuto di arrivo del treno alla stazione
        t.setStatus(1);                 //next step: partire dalla stazione
    }
}

void Line::train_departure(Train& t, Station& s, int m, int position_in_active_trains){
    bool flag = distance_check(t, position_in_active_trains);
    if(t.getStatus() == 1 && flag){
        if(t.getPassedStations() == 0){
            cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " inizia la sua corsa dal binario " << t.getBinary() << " della stazione di " << s.get_Station_name() << ".\n";
            t.setStatus(2);
        }
        if(t.getMinutes() + 5 == m){
            cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " parte dal binario " << t.getBinary() << " della stazione di " << s.get_Station_name() << ".\n";
            t.setStops(t.getStops() + 1);
            t.setStatus(2);
        }
    }
    
    //controllo distance_check
    /*if(!flag){
        cout << "Train " << t.getTrainCode() <<  "is waiting!\n";
    }*/
}

void Line::station_entry(Train& t, Station& s, int m, double d){
    bool p = false;
    if(s.get_Station_distance() - d >= 5 && s.get_Station_distance() - t.getDistance() <= 5){
        p = true;
    }
    if(t.getStatus() == 4 && p){
        if(t.getBinary() == 1){
            s.set_stb1_status(false);
        }else{
            if(t.getBinary() == 2){
                s.set_stb2_status(false);
            }else{
                if(t.getBinary() == 3){
                    s.set_stb3_status(false);
                }else{
                    if(t.getBinary() == 4){
                        s.set_stb4_status(false);
                    }else{
                        if(t.getBinary() == 5){
                            t.setStatus(3);
                            get_station_binary(t, s, m, t.getDistance());
                            if(t.getBinary() != 5){
                                s.remove_from_Deposit(t);
                                station_entry(t, s, m, t.getDistance());
                            }
                        }
                    }
                }
            }
        }
        cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " entra nel binario " << t.getBinary() << " della stazione di " << s.get_Station_name() << ".\n";
        t.setStatus(0);
    }
}

void Line::station_exit(Train& t, Station& s, int m, double d){
    bool p = false;
    if(d - s.get_Station_distance() <= 5 && t.getDistance() - s.get_Station_distance() >= 5){
        p = true;
    }
    if(t.getStatus() == 2 && p){
        cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " lascia il binario " << t.getBinary() << " della stazione di " << s.get_Station_name() << ".\n";
        if(t.getBinary() == 1){
            s.set_stb1_status(true);
            t.setBinary(0);
        }else{
            if(t.getBinary() == 2){
                s.set_stb2_status(true);
                t.setBinary(0);
            }else{
                if(t.getBinary() == 3){
                    s.set_stb3_status(true);
                    t.setBinary(0);
                }else{
                    if(t.getBinary() == 4){
                        s.set_stb4_status(true);
                        t.setBinary(0);
                    }
                }
            }
        }
        t.setStatus(3);
        vector<Station> st = stations;
        if(!t.isDirection()){
            st = da.get_reversed_Station();
        }
        if(st[t.getPassedStations()+1].get_Station_distance() - s.get_Station_distance() == 20){
            t.setStatus(4);
            int l = t.getNextBinary();
            t.setBinary(l);
        }
        t.setPassedStations(t.getPassedStations() + 1);
    }
}

void Line::go_trought(Train& t, Station& s, int m){
    t.setPassedStations(t.getPassedStations() + 1);
    cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " comunica che non si fermera' alla stazione di " << s.get_Station_name() << ". Bin.: " << t.getBinary() << ".\n";
    t.setStatus(3);
}

void Line::finish(Train& t, Station& s, int m){
    cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " conclude la sua corsa alla stazione di " << s.get_Station_name() << ".\n";
    active_trains.erase(active_trains.begin());
}

void Line::update_distance(Train& t){
    double k = get_km(t, 1);
    t.setDistance(t.getDistance() + k);
}

void Line::update_speed(Train& t){
    //controllare se ha un treno davanti a meno di 10km

    if(t.getStatus() != 5){
        int n = 0;
        double k = 0;
        double v = 0;
        vector<Station> st = stations;
        if(!t.isDirection()){
            st = da.get_reversed_Station();
        }
        if(t.isStopLocal()){
            if(t.getPassedStations() > 0){
                int stop = 5;
                if(t.getDistance() < (st[1].get_Station_distance())){
                    stop = 0;
                }
                n = t.getPath()[t.getPassedStations()] - (t.getPath()[t.getPassedStations()-1] + stop);
                k = st[t.getPassedStations()].get_Station_distance() - st[t.getPassedStations()-1].get_Station_distance();
                v = (k/n)*60;
                if (v > 160){
                    v = 160;
                }
                t.setCurrSpeed(v);
            }else{
                n = t.getPath()[t.getPassedStations()+1] - (t.getPath()[t.getPassedStations()]);
                k = st[t.getPassedStations()+1].get_Station_distance() - st[t.getPassedStations()].get_Station_distance();
                v = (k/n)*60;
                if (v > 160){
                    v = 160;
                }
                t.setCurrSpeed(v);
            }
            if(t.getCurrSpeed() > 80){
                if(t.getStatus() ==  2){        //sta uscendo da una stazione
                    t.setCurrSpeed(80);
                }else{
                    if(t.getStatus() == 0){     //sta entrando in una stazione
                        t.setCurrSpeed(80);
                    }else{
                        k -= 10;
                        v = (k/(n-8))*60;
                        if (v > 160){
                            v = 160;
                        }
                        t.setCurrSpeed(v);
                    }
                }
            }
        }else{
            if(t.getPassedStations() > 0){
                int stop = 5;
                if(t.getDistance() < (st[1].get_Station_distance())){
                    stop = 0;
                }
                vector<int> r = principal_distances;
                if(!(t.isDirection())){
                    r = reverse_principal_distances;
                }
                n = t.getPath()[t.getStops()+1] - (t.getPath()[t.getStops()] + stop);
                k = r[t.getStops()];
                v = (k/n)*60;
                t.setNextSpeed(v);
            }else{
                //se getPassedStations = 0
                int p = next_Principal_Station(t);
                n = t.getPath()[t.getPassedStations()+1] - (t.getPath()[t.getPassedStations()]);
                k = st[p].get_Station_distance() - st[t.getPassedStations()].get_Station_distance();
                v = (k/n)*60;
                t.setNextSpeed(v);
            }
            double nextSpeed = t.getNextSpeed();
            if(nextSpeed <= 80){
                t.setCurrSpeed(nextSpeed);
            }else{
                if(t.getStatus() ==  2){        //sta uscendo da una stazione
                    t.setCurrSpeed(80);
                }else{
                    if(t.getStatus() == 0){     //sta entrando in una stazione
                        t.setCurrSpeed(80);
                    }else{
                        k -= 10;
                        v = (k/(n-8))*60;
                        if (v > 240 && (t.getType() == 2)){
                            v = 240;
                        }
                        if (v > 300 && (t.getType() == 3)){
                            v = 300;
                        }
                        t.setCurrSpeed(v);
                    }
                }
            }
        }
    }
}

int Line::next_Principal_Station(Train& t){
    int i=0;
    vector<Station> st = stations;
    if(!t.isDirection()){
        st = da.get_reversed_Station();
    }

    if(t.getStatus() == 2){
        for(i=t.getPassedStations() + 1; i<ns; i++){
            if(!(st[i].get_Station_type())){
                return i;
            }
        }
    }else{
        for(i=t.getPassedStations()-1; i<ns; i++){
            if(!(st[i+1].get_Station_type())){
                return i+1;
            }
        }
    }
    return ns-1;
}

bool Line::distance_check(Train& t, int position_in_active_trains){
    for(int i=0; i<active_trains.size(); i++){
        
        //cout << "Distanza treno " << t.getTrainCode() << ": " << t.getDistance() << endl;
        //cout << "Distanza treno " << t.getTrainCode() << " dal treno " << active_trains[i].getTrainCode() << ": " << active_trains[i].getDistance() - t.getDistance() << endl;
        
        if((fabs(active_trains[i].getDistance() - t.getDistance() )<= 10) && (i != position_in_active_trains)){
            return false;
        }
    }
    return true;
}

void Line::simulation(){
    cout << "\n\t\t\t\t\t\t\t\tSTART\n\n";
    for(int i=120; i<3000; i++){            //mettere a 0 !!!!

        for(int t=0; t<nt; t++){
            if(trains[t].getPath()[0] == i){
                active_trains.push_back(trains[t]);
            }
        }

        for(int t=0; t<active_trains.size(); t++){

            vector<Station> s = stations;
            if(!active_trains[t].isDirection()){
                s = da.get_reversed_Station();
            }

            double d = active_trains[t].getDistance();
            if(active_trains[t].getStatus() != 1){
                update_distance(active_trains[t]);
            }

            station_entry(active_trains[t], s[active_trains[t].getPassedStations()], i, d);
            train_arrival(active_trains[t], s[active_trains[t].getPassedStations()], i, d);
            train_departure(active_trains[t], s[active_trains[t].getPassedStations()], i, t);
            station_exit(active_trains[t], s[active_trains[t].getPassedStations()], i, d);
            get_station_binary(active_trains[t], s[active_trains[t].getPassedStations()], i, d);

            update_speed(active_trains[t]);

        }
    }
    cout << "\n\t\t\t\t\t\t\t\tEND\n";
}