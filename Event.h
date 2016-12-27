//
// Created by Jan Kosinski on 27.12.2016.
// Klasa nadrzedna dla zadania i przerwy technicznej
//

#ifndef TASKSSCHEDULING_EVENT_H
#define TASKSSCHEDULING_EVENT_H


class Event {
    protected:
        int len_2m;         //czas trwania zdarzenia na drugiej maszynie
        int begin_2m;       //poczatek zdarzenia na drugiej maszynie
    public:
        virtual int getBeginning_2m()=0;    //pobiera czas rozpoczecia sie zdarzenia na drugiej maszynie
        virtual void setBeginning_2m(int newBeginning)=0;   //ustawia czas rozpoczecia sie zdarzenia na drugiej maszynie
        virtual int getLen_2m()=0;          //pobiera czas trwania zdarzenia na drugiej maszynie
        virtual int getBeginning_1m()=0;    //pobiera czas rozpoczecia sie zdarzenia na drugiej maszynie
        virtual void setBeginning_1m(int newBeginning)=0;   //ustawia czas rozpoczecia sie zdarzenia na drugiej maszynie
        virtual int getLen_1m()=0;          //pobiera czas trwania zdarzenia na drugiej maszynie
};


#endif //TASKSSCHEDULING_EVENT_H
