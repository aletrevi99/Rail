//Alessandro Trevisan 1221819

#ifndef ASSEGNAMENTO_2_TRAIN_H
#define ASSEGNAMENTO_2_TRAIN_H

#include "vector"

class Train
{
    public:
        // getter functions
        int getTrainCode() const;
        int getMaxSpeed() const;
        int getCurrSpeed() const;
        double getDistance() const;
        double getDelay() const;
        bool isDirection() const;
        int getBinary() const;
        bool isStopLocal() const;
        int getType() const;
        const std::vector<int> &getPath() const;

        // setter functions
        void setCurrSpeed(int cs);
        void setDistance(double d);
        void setBinary(int bin);
        void setPath(const std::vector<int> &path);


    protected:
        // costruttore
        Train(int tc, bool dir, const std::vector<int>& p);

        // codice del treno
        const int trainCode;
        // velocità di crociera
        int currSpeed;
        // distanza dalla stazione
        double distance;
        // ritardo accumulato dal treno
        double delay;
        // true se va da origine a termine, false se va da termine a origine
        bool direction;
        // binario in entrata stazione. 0 se fuori da stazione. 1 a 4 se binari
        int binary;
        // velocità massima del treno: 160km\h regionale; 240km\h alta velocità; 300km\h super alta velocità
        int maxSpeed = 0;
        // variabile per indicare se si ferma nelle stazioni locali (solo i treni regionali)
        bool stopLocal = false;
        // tipologia treno. 1 regionale, 2 alta velocità, 3 super alta velocità
        int type = 0;
        // vettore degli orari di arrivo
        std::vector<int> path;
};

// overload operatore < per ordinare i treni a seconda della loro velcità
bool operator<(const Train&, const Train&);

class Regional_Train : public Train
{
    public:
        Regional_Train(int tc, bool dir, const std::vector<int>& p);
};

class High_Speed_Train : public Train
{
    public:
        High_Speed_Train(int tc, bool dir, const std::vector<int>& p);
};

class Super_High_Speed_Train : public Train
{
    public:
        Super_High_Speed_Train(int tc, bool dir, const std::vector<int>& p);
};

#endif //ASSEGNAMENTO_2_TRAIN_H

//Alessandro Trevisan 1221819