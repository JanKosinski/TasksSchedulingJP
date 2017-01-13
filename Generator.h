//
// Created by Loczi94 on 2017-01-03.
//

#ifndef TASKSSCHEDULING_GENERATOR_H
#define TASKSSCHEDULING_GENERATOR_H

#include <vector>

class Generator {
public:
    Generator();
    static void generate();
    static void automaticGenerativity();
    static void manualGenerativity();
    static void printTasks();
    static std::vector<Task>returnTasks();
};

#endif //TASKSSCHEDULING_GENERATOR_H