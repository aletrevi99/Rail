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
    
    Data d;
    st = d.getStation();
    t = d.getTrains();
    
    ns = st.size();
    nt = t.size();
    
}

void Rail::change_v(Train& t, int v){
    t.setCurrSpeed(v);
}

int Rail::get_minutes(Train& t, double d){
    int m;
    m = round((d/t.getCurrSpeed())*60);
    return m;
}

int Rail::get_km(Train& t, double m){
    int n;
    n = round(t.getCurrSpeed()*(m/60));
    return n;
}

void Rail::get_station_binary(Train& t, Station& s){        //da usare a 20km dalla stazione quando treno manda segnalazione
    if(t.isDirection()){
        if(s.get_stb1_status()){
            t.setBinary(1);
        }else{
            if(s.get_stb2_status()){
                t.setBinary(2);
            }else{
                t.setBinary(5);     //binari occupati, al deposito!
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
            }
        }
    }
    t.setStatus(4);
}

void Rail::train_arrival(Train& t, Station& s){
    if(t.getPassedStations() == 0){
        get_station_binary(t, s);
    }
    change_v(t, 0);
    if(t.getPassedStations() != 0 && t.getPassedStations() != (ns-1)){
        t.setMinutes(t.getMinutes() + 5);
    }
    t.setStatus(1);
}

void Rail::train_departure(Train& t){
    t.setCurrSpeed(80);
    t.setMinutes(t.getMinutes() + CROSSING_TIME);
    t.setStatus(2);
}

void Rail::station_entry(Train& t, Station& s){
    change_v(t, 80);
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
                        get_station_binary(t, s);
                        if(t.getBinary() != 5){
                            station_entry(t, s);
                        }
                    }
                }
            }
        }
    }
    t.setMinutes(t.getMinutes() + CROSSING_TIME);
    t.setStatus(0);
}

void Rail::station_exit(Train& t, Station& s){
    change_v(t, t.getMaxSpeed());
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
    t.setPassedStations(t.getPassedStations() + 1);
    t.setStatus(3);
}

void Rail::simulation(){
    cout << "START\n";
    for(int i=0; i<3000; i++){
        for(int tr=0; tr<nt; tr++){
            
            vector<Station> s = st;
            if(!t[tr].isDirection()){
                int m = s[ns-1].get_Station_distance();
                reverse(s.begin(), s.end());
                for(int c=0; c<ns; c++){
                    s[c].set_Station_distance(m - s[c].get_Station_distance());
                }
            }
            
            vector<int> orari = t[tr].getPath();
            for(int j=0; j<orari.size(); j++){
                                
                //treno arriva al binario
                if(orari[j] == i && t[tr].getStatus() == 0 /*&& i == orari[0] + t[tr].getMinutes()*/){
                    train_arrival(t[tr], s[t[tr].getPassedStations()]);
                    cout << "Al minuto " << i << " il treno " << t[tr].getTrainCode() << " arriva al binario " << t[tr].getBinary() << " della stazione di " << s[t[tr].getPassedStations()].get_Station_name() << ".\n";
                    if(t[tr].getPassedStations() == ns-1 || j == orari.size()-1){
                        cout << "Al minuto " << i << " il treno " << t[tr].getTrainCode() << " conclude la sua corsa alla stazione di " << s[t[tr].getPassedStations()].get_Station_name() << ".\n";
                        t[tr].setStatus(6); //stato 6 = treno ha 
                    }
                }else{
                    
                    //treno lascia il binario
                    if(t[tr].getStatus() == 1 /*&& i == orari[0] + t[tr].getMinutes()*/){
                        train_departure(t[tr]);
                        cout << "Al minuto " << i << " il treno " << t[tr].getTrainCode() << " parte dal binario " << t[tr].getBinary() << " della stazione di " << s[t[tr].getPassedStations()].get_Station_name() << ".\n";
                    }else{
                        
                        //uscita di un treno da una stazione (dopo 5km)
                        if(t[tr].getStatus() == 2 /*&& i == orari[0] + t[tr].getMinutes()*/){
                            cout << "Al minuto " << i << " il treno " << t[tr].getTrainCode() << " lascia il binario " << t[tr].getBinary() << " della stazione di " << s[t[tr].getPassedStations()].get_Station_name() << ".\n";
                            station_exit(t[tr], s[t[tr].getPassedStations()]);
                            
                            int m = get_minutes(t[tr], s[t[tr].getPassedStations()].get_Station_distance() - s[t[tr].getPassedStations()-1].get_Station_distance() - 10);
                            t[tr].setMinutes(t[tr].getMinutes() + m);
                            
                        }else{
                            
                            //treno segna ad una stazione il suo arrivo
                            int l = get_minutes(t[tr], 15);
                            if(t[tr].getStatus() == 3 /*&& i == orari[0] + t[tr].getMinutes() -l*/){
                                
                                //se il treno non è regionale e la stazione non è locale, il treno non si ferma
                                if((!(t[tr].isStopLocal())) && (s[t[tr].getPassedStations()].get_Station_type())){
                                    int u = get_minutes(t[tr], s[t[tr].getPassedStations()+1].get_Station_distance() - s[t[tr].getPassedStations()].get_Station_distance());
                                    t[tr].setMinutes(t[tr].getMinutes() + u);
                                    t[tr].setStatus(3);
                                    cout << "Al minuto " << i << " il treno " << t[tr].getTrainCode() << " comunica che non si fermera' alla stazione di " << s[t[tr].getPassedStations()].get_Station_name() << ". Bin.: " << t[tr].getBinary() << ".\n";
                                    t[tr].setPassedStations(t[tr].getPassedStations() + 1);
                                }else{
                                    get_station_binary(t[tr], s[t[tr].getPassedStations()]);
                                    cout << "Al minuto " << i << " il treno " << t[tr].getTrainCode() << " avvisa la stazione di " << s[t[tr].getPassedStations()].get_Station_name() << ". Bin.: " << t[tr].getBinary() << ".\n";
                                }
                            }else{
                                
                                //arrivo di un treno alla stazione (ai -5km)
                                if(t[tr].getStatus() == 4 /*&& i == orari[0] + t[tr].getMinutes()*/){
                                    if(t[tr].getBinary() != 5){
                                        station_entry(t[tr], s[t[tr].getPassedStations()]);
                                        cout << "Al minuto " << i << " il treno " << t[tr].getTrainCode() << " entra nel binario " << t[tr].getBinary() << " della stazione di " << s[t[tr].getPassedStations()].get_Station_name() << ".\n";
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}