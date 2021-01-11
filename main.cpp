/*
 * Studente: Ghiotto Andrea
 * Matricola: 1216363
 * Corso: Laboratorio di Programmazione
 * Anno: 2°
 * Scuola: Ing. Informatica - UniPd
 * Data di creazione: 31/12/2020
*/

#include "Line.h"

using namespace std;
int main(){
    
    /* Viene utilizzato questo main per verificare il corretto funzionamento della linea ferroviaria.
     * Dopo aver creato un oggetto della classe Line, infatti, viene chiamata la funzione simulation che simula
     * il funzionamento della linea ferroviaria nell'arco della giornata. */
    
    Line l;
    l.simulation();
    
    return 0;
}