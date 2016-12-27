//
// Created by Jan Kosinski on 27.12.2016.
//

#ifndef TASKSSCHEDULING_TECHNICALBREAK_H
#define TASKSSCHEDULING_TECHNICALBREAK_H


#include "Event.h"

class TechnicalBreak: public Event {
    public:
        TechnicalBreak(int len);
        int doNothing();   //nic nie robi. Test
        int getBeginning_2m();  //patrz klasa Event
        void setBeginning_2m(int newBeginning); //patrz klasa Event
        int getLen_2m();    //patrz klasa
        int getBeginning_1m();  //patrz klasa Event
        void setBeginning_1m(int newBeginning); //patrz klasa Event
        int getLen_1m();    //patrz klasa Event
};


#endif //TASKSSCHEDULING_TECHNICALBREAK_H
