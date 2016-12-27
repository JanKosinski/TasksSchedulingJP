//
// Created by Jan Kosinski on 27.12.2016.
// Plik zawierający parametry uruchamiania algorytmu
//

#ifndef TASKSSCHEDULING_PARAMETERS_H
#define TASKSSCHEDULING_PARAMETERS_H

extern int numOfTasks;     //liczba zadań
extern int numOfBreaks;     //liczba przerw technicznych (okresow niedostepnosci)
extern int breaksLen;       //czas trwania przerw
extern int maxTaskLen;      //maksymalny czas trwania jednej operacji zadania
extern int maxDistBetweenBreaks;    //maksymalny czas x po ukonczeniu jednego okresu niedostepnosci, po ktorym musi zaczac sie nastepny

#endif //TASKSSCHEDULING_PARAMETERS_H
