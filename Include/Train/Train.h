//Alessandro Trevisan 1221819

#ifndef ASSEGNAMENTO_2_TRAIN_H
#define ASSEGNAMENTO_2_TRAIN_H


class Train
{
    public:
        // disabilito costruttore di copia e operatore di assegnamento di copia
        Train(const Train&) = delete;
        Train& operator=(const Train&) = delete;

        // getter functions
        int getTrainCode() const;
        int getMaxSpeed() const;
        int getCurrSpeed() const;
        double getDistance() const;

        // setter functions
        bool isStopLocal() const;
        void setCurrSpeed(int cs);
        void setDistance(double d);

        // segnalazione a stazione -20km
        virtual bool signal();



    protected:
        // codice del treno
        const int trainCode;
        // velocità massima del treno: 160km\h regionale; 240km\h alta velocità; 300km\h super alta velocità
        const int maxSpeed;
        // velocità di crociera
        int currSpeed;
        // distanza dalla stazione
        double distance;
        // variabile per indicare se si ferma nelle stazioni locali (solo i treni regionali)
        bool stopLocal;
        // ritardo accumulato
        double delay;



        // costruttore
        Train(int tc, int ms);
        // distruttore di default
        ~Train() = default;
};


class Regional_Train : public Train
{
    public:
        Regional_Train(int tc, int ms) : Train(tc, 160) {};

};

class High_Speed_Train : public Train
{
    public:
        High_Speed_Train(int tc, int ms) : Train(tc, 240) {};

};

class Super_High_Speed_Train : public Train
{
    public:
        Super_High_Speed_Train(int tc, int ms) : Train(tc, 300) {};

};

#endif //ASSEGNAMENTO_2_TRAIN_H

//Alessandro Trevisan 1221819