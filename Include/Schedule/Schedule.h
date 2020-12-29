/*
 * @author Giacomo Checchini
 * n.m. 1216347
 */
#include<iostream>
#ifndef ASSEGNAMENTO_2_SCHEDULE_H
#define ASSEGNAMENTO_2_SCHEDULE_H
struct Entry {
   
   int train_number; //numero identificativo del treno
   int start; //0 se parte da stazione origine, 1 se parte da capolinea
   int train_type; //0 se regionale, 1 se alta velocità, 2 se alta velocità super
   vector<int> path; //vector che contiene gli orari delle fermate nelle varie stazioni
}
class Schedule {
   public:
   //class constructor
   Schedule(); //dentro deve prendere time tables txt
   
   //class destructor
   ~Schedule();
   
   
   private:
   vector<Entry> timetable;//struttura dati che contiene le varie partenze 
   int size; //
}

#endif //ASSEGNAMENTO_2_SCHEDULE_H