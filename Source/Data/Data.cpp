/*
 * @author Giacomo Checchini
 * n.m. 1216347
 */

#include "Data.h"

using namespace std;

//costruttore
Data::Data() {
   number_of_principal_stations = 0;
   number_of_local_stations = 0;
   flag = false;

   readStations();
   readTrains();
   sort();
   last_arrival = findLastArrival();
   reversedStationFiller();

   if (flag)
      print();
}

//metodi pubblici

void Data::print() {

   for (auto &i : tr)
      cout << i << endl;
}

vector<Train> &Data::getTrains() {
   return tr;
}

vector<Station> &Data::getStation() {
   return st;
}

vector<Station> &Data::get_reversed_Station() {
   return rev_st;
}

vector<int> Data::getPrincipalDistances() const {
   return principal_distances;
}

int Data::getLastArrival() const {
   return last_arrival;
}

//metodi privati
void Data::readStations() {

   ifstream file;
   file.open("../line_description.txt");
   if (file.is_open())
      cout << "\nline_description.txt aperto con successo.";
   if (!file.is_open())
      cout << "\nline_description.txt non trovato. Prova a controllare la directory di appartenenza.";
   string line;

   string name_station;
   int type_station = 0;
   int distance = 0;
   int previous_distance = 0;
   int previous_principal_distances = 0;

   getline(file, line);

   name_station = line;
   Principal_Station s(name_station, 0);
   st.push_back(s);   //aggiungo la stazione origine al vector
   number_of_principal_stations++;
   while (getline(file, line)) {

      name_station = line.substr(0, line.rfind(' ') - 2);
      type_station = stoi(line.substr(line.rfind(' ') - 1, 1));


      distance = stoi(line.substr(line.rfind(' ') + 1));


      if (((distance - previous_distance) >= 20) && ((type_station == 0) || (type_station == 1)) && !((distance <= 0) || ((distance - previous_distance) < 0))) {

         if (type_station == 0) {
            Principal_Station sp(name_station, distance);
            st.push_back(sp);
            distances.push_back(distance - previous_distance);
            if (number_of_principal_stations == 1) {
               principal_distances.push_back(distance);
               previous_principal_distances = distance;
            } else {
               principal_distances.push_back(distance - previous_principal_distances);
               previous_principal_distances = distance;
            }
            previous_distance = distance;
            number_of_principal_stations++;
         } else {
            Local_Station sl(name_station, distance);
            st.push_back(sl);
            distances.push_back(distance - previous_distance);
            previous_distance = distance;
            number_of_local_stations++;
         }
      }
   }

   file.close();
}

void Data::readTrains() {

   ifstream file;
   file.open("../timetables_3.txt");
   if (file.is_open())
      cout << "\ntimetables.txt aperto con successo.\n" << endl;
   if (!file.is_open())
      cout << "\ntimetables.txt non trovato. Prova a controllare la directory di appartenenza.\n" << endl;
   string line;
   int train_code;
   int train_type;
   int train_direction;
   int min;
   int n = 0;
   vector<int> path;

   while (getline(file, line)) {
      stringstream ss(line);

      while (!ss.eof()) {
         ss >> train_code;
         ss >> train_direction;
         ss >> train_type;

         n = number_of_principal_stations;

         if (train_type == 1)
            n += number_of_local_stations;

         while (!ss.eof()) {
            ss >> min;
            if(min >= 0)
               path.push_back(min);
         }
      }

      if (n < path.size())
         path.resize(n);


      //per inserire correttamente il campo su train
      bool direction = false;
      if (train_direction == 0)
         direction = true;

      //controllo su orari di arrivo
      pathChecker(path, train_type, train_direction);

      if (((train_type == 1) || (train_type == 2) || (train_type == 3)) && ((train_direction == 0) || (train_direction == 1)))
      {
          if (train_type == 1)
          {
              Regional_Train t1(train_code, direction, path);

              if (t1.getPath()[0] <= 1440)
                  tr.push_back(t1);
          } else if (train_type == 2)
          {
              High_Speed_Train t2(train_code, direction, path);

              if (t2.getPath()[0] <= 1440)
                  tr.push_back(t2);
          } else
          {
              Super_High_Speed_Train t3(train_code, direction, path);

              if (t3.getPath()[0] <= 1440)
                  tr.push_back(t3);
          }
      }
       path.clear();
   }
   file.close();
}

