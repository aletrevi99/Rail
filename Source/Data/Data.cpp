#include "Data.h"

#include <stdexcept>
#include <string>
#include <sstream> 
#include <fstream>
#include <cmath>
#include <iterator>
#include <algorithm>

using namespace std;
//costruttore
Data::Data() {
   number_of_principal_stations = 0;
   number_of_local_stations = 0;
   number_of_regional_trains = 0;
   number_of_highspeed_trains = 0;
   number_of_superhighspeed_trains = 0;
   flag = false;
   readStations();
   readTrains();

   if(flag)
      print();
}

//metodi pubblici

void Data::print(){
   
   for(int i = 0; i < tr.size(); i++)
      cout << tr[i] << endl;
}

vector<Train>& Data::getTrains() const{
   return tr;
}

vector<Station>& Data::getStation() const{
   return st;
}
vector<int>& Data::getDistances() const{
   return distances;
}
vector<int>& Data::getPrincipalDistances() const{
   return principal_distances;
}
//metodi privati

void Data::readStations(){
   
   ifstream file;
   file.open("C:/LDP/LDP/TrainLine/line_description.txt");
   if(file.is_open())
   cout<<":)"<<endl;
   string line = "";
   
   string name_station = "";
   int type_station = 0;
   int distance = 0;
   int previous_distance = 0;
   
   getline(file,line);     
                                                 //aggiungo la stazione origine al vector
   name_station = line;
   Principal_Station s(name_station,0);
   st.push_back(s);
   number_of_principal_stations++;
   while(getline(file,line)){
      
      name_station = line.substr(0, line.rfind(" ") - 2);
      type_station = stoi(line.substr(line.rfind(" ") - 1,1));
      
      if(!((type_station == 0)||(type_station == 1)))
         throw exception();
         
      distance = stoi(line.substr(line.rfind(" ") + 1));
      
       if((distance <= 0)||((distance - previous_distance) < 0))
          throw exception();
         
      if(!((distance - previous_distance) < 20)){ 
         
         if(type_station == 0) { 
            Principal_Station sp(name_station,distance);
            st.push_back(sp);
            distances.push_back(distance - previous_distance);
            if(number_of_principal_stations == 1)
               principal_distances.push_back(distance);
            else
               principal_distances.push_back(distance - principal_distances.back());
            previous_distance = distance;
            number_of_principal_stations++;
         }
         else {
            Local_Station sl(name_station,distance);
            st.push_back(sl);
            distances.push_back(distance - previous_distance);
            previous_distance = distance;
            number_of_local_stations++;
         } 
      }
   }
   
   file.close();
}
void Data::readTrains(){
   
   ifstream file;
   file.open("C:/LDP/LDP/TrainLine/timetables.txt");
   if(file.is_open())
   cout<<":)"<<endl;
   string line;
   int train_code;
   int train_type;
   int train_direction;
   int min;
   vector<int> path;
   
   while(getline(file,line)){
      stringstream ss(line);
      
      while (!ss.eof()) { 
         ss >> train_code; 
         ss >> train_direction;
         ss >> train_type;
         while(!ss.eof()){
            ss >> min;
            path.push_back(min);
         }
      }
      //controlli su tipo nome e campo
      if(!((train_direction == 0) || (train_direction == 1)))
         throw exception();
      
      if(!((train_type == 1) || (train_type == 2) || (train_type == 3)))
         throw exception(); 

      bool direction = false;
      if(train_direction == 0)
         direction = true;
      
      //controllo su orari di arrivo
      pathChecker(path,train_type,train_direction);
      
      if(train_type == 1){
         Regional_Train t1(train_code, direction, path);
         tr.push_back(t1);
      }
      else if(train_type == 2){
         High_Speed_Train t2(train_code, direction,path);
         tr.push_back(t2);
      }
      else{
         Super_High_Speed_Train t3(train_code, direction,path);
         tr.push_back(t3);   
      }
   path.clear();
   }
   file.close();
}
void Data::pathChecker(vector<int>& p, int t, int dir){
   
   int min_time = 0;
   int time = 0;
   
   int psize = p.size();
   
   if(t == 1) {
      vector<int> tmp = distances;
      if(dir == 1)
         reverse(tmp.begin(),tmp.end());
       
      int tot_stations =  number_of_principal_stations + number_of_local_stations;
      for(int i = 1; i < tot_stations; i++){
         if(i < psize) {                                                             
            min_time = round(((((double) tmp[i - 1] - 10)/160) * 60) + ((10/80) * 60));
            time = p[i] - p[i - 1];
            if(min_time >= time) {
               p[i] = p[i - 1] + min_time + 10;
               flag = true;
            }
         }   
         else{
            min_time = round(((((double) tmp[i - 1] - 10)/160) * 60) + ((10/80) * 60)) + 10 + p.back();
            p.push_back(min_time);
            flag = true;
         } 
      }
   }
   
   if(t == 2) {
       vector<int> tmp = principal_distances;
       if(dir == 1)
          reverse(tmp.begin(),tmp.end());
      int tot_stations =  number_of_principal_stations;
      for(int i = 1; i < tot_stations; i++){
         if(i < psize) {                                                             
            min_time = round(((((double) tmp[i - 1] - 10)/240) * 60) + ((10/80) * 60));
            if(min_time >= (p[i] - p[i - 1])){
               p[i] = p[i - 1] + min_time + 10;
               flag = true; 
            }
         }  
         else {
            min_time = round(((((double) tmp[i - 1] - 10)/240) * 60) + ((10/80) * 60)) + 10 + p.back();
            p.push_back(min_time);
            flag = true;
         } 
      }
   }
   
 
   if(t == 3) {
      
      vector<int> tmp = principal_distances;
      if(dir == 1)
         reverse(tmp.begin(),tmp.end());
      
      int tot_stations =  number_of_principal_stations;
      for(int i = 1; i < tot_stations; i++){
         if(i < psize) {                                                             
            min_time = round(((((double) tmp[i - 1] - 10)/300) * 60) + ((10/80) * 60));
            if(min_time >= (p[i] - p[i - 1])) {
               p[i] = p[i - 1] + min_time + 10;
               flag = true;  
            }
         }
         else{
            min_time = round(((((double) tmp[i - 1] - 10)/300) * 60) + ((10/80) * 60)) + 10 + p.back();
            p.push_back(min_time);
            flag = true;
         } 
      }
   }
}  


