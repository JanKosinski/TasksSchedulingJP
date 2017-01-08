//
// Created by Jan Kosinski on 27.12.2016.
//
#include <vector>
#ifndef TASKSSCHEDULING_LINEUP_H
#define TASKSSCHEDULING_LINEUP_H


#include "Task.h"

class Lineup {
    private:
        int cj; // minimalizowany parametr. Suma czasów zakończenia zadań
    public:
        int getCj();
        void setCj(int value);
        std::vector<Task>lineup;
        void createLineup(std::vector<int>tasksOrder);  //tworzy uszeregowanie (przypisuje czasy rozpoczecia i zakonczenia) na podstawie kolejnosci zadan. Np. 2, 3,7,1 oznacza ze najpierw zadanie 2, potem przerwa o id 3 itp, itd...
};


#endif //TASKSSCHEDULING_LINEUP_H
