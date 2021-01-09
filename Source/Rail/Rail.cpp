/*
 * Studente: Ghiotto Andrea
 * Matricola: 1216363
 * Corso: Laboratorio di Programmazione
 * Anno: 2°
 * Scuola: Ing. Informatica - UniPd
 * Data di creazione: 30/12/2020
*/

#include "Rail.h"

using namespace std;

Rail::Rail(){
    
    stations = da.getStation();
    trains = da.getTrains();
    
    ns = stations.size();
    nt = trains.size();
    
    principal_distances = da.getPrincipalDistances();
    reverse_principal_distances = principal_distances;
    reverse(reverse_principal_distances.begin(), reverse_principal_distances.end());
    
}

void Rail::change_v(Train& t, double v){
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

void Rail::get_station_binary(Train& t, Station& s, int m, double d){        //da usare a 20km dalla stazione quando treno manda segnalazione
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

void Rail::train_arrival(Train& t, Station& s, int m, double d){
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
        
        
        //aggiunta
        if(stations[ns-1].get_Station_distance() == s.get_Station_distance()){
            t.setStatus(5);
        }
        
        if(/*t.getPassedStations() == (ns-1)*/t.getStatus() == 5){              //aggiunta
            finish(t, s, m);
            return;
        }
        int g = t.getBinary();
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
        }
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
            t.setStops(t.getStops() + 1);
            t.setStatus(2);
        }
    }
}

void Rail::station_entry(Train& t, Station& s, int m, double d){
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

void Rail::station_exit(Train& t, Station& s, int m, double d){
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
            if (v > 160) v = 160;
            t.setCurrSpeed(v);
        }else{
            n = t.getPath()[t.getPassedStations()+1] - (t.getPath()[t.getPassedStations()]);
            k = st[t.getPassedStations()+1].get_Station_distance() - st[t.getPassedStations()].get_Station_distance();
            v = (k/n)*60;
            if (v > 160) v = 160;
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
                    if (v > 160) v = 160;
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
            int p = next_Principal_Station(t);;
            n = t.getPath()[t.getStops()+1] - (t.getPath()[t.getStops()] + stop);
            k = principal_distances[t.getStops()];      //fare controllo per quando usare reverse_principal_distances
            v = (k/n)*60;
            if (v > 240 && (t.getType() == 2)) v = 240;
            if (v > 300 && (t.getType() == 3)) v = 300;
            t.setNextSpeed(v);
        }else{
            //se getPassedStations = 0
            int p = next_Principal_Station(t);
            n = t.getPath()[t.getPassedStations()+1] - (t.getPath()[t.getPassedStations()]);
            k = st[p].get_Station_distance() - st[t.getPassedStations()].get_Station_distance();
            v = (k/n)*60;
            if (v > 240 && (t.getType() == 2)) v = 240;
            if (v > 300 && (t.getType() == 3)) v = 300;
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
                    if (v > 240 && (t.getType() == 2)) v = 240;
                    if (v > 300 && (t.getType() == 3)) v = 300;
                    t.setCurrSpeed(nextSpeed);
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
            
            double d = active_trains[t].getDistance();
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