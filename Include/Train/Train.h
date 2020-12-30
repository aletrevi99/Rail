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
        double getDelay() const;
        bool isDirection() const;
        int getBinary() const;
        bool isStopLocal() const;

        // setter functions
        void setCurrSpeed(int cs);
        void setDistance(double d);
        void setBinary(int bin);

        // true se è a meno di 20km dalla stazione, altrimenti false
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
        // ritardo accumulato dal treno
        double delay;
        // true se va da origine a termine, false se va da termine a origine
        bool direction;
        // binario in entrata stazione. 0 se fuori da stazione. 1 se binario 1 o 3. 2 se binario 2 o 4
        int binary;

        // costruttore
        Train(int tc, int ms, bool dir);
        // distruttore di default
        ~Train() = default;
};


class Regional_Train : public Train
{
    public:
        Regional_Train(int tc, int ms, bool dir) : Train(tc, 160, dir) {};

};

class High_Speed_Train : public Train
{
    public:
        High_Speed_Train(int tc, int ms, bool dir) : Train(tc, 240, dir) {};

};

class Super_High_Speed_Train : public Train
{
    public:
        Super_High_Speed_Train(int tc, int ms, bool dir) : Train(tc, 300, dir) {};

};

#endif //ASSEGNAMENTO_2_TRAIN_H

//Alessandro Trevisan 1221819