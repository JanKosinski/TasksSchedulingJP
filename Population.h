//
// Created by Jan Kosinski on 08.01.2017.
//

#ifndef TASKSSCHEDULING_POPULATION_H
#define TASKSSCHEDULING_POPULATION_H
#include "parameters.h"
#include <algorithm>
#include "Task.h"
#include <vector>
#include "Lineup.h"



class Population {
    public:
        std::vector<Lineup>lineups;
        std::vector<int>probabilities; //prawdopodobieństwa z jakimi uszeregowania przejda dalej
        void createRandomPopulation();
        void selection();
        void sortPopulation();  //sortowanie populacji wg przystosowania
        void hybridization();   // w pliku hybridization.cpp . Inaczej powodowalo tajemnicze bledy
        void createProbabilities();
};


#endif //TASKSSCHEDULING_POPULATION_H
