/*
 * Studente: Ghiotto Andrea
 * Matricola: 1216363
 * Corso: Laboratorio di Programmazione
 * Anno: 2°
 * Scuola: Ing. Informatica - UniPd
 * Data di creazione: 30/12/2020
*/

#include "Rail.h"
#include <Math.h>

#include <iterator>
#include <algorithm>

using namespace std;

Rail::Rail(){
    
    stations = da.getStation();
    trains = da.getTrains();
    
    ns = stations.size();
    nt = trains.size();
    
}

void Rail::change_v(Train& t, int v){
    t.setCurrSpeed(v);
}

int Rail::get_minutes(Train& t, double d){
    int m;
    m = round((d/t.getCurrSpeed())*60);
    return m;
}

double Rail::get_km(Train& t, double m){
    double n;
    n = (t.getCurrSpeed()*(m/60));
    return n;
}

void Rail::get_station_binary(Train& t, Station& s, int m, int d){        //da usare a 20km dalla stazione quando treno manda segnalazione
    bool p = false;
    if(((s.get_Station_distance() - d) >= 20) && ((s.get_Station_distance() - t.getDistance()) <= 20)){
        p = true;
    }
    if(t.getStatus() == 3 && (p || (t.getDistance() == 0))){
        if((!(t.isStopLocal())) && (s.get_Station_type())){
            go_trought(t, s, m);
        }else{
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
                if(s.get_stb3_status()){
                    t.setBinary(3);
                    /*
                    if(s.get_Station_distance() == 280){
                        t.setBinary(4);
                    }*/
                    
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
            t.setStatus(4);
        }
    }
}

void Rail::train_arrival(Train& t, Station& s, int m, int d){
    bool p = false;
    if(s.get_Station_distance() - d >= 0 && s.get_Station_distance() - t.getDistance() <= 0){
        p = true;
    }
    if(t.getStatus() == 0 && p){
        t.setDistance(s.get_Station_distance());
        //change_v(t, 0);
        if(t.getPassedStations() == 0){
            t.setStatus(3);
            get_station_binary(t, s, m, 0);
        }
        cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " arriva al binario " << t.getBinary() << " della stazione di " << s.get_Station_name() << ".\n";
        //cout << "KM percorsi: " << t.getDistance() << endl;
        if(t.getPassedStations() == (ns-1)){
            finish(t, s, m);
        }
        int g = t.getBinary();
        //cout << "Binario attuale: " << g << endl;
        vector<Station> st = stations;
        if(!t.isDirection()){
            st = da.get_reversed_Station();
        }
        if((st[t.getPassedStations()+1].get_Station_distance() - s.get_Station_distance()) == 20){
            t.setStatus(3);
            get_station_binary(t, st[t.getPassedStations()+1], m, t.getDistance());
            int l = t.getBinary();
            t.setNextBinary(l);
            t.setBinary(g);
            //cout << "Prossimo binario: " << l << endl;
        }
        //cout << "Distanza dalla stazione successiva: " << (st[t.getPassedStations()+1].get_Station_distance() - s.get_Station_distance()) << endl;
        t.setMinutes(m);
        t.setStatus(1);
    }
}

void Rail::train_departure(Train& t, Station& s, int m){
    if(t.getStatus() == 1 && t.getDistance() == s.get_Station_distance()){
        //t.setCurrSpeed(80);
        if(t.getPassedStations() == 0){
            cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " inizia la sua corsa dal binario " << t.getBinary() << " della stazione di " << s.get_Station_name() << ".\n";
            t.setStatus(2);
        }
        if(t.getMinutes() + 5 == m){
            cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " parte dal binario " << t.getBinary() << " della stazione di " << s.get_Station_name() << ".\n";
            t.setStatus(2);
        }
    }
}

void Rail::station_entry(Train& t, Station& s, int m, int d){
    bool p = false;
    if(s.get_Station_distance() - d >= 5 && s.get_Station_distance() - t.getDistance() <= 5){
        p = true;
    }
    if(t.getStatus() == 4 && p){
        //change_v(t, 80);
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

void Rail::station_exit(Train& t, Station& s, int m, int d){
    bool p = false;
    if(d - s.get_Station_distance() <= 5 && t.getDistance() - s.get_Station_distance() >= 5){
        p = true;
    }
    if(t.getStatus() == 2 && p){
        cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " lascia il binario " << t.getBinary() << " della stazione di " << s.get_Station_name() << ".\n";
        //change_v(t, t.getMaxSpeed());
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

void Rail::go_trought(Train& t, Station& s, int m){
    t.setPassedStations(t.getPassedStations() + 1);
    cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " comunica che non si fermera' alla stazione di " << s.get_Station_name() << ". Bin.: " << t.getBinary() << ".\n";
    t.setStatus(3);
    cout << t.getCurrSpeed() << endl;
}

void Rail::finish(Train& t, Station& s, int m){
    change_v(t, 0);
    active_trains.erase(active_trains.begin());
    cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " conclude la sua corsa alla stazione di " << s.get_Station_name() << ".\n";
    t.setStatus(5);
}

void Rail::update_distance(Train& t){
    double k = get_km(t, 1);
    t.setDistance(t.getDistance() + k);
}

void Rail::update_speed(Train& t){
    //controllare se ha un treno davanti a meno di 10km
    
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
            t.setCurrSpeed(v);
        }else{
            n = t.getPath()[t.getPassedStations()+1] - (t.getPath()[t.getPassedStations()]);
            k = st[t.getPassedStations()+1].get_Station_distance() - st[t.getPassedStations()].get_Station_distance();
            v = (k/n)*60;
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
                    t.setCurrSpeed(v);
                }
            }
        }
        
        //fino a qui funziona tutto ok con treni regionali
        
        
        
        
        
        
        
        
    }else{
        
        //int l = next_Principal_Station(t);
        
        if(t.getPassedStations() > 0){
            
            int stop = 5;
            if(t.getDistance() < (st[1].get_Station_distance())){
                stop = 0;
            }
            if(!(st[t.getPassedStations()].get_Station_type()) && t.getStatus() != 2){
                int l = next_Principal_Station(t);
                n = t.getPath()[t.getPassedStations()] - (t.getPath()[t.getPassedStations()-1] + stop);
                k = st[l].get_Station_distance() - st[t.getPassedStations()-1].get_Station_distance();
                v = (k/n)*60;
                
                if(v > 80){
                    k -= 10;
                    n -= 8;
                    v = (k/n)*60;
                    t.setNextSpeed(v);
                }else{
                    t.setNextSpeed(v);
                }
                
                
            }else{
                if(!(st[t.getPassedStations()].get_Station_type()) && t.getStatus() == 2){
                    int l = next_Principal_Station(t);
                    n = t.getPath()[t.getPassedStations()+1] - (t.getPath()[t.getPassedStations()] + stop);
                    k = st[l].get_Station_distance() - st[t.getPassedStations()].get_Station_distance();
                    v = (k/n)*60;
                    
                    if(v > 80){
                        k -= 10;
                        n -= 8;
                        v = (k/n)*60;
                        t.setNextSpeed(v);
                    }else{
                        t.setNextSpeed(v);
                    }
                    
                    
                }
            }
        }else{
            if(!(st[t.getPassedStations()].get_Station_type())){
                int l = next_Principal_Station(t);
                n = t.getPath()[t.getPassedStations()+1] - (t.getPath()[t.getPassedStations()]);
                k = st[l].get_Station_distance() - st[t.getPassedStations()].get_Station_distance();
                v = (k/n)*60;
                
                
                if(v > 80){
                    k -= 10;
                    n -= 8;
                    v = (k/n)*60;
                    t.setNextSpeed(v);
                }else{
                    t.setNextSpeed(v);
                }
                
            }
        }
        
        if(t.getNextSpeed() > 80){
            if(t.getStatus() ==  2){        //sta uscendo da una stazione
                t.setCurrSpeed(80);
            }else{
                if(t.getStatus() == 0){     //sta entrando in una stazione
                    t.setCurrSpeed(80);
                }else{
                    t.setCurrSpeed(t.getNextSpeed());
                }
            }
        }
        
        
        
        
    }
    
    
}

int Rail::next_Principal_Station(Train& t){
    int i=0;
    vector<Station> st = stations;
    if(!t.isDirection()){
        st = da.get_reversed_Station();
    }
    
    if(t.getStatus() == 2){
        for(i=t.getPassedStations(); i<ns; i++){
            if(!(st[i+1].get_Station_type())){
                return i+1;
            }
        }
    }else{
        for(i=t.getPassedStations()-1; i<ns; i++){
            if(!(st[i+1].get_Station_type())){
                return i+1;
            }
        }
    }
    
    
    /*
    for(i=t.getPassedStations(); i<ns; i++){
        if(!(st[i+1].get_Station_type())){
            return i+1;
        }
    }*/
    return ns-1;
}

void Rail::simulation(){
    cout << "START\n";
    for(int i=120; i<3000; i++){
        
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
            
            int d = active_trains[t].getDistance();
            if(active_trains[t].getStatus() != 1){
                update_distance(active_trains[t]);
            }
            
            station_entry(active_trains[t], s[active_trains[t].getPassedStations()], i, d);
            train_arrival(active_trains[t], s[active_trains[t].getPassedStations()], i, d);
            train_departure(active_trains[t], s[active_trains[t].getPassedStations()], i);
            station_exit(active_trains[t], s[active_trains[t].getPassedStations()], i, d);
            get_station_binary(active_trains[t], s[active_trains[t].getPassedStations()], i, d);
            
            update_speed(active_trains[t]);
            
        }
    }
}