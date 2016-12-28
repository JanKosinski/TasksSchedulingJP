//
// Created by Jan Kosinski on 27.12.2016.
//

#ifndef TASKSSCHEDULING_TASK_H
#define TASKSSCHEDULING_TASK_H


class Task{
    private:
        int id;
        int begin_1m;
        int len_1m;
        int begin_2m;
        int len_2m;
        bool task;      //jezeli przerwa to false, zadanie to true
    public:
        Task(int len_1m, int len_2m, bool _task);   //konstruktor
        int getBeginning_1m();  //pobiera czas rozpoczecia  zadania na 1 maszynie
        void setBeginning_1m(int newBeginning); //ustawia czas rozpoczecia zadania na 1 maszynie
        int getLen_1m();    //pobiera czas trwania zadania na 1 maszynie
        int getBeginning_2m();  //patrz klasa Event
        void setBeginning_2m(int newBeginning); //patrz klasa Event
        int getLen_2m();    //patrz klasa Event
        int getId();
        void setId(int id);
        bool isItTask();
};


#endif //TASKSSCHEDULING_TASK_H
