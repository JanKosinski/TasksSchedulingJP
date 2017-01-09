//
// Created by Jan Kosinski on 27.12.2016.
// Plik zawierający parametry uruchamiania algorytmu
//

#ifndef TASKSSCHEDULING_PARAMETERS_H
#define TASKSSCHEDULING_PARAMETERS_H

#include "Task.h"
#include "Generator.h"
//#include <generate.cpp>
#include <vector>

using namespace std;

extern std::vector <Task> tasks;

extern int numOfTasks;     //liczba zadań
extern int numOfBreaks;     //liczba przerw technicznych (okresow niedostepnosci)
extern int breaksLen;       //czas trwania przerw
extern int maxTaskLen;      //maksymalny czas trwania jednej operacji zadania
extern int maxDistBetweenBreaks;    //maksymalny czas x po ukonczeniu jednego okresu niedostepnosci, po ktorym musi zaczac sie nastepny

//algorytm genetyczny
extern int populationSize; //rozmiar populacji
extern int minPopulationSize; //liczebnosc populacji nie moze spasc ponizej tego poziomu

#endif //TASKSSCHEDULING_PARAMETERS_H
