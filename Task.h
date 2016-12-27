//
// Created by Jan Kosinski on 27.12.2016.
//
#include "Event.h"

#ifndef TASKSSCHEDULING_TASK_H
#define TASKSSCHEDULING_TASK_H


class Task: public Event {
    private:
        int begin_1m;
        int len_1m;
    public:
        Task(int len_1m, int len_2m);   //konstruktor
        int getBeginning_1m();  //pobiera czas rozpoczecia  zadania na 1 maszynie
        void setBeginning_1m(int newBeginning); //ustawia czas rozpoczecia zadania na 1 maszynie
        int getLen_1m();    //pobiera czas trwania zadania na 1 maszynie
        virtual int getBeginning_2m();  //patrz klasa Event
        virtual void setBeginning_2m(int newBeginning); //patrz klasa Event
        virtual int getLen_2m();    //patrz klasa Event
};


#endif //TASKSSCHEDULING_TASK_H
