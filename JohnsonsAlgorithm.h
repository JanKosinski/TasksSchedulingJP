//
// Created by Loczi94 on 2017-01-05.
//

#ifndef TASKSSCHEDULING_JOHNSONSALGORITHM_H
#define TASKSSCHEDULING_JOHNSONSALGORITHM_H

#include "Task.h"
#include <vector>

class JohnsonsAlgorithm {
    private:
        int Cj;
    public:
        int getCj();
        void setCj(int value);
        std::vector <Task> lineupJA;
        static  void  createLineupJA();
        //static std::vector <Task> createLineupJA();
};

#endif //TASKSSCHEDULING_JOHNSONSALGORITHM_H