void Data::pathChecker(vector<int> &p, int t, int dir) {

   int min_time = 0;
   int time = 0;

   int psize = p.size();

   if (t == 1) {
      vector<int> tmp = distances;
      if (dir == 1)
         reverse(tmp.begin(), tmp.end());

      int tot_stations = number_of_principal_stations + number_of_local_stations;
      for (int i = 1; i < tot_stations; i++) {
         if (i < psize) {
            min_time = round(((((double) tmp[i - 1] - 10) / 160) * 60) + ((10.0 / 80) * 60));
            time = p[i] - p[i - 1];
            if (min_time >= time) {
               p[i] = p[i - 1] + min_time + 5;
               if (i == 1)
                  p[i] = p[i] - 5;
               flag = true;
            }
         } else {
            min_time = round(((((double) tmp[i - 1] - 10) / 160) * 60) + ((10.0 / 80) * 60)) + 15 + p.back();
            if (i == 1)
               min_time = min_time - 5;
            p.push_back(min_time);
            flag = true;
         }
      }
   }

   if (t == 2) {
      vector<int> tmp = principal_distances;
      if (dir == 1)
         reverse(tmp.begin(), tmp.end());
      int tot_stations = number_of_principal_stations;
      for (int i = 1; i < tot_stations; i++) {
         if (i < psize) {
            min_time = round(((((double) tmp[i - 1] - 10) / 240) * 60) + ((10.0 / 80) * 60));
            if (min_time >= (p[i] - p[i - 1])) {
               p[i] = p[i - 1] + min_time + 5;
               if (i == 1)
                  p[i] = p[i] - 5;
               flag = true;
            }
         } else {
            min_time = round(((((double) tmp[i - 1] - 10) / 240) * 60) + ((10.0 / 80) * 60)) + 15 + p.back();
            if (i == 1)
               min_time = min_time - 5;
            p.push_back(min_time);
            flag = true;
         }
      }
   }


   if (t == 3) {

      vector<int> tmp = principal_distances;
      if (dir == 1)
         reverse(tmp.begin(), tmp.end());

      int tot_stations = number_of_principal_stations;
      for (int i = 1; i < tot_stations; i++) {
         if (i < psize) {
            min_time = round(((((double) tmp[i - 1] - 10) / 300) * 60) + ((10.0 / 80) * 60));
            if (min_time >= (p[i] - p[i - 1])) {
               p[i] = p[i - 1] + min_time + 5;
               if (i == 1)
                  p[i] = p[i] - 5;
               flag = true;
            }
         } else {
            min_time = round(((((double) tmp[i - 1] - 10) / 300) * 60) + ((10.0 / 80) * 60)) + 15 + p.back();
            if (i == 1)
               min_time = min_time - 5;
            p.push_back(min_time);
            flag = true;
         }
      }
   }
}

void Data::sort() {

   int min = 0;
   for (int i = 0; i < tr.size(); i++) {
      min = i;

      for (int j = i + 1; j < tr.size(); j++)
         if (tr[j].isFirst(tr[min]))
            min = j;

      Train tmp = tr[min];
      tr[min] = tr[i];
      tr[i] = tmp;
   }
}

int Data::findLastArrival() {

   int max = 0;
   vector<int> tmp;

   for(auto & i : tr)
      tmp.push_back(i.getPath().back());

   std::sort(tmp.begin(), tmp.end());

   max = tmp.back();

   return max;
};

void Data::reversedStationFiller() {

   rev_st = st;   //riempimento del vettore di stazioni rovesciato
   int n = number_of_local_stations + number_of_principal_stations;
   int m = rev_st[n - 1].getStationDistance();
   reverse(rev_st.begin(), rev_st.end());

   for (int i = 0; i < n; i++)
       rev_st[i].setStationDistance(m - rev_st[i].getStationDistance());
}