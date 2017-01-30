//
// Created by Loczi94 on 2017-01-24.
//

#ifndef TASKSSCHEDULING_EXACTALGORITHM_H
#define TASKSSCHEDULING_EXACTALGORITHM_H

#include "Task.h"
#include <vector>

class ExactAlgorithm {
private:
    int Cj;
    int theBestCj;
public:
    void setCj(int value);
    int getCj();
    void setTheBestCj(int value);
    int getTheBestCj();
    std::vector <Task> lineupEA;
    std::vector <Task> theBestLineupEA;
    void generatePermutations(std::vector <int> order, int pointer);
    void setValues(std::vector<int> tasksOrder);
    void printLineup();
    //void deleteEmptyBreaks();
};

#endif //TASKSSCHEDULING_EXACTALGORITHM_H
