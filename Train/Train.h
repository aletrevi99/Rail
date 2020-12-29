#ifndef ASSEGNAMENTO_2_TRAIN_H
#define ASSEGNAMENTO_2_TRAIN_H


class Train
{
    public:

        Train(const Train&) = delete;
        Train& operator=(const Train&) = delete;


    protected:
        Train() = default;
        ~Train() = default;
};


#endif //ASSEGNAMENTO_2_TRAIN_H