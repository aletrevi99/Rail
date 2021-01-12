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
     * line_description.txt nelle variabili stations e trains.
     * Viene inoltre utilizzata la funzione get_reversed_Station() della classe Data per salvare in reverse_station le stazioni della linea, rovesciate.
     * Vengono settate ns e nt alle dimensioni rispettivamente di stations e trains.
     * Viene settato il valore della variabile time, usufruendo della funzione getLastArrival() della classe Data.
     * Vengono inoltre riempiti principal_distances e reverse_principal_distances con i valori della distanze tra le varie stazioni. */
    
    stations = da.getStation();
    trains = da.getTrains();
    
    reverse_stations = da.get_reversed_Station();
    
    ns = stations.size();
    nt = trains.size();
    
    time = da.getLastArrival();
    if(time < 1440){
        time = 1440;
    }
    
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
    if(((s.getStationDistance() - d) >= 20) && ((s.getStationDistance() - t.getDistance()) <= 20)){
        p = true;
    }
    if(t.getStatus() == 3 && (p || (t.getDistance() == 0))){
        
        /* Se il treno non è un treno regionale e la stazione è una stazione locale, il treno non entra nei binari di quella stazione, continua a viaggiare
         * nei binari di transito e non si ferma in quella stazione. */
         
        if((!(t.isStopLocal())) && (s.isLocal())){
            t.setBinary(0);
            go_trought(t, s, m);
        }else{
            
            /* Se il treno viaggia dalla stazione di origine verso il capolinea, viene verificata la disponibilità dei binari 1 e 2. Se uno dei due binari è
             * libero, viene comunicato al treno come binario su cui fermarsi, altrimenti il treno dovrà entra nel deposito d1. */
            
            if(t.isDirection()){
                if(s.isStb1Status()){
                    t.setBinary(1);
                }else{
                    if(s.isStb2Status()){
                        t.setBinary(2);
                    }else{
                        t.setBinary(5);     //binari occupati, al deposito!
                        s.addToDeposit(t);
                    }
                }
            }else{
                
                /* Se il treno viaggia dal capolinea verso la stazione di origine, viene verificata la disponibilità dei binari 3 e 4. Se uno dei due binari è
                 * libero, viene comunicato al treno come binario su cui fermarsi, altrimenti il treno dovrà entra nel deposito d2. */
                 
                if(s.isStb3Status()){
                    t.setBinary(3);
                }else{
                    if(s.isStb4Status()){
                        t.setBinary(4);
                    }else{
                        t.setBinary(5);     //binari occupati, al deposito!
                        s.addToDeposit(t);
                    }
                }
            }
            
            cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " avvisa la stazione di " << s.getStationName() << ".\n";
            cout << "Al minuto " << m << " la stazione di " << s.getStationName() << " avvisa il treno " << t.getTrainCode() << " che dovra' fermarsi al binariro: " << t.getBinary() << ".\n"; //Bin. = 5 -> deposito
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
    if(s.getStationDistance() - d >= 0 && s.getStationDistance() - t.getDistance() <= 0){
        p = true;
    }
    if(t.getStatus() == 0 && p){
        
        //Se il treno è arrivato alla stazione, viene aggiornata la distanza che ha percorso ponendola uguale alla distanza della stazione.
        t.setDistance(s.getStationDistance());
        
        /* Se il treno deve ancora partire, viene "virtualmente" fatto arrivare al binario della stazione e segnala alla stazione la sua partenza,
         * chiedendo il binario da cui deve partire. */
        if(t.getPassedStations() == 0){
            t.setStatus(3);
            get_station_binary(t, s, m, 0);
        }
        cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " arriva al binario " << t.getBinary() << " della stazione di " << s.getStationName() << ".\n";
        
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
        
        if(stations[ns - 1].getStationDistance() == s.getStationDistance()){
            t.setStatus(5);
        }
        if(t.getStatus() == 5){
            finish(t, s, m);
            return;
        }
        
        /* Se la prossima stazione si trova esattamente a 20km di distanza da quella in cui è arrivato il treno, esso, contemporaneamente al suo arrivo,
         * deve avvisare la stazione successiva, chiedendo un binario nel caso si debba fermare o avvisando del suo passaggio. */
        
        int g = t.getBinary();          //viene salvato il binario attuale del treno
        vector<Station> st = stations;
        if(!t.isDirection()){
            st = da.get_reversed_Station();
        }
        int dist = st[t.getPassedStations() + 1].getStationDistance() - s.getStationDistance();
        if(dist == 20){
            t.setStatus(3);
            get_station_binary(t, st[t.getPassedStations()+1], m, t.getDistance());
            int l = t.getBinary();      //binario in cui il treno dovrà fermarsi nella prossima stazione
            t.setNextBinary(l);
            t.setBinary(g);             //viene ri-settato il binario su cui è attualment il treno
        }
        
        t.setMinutes(m);                //viene salvato il minuto di arrivo del treno alla stazione
        t.setStatus(1);                 //next step: partire da una stazione
    }
}

void Line::train_departure(Train& t, Station& s, int m){
    
    /* La funzione train_departure() gestisce la partenza di un treno da una stazione.
     * Se lo stato del treno è 1 (ovvero coerente con la prossima azione che il treno deve "compiere", la partenza da una stazione appunto) e se il treno
     * ha atteso 5 minuti per la salita/discesa dei passeggeri, esso parte dalla stazione.
     * Il parametro m che viene passato indica il minuto in cui viene chiamata la funzione. */
    
    if(t.getStatus() == 1){
        if(t.getPassedStations() == 0){
            cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " inizia la sua corsa dal binario " << t.getBinary() << " della stazione di " << s.getStationName() << ".\n";
            t.setStatus(2);         //next step: uscire dai binari di una stazione (5km dopo di essa)
        }
        if(t.getMinutes() + 5 <= m){
            cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " parte dal binario " << t.getBinary() << " della stazione di " << s.getStationName() << ".\n";
            t.setStops(t.getStops() + 1);       //viene aggiornato il counter delle fermate effettuate dal treno
            t.setStatus(2);                     //next step: uscire dai binari di una stazione (5km dopo di essa)
        }
    }
}

void Line::station_entry(Train& t, Station& s, int m, double d){
    
    /* La funzione station_entry() gestisce l'entrata di un treno nei binari di una stazione (5km prima della stazione).
     * Se lo stato del treno è 4 (ovvero coerente con la prossima azione che il treno deve "compiere", l'entrata nei binari di una stazione appunto) e se il
     * treno è nella posizione corretta (ai -5km dalla stazione), esso entra nel binario della stazione che gli era stato precedentemente assegnato in fase
     * di segnalazione, binario 5 = deposito. Lo stato binario su cui entra viene cambiato in false -> "occupato".
     * Se ad un treno è stato indicato di sostare nel deposito, esso manda una segnalazione alla stazione. Nel caso riceva un binario diverso da quello che 
     * indica il deposito, entra in quel binario.
     * Il parametro m che viene passato indica il minuto in cui viene chiamata la funzione, mentre d indica la distanza percorsa dal treno fino al minuto
     * precedente e viene usata, confrontandola con la distanza attuale, per verificare se il treno è entrato nei binari della stazione. */
    
    bool p = false;
    if(s.getStationDistance() - d >= 5 && s.getStationDistance() - t.getDistance() <= 5){
        p = true;
    }
    if(t.getStatus() == 4 && p){
        if(t.getBinary() == 1){
            s.setStb1Status(false);
        }else{
            if(t.getBinary() == 2){
                s.setStb2Status(false);
            }else{
                if(t.getBinary() == 3){
                    s.setStb3Status(false);
                }else{
                    if(t.getBinary() == 4){
                        s.setStb4Status(false);
                    }else{
                        if(t.getBinary() == 5){
                            t.setStatus(3);
                            get_station_binary(t, s, m, t.getDistance());
                            if(t.getBinary() != 5){
                                s.removeFromDeposit(t);
                                station_entry(t, s, m, t.getDistance());
                            }
                        }
                    }
                }
            }
        }
        //cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " entra nel binario " << t.getBinary() << " della stazione di " << s.getStationName() << ".\n";
        t.setStatus(0);             //next step: arrivare in una stazione
    }
}

void Line::station_exit(Train& t, Station& s, int m, double d){
    
    /* La funzione station_exit() gestisce l'uscita di un treno nei binari di una stazione (5km dopo la stazione).
     * Se lo stato del treno è 2 (ovvero coerente con la prossima azione che il treno deve "compiere", l'uscita dai binari di una stazione appunto) e se il
     * treno è nella posizione corretta (ai +5km dalla stazione in cui si è appena fermato), esso esce dal binario della stazione su cui viaggiava.
     * Il parametro m che viene passato indica il minuto in cui viene chiamata la funzione, mentre d indica la distanza percorsa dal treno fino al minuto
     * precedente e viene usata, confrontandola con la distanza attuale, per verificare se il treno è uscito dai binari della stazione. */
    
    bool p = false;
    if(d - s.getStationDistance() <= 5 && t.getDistance() - s.getStationDistance() >= 5){
        p = true;
    }
    if(t.getStatus() == 2 && p){
        //cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " lascia il binario " << t.getBinary() << " della stazione di " << s.getStationName() << ".\n";
        if(t.getBinary() == 1){
            s.setStb1Status(true);
            t.setBinary(0);
        }else{
            if(t.getBinary() == 2){
                s.setStb2Status(true);
                t.setBinary(0);
            }else{
                if(t.getBinary() == 3){
                    s.setStb3Status(true);
                    t.setBinary(0);
                }else{
                    if(t.getBinary() == 4){
                        s.setStb4Status(true);
                        t.setBinary(0);
                    }
                }
            }
        }
        
        t.setStatus(3);                 //next step: segnalare ad una stazione l'arrivo/passaggio
        
        /* Se la prossima stazione si trova esattamente a 20km di distanza da quella dai cui binari il treno è appena uscito, il binario su cui dovrà
         * transitare è quello che gli era stato assegnato in precedenza, in fase di segnalazione, una volta arrivato alla stazione precedente. */
        
        vector<Station> st = stations;
        if(!t.isDirection()){
            st = da.get_reversed_Station();
        }
        int dist = st[t.getPassedStations() + 1].getStationDistance() - s.getStationDistance();
        if(dist == 20){
            t.setStatus(4);                 //lo stato viene settato a 4 (entrata nei binari di una stazione) in quanto ha già segnalato in precedenza
            int l = t.getNextBinary();
            t.setBinary(l);
        }
        
        //Una volta uscito dai binari di una stazione, il counter delle stazione passate dal treno viene aggiornato.
        t.setPassedStations(t.getPassedStations() + 1);
    }
}

void Line::go_trought(Train& t, Station& s, int m){
    
    /* La funzione go_trought() gestisce la situazione in cui un treno (alta velocità / alta velocità super) sia prossimo ad una stazione locale e non vi si
     * fermi. Viene aggiornato il counter delle stazioni passate ma non, logicamente, quello delle fermate compiute. */
    
    t.setPassedStations(t.getPassedStations() + 1);
    //cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " comunica che non si fermera' alla stazione di " << s.getStationName() << ". Bin.: " << t.getBinary() << ".\n";
    t.setStatus(3);             //next step: segnalare ad una stazione l'arrivo/passaggio
}

void Line::finish(Train& t, Station& s, int m){

    /* La funzione finish() gestisce l'arrivo di un treno all'ultima stazione e, quindi la conclusione della sua corsa.
     * Il treno, una volta arrivato, viene eliminato dall'array contenente i treni attualmente in viaggio sulla linea ferroviaria. */
     
    cout << "Al minuto " << m << " il treno " << t.getTrainCode() << " conclude la sua corsa alla stazione di " << s.getStationName() << ".\n";
    
    //Viene "liberato" il binario su cui il treno è arrivato.
    if(t.getBinary() == 1){
        s.setStb1Status(true);
        t.setBinary(0);
    }else{
        if(t.getBinary() == 2){
            s.setStb2Status(true);
            t.setBinary(0);
        }else{
            if(t.getBinary() == 3){
                s.setStb3Status(true);
                t.setBinary(0);
            }else{
                if(t.getBinary() == 4){
                    s.setStb4Status(true);
                    t.setBinary(0);
                }
            }
        }
    }
    
    for(int i = 0; i < active_trains.size(); ++i){
        if (t.getTrainCode() == active_trains[i].getTrainCode())
            active_trains.erase(active_trains.begin() + i);
    }
}

void Line::update_distance(Train& t){
    
    /* Il metodo update_distance() aggiorna la distanza percorsa da un treno. */
    
    double k = get_km(t, 1);
    t.setDistance(t.getDistance() + k);
}

void Line::update_speed(Train& t){
    
    /* Il metodo update_speed() aggiorna la velocità corrente di un treno. */ 
    
    //La velocità di un treno viene aggiornata solamente se il treno è in viaggio.
    if(t.getStatus() != 5){
        
        int m = 0;          //minuti
        double k = 0;       //kilometri
        double v = 0;       //velocità
        
        vector<Station> st = stations;
        if(!t.isDirection()){
            st = da.get_reversed_Station();
        }
        
        //Se il treno è un treno regionale utilizzo passedStations come indice per scorrere l'array (path) contenente gli orari di fermata nelle varie stazioni.
        if(t.isStopLocal()){
            
            if(t.getPassedStations() > 0){
                int stop = 5;
                if(t.getDistance() < (st[1].getStationDistance())){
                    stop = 0;
                }
                m = t.getPath()[t.getPassedStations()] - (t.getPath()[t.getPassedStations()-1] + stop);
                k = st[t.getPassedStations()].getStationDistance() -
                    st[t.getPassedStations() - 1].getStationDistance();
                v = (k/m)*60;
                if (v > 160){
                    v = 160;
                }
                t.setCurrSpeed(v);
            }else{
                
                //Se il treno deve ancora partire.
                m = t.getPath()[t.getPassedStations()+1] - (t.getPath()[t.getPassedStations()]);
                k = st[t.getPassedStations() + 1].getStationDistance() - st[t.getPassedStations()].getStationDistance();
                v = (k/m)*60;
                if (v > 160){
                    v = 160;
                }
                t.setCurrSpeed(v);
            }
            
            if(t.getCurrSpeed() > 80){
                if(t.getStatus() ==  2){        //sta uscendo da una stazione, la velocità massima può essere di 80km/h
                    t.setCurrSpeed(80);
                }else{
                    if(t.getStatus() == 0){     //sta entrando in una stazione, la velocità massima può essere di 80km/h
                        t.setCurrSpeed(80);
                    }else{
                        
                        //Se è in un tratto privo di limiti di velocità, la velocità massima può essere di 160km/h
                        k -= 10;                //vengono tolti i 5km prima e dopo la stazione
                        m -= 8;                 //vengono tolti gli 8 minuti necessari a percorrere i 10km con limiti di velocità
                        v = (k/m)*60;       
                        if (v > 160){
                            v = 160;
                        }
                        t.setCurrSpeed(v);
                    }
                }
            }
        }else{
            
            //Se il treno non è regionale utilizzo stops come indice per scorrere l'array (path) contenente gli orari di fermata nelle varie stazioni.
            if(t.getPassedStations() > 0){
                int stop = 5;
                if(t.getDistance() < (st[1].getStationDistance())){
                    stop = 0;
                }
                vector<int> r = principal_distances;
                if(!(t.isDirection())){
                    r = reverse_principal_distances;
                }
                m = t.getPath()[t.getStops()+1] - (t.getPath()[t.getStops()] + stop);
                k = r[t.getStops()];
                v = (k/m)*60;
                t.setCurrSpeed(v);
            }else{
                
                //Se il treno deve ancora partire.
                int p = next_Principal_Station(t);
                m = t.getPath()[t.getPassedStations()+1] - (t.getPath()[t.getPassedStations()]);
                k = st[p].getStationDistance() - st[t.getPassedStations()].getStationDistance();
                v = (k/m)*60;
                t.setCurrSpeed(v);
            }
            
            if(t.getCurrSpeed() > 80){
                if(t.getStatus() ==  2){        //sta uscendo da una stazione, la velocità massima può essere di 80km/h
                    t.setCurrSpeed(80);
                }else{
                    if(t.getStatus() == 0){     //sta entrando in una stazione, la velocità massima può essere di 80km/h
                        t.setCurrSpeed(80);
                    }else{
                        
                        //Se è in un tratto privo di limiti di velocità, la velocità massima può essere di 240km/h per gli av e di 300km/h per gli av super.
                        k -= 10;                //vengono tolti i 5km prima e dopo la stazione
                        m -= 8;                  //vengono tolti gli 8 minuti necessari a percorrere i 10km con limiti di velocità
                        v = (k/m)*60;
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
    
    /* La funzione next_Principal_Station() restituisce l'indice nel vector di stazioni della prossima stazione principale che il treno incontrerà. */
    
    int i=0;
    vector<Station> st = stations;
    if(!t.isDirection()){
        st = da.get_reversed_Station();
    }
    
    //Se il treno deve ancora uscire dai binari della stazione, e quindi il passedStations deve ancora essere incrementato.
    if(t.getStatus() == 2){
        for(i=t.getPassedStations() + 1; i<ns; i++){
            if(!(st[i].isLocal())){
                return i;
            }
        }
    }else{
        
        //Se il treno è già uscito dai binari della stazione, e quindi il passedStations è già stato incrementato.
        for(i=t.getPassedStations()-1; i<ns; i++){
            if(!(st[i + 1].isLocal())){
                return i+1;
            }
        }
    }
    
    return ns-1;        //se non viene trovata alcuna stazione principale, viene ritornato l'indice dell'ultima stazione.
}

void Line::simulation(){
    
    /* La funzione simulation() simula il funzionamento giornaliero della linea ferroviaria. */
    
    cout << "\nSTART SIMULATION\n" << endl;
    
    //Scorre tutti i minuti della giornata, fino al minuto di arrivo dell'ultimo treno, eventualmente il giorno successivo.
    for(int i=0; i<time+360; i++){      //ritardo massimo dell'ultimo treno: 6 ore
        
        //Scorre tutti i treni
        for(int t=0; t<nt; t++){
            
            /* Se l'orario di partenza di un treno coincide con il minuto attuale, il treno viene inserito nel vettore contenente
             * i treni attualmente in viaggio lungo la linea ferroviaria. */
             
            if(trains[t].getPath()[0] == i){
                active_trains.push_back(trains[t]);
            }
        }
        vector<Station> s = stations;
        
        //Scorre tutti i treni attualmente in viaggio lungo la linea ferroviaria.
        for(int t=0; t<active_trains.size(); t++){
            
            //Se il treno viaggia da capolinea verso la stazione d'origine, vengono considerate le stazioni in ordine "rovesciato".
            if(!active_trains[t].isDirection()){
                s = reverse_stations;
            }
            
            double d = active_trains[t].getDistance();      //Distanza percorsa dal treno (calcolata al minuto i-1)
            
            //Viene aggiornata la distanza percorsa dal treno (calcolata al minuto i)
            if(active_trains[t].getStatus() != 1){
                update_distance(active_trains[t]);
            }
            
            station_entry(active_trains[t], s[active_trains[t].getPassedStations()], i, d);
            train_arrival(active_trains[t], s[active_trains[t].getPassedStations()], i, d);
            train_departure(active_trains[t], s[active_trains[t].getPassedStations()], i);
            station_exit(active_trains[t], s[active_trains[t].getPassedStations()], i, d);
            get_station_binary(active_trains[t], s[active_trains[t].getPassedStations()], i, d);
            
            //Viene aggiornata la velocità attuale del treno.
            update_speed(active_trains[t]);
            
            stations = s;
            if(!active_trains[t].isDirection()){
                reverse_stations = s;
            }
            
        }
        for (int j = 0; j < active_trains.size(); ++j){
            check10km(active_trains[j]);
        }
    }
    cout << "\nEND SIMULATION\n" << endl;
}

void Line::check10km(Train& t){
    
    /* La funzione check10km() controlla che i treni abbiano una distanza tra loro superiore ai 10km. */
    
    for (int i = 0; i < active_trains.size(); i++){
        
        //Controllo effettuato con 15 per evitare che vadano oltre ai 10 km di distanza.
        if (((active_trains[i].getDistance() - t.getDistance()) <= 15 && (active_trains[i].getDistance() - t.getDistance() > 0)) && (active_trains[i].isDirection() == t.isDirection()) && (active_trains[i].getBinary() == 0)){
            t.setCurrSpeed(active_trains[i].getCurrSpeed());
        }
    }
}