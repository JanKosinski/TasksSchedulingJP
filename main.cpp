#include <iostream>
#include "parameters.h"
#include <vector>
#include "Lineup.h"
#include "Task.h"
#include <time.h>
#include <cstdlib>
#include "Generator.h"
#include "JohnsonsAlgorithm.h"

using namespace std;

//int maxDistBetweenBreaks = 0;
#include "Population.h"


void test1() {
    //testowane dla maxDistBetweenBreaks = 3. test ok!
    Lineup *lineup = new Lineup();

    Task *task1 = new Task(1,1,2,true);
    Task *task2 = new Task(2,3,1,true);
    Task *task3 = new Task(3,4,1,true);
    Task *task4 = new Task(4,5,2,true);
    Task *break1 = new Task(5,0,3,false);
    Task *break2 = new Task(6,0,3,false);

    lineup->lineup.push_back(*task1);
    lineup->lineup.push_back(*task2);
    lineup->lineup.push_back(*task3);
    lineup->lineup.push_back(*task4);
    lineup->lineup.push_back(*break1);
    lineup->lineup.push_back(*break2);

    vector<int>tasksOrder;
    tasksOrder.push_back(3);
    tasksOrder.push_back(5);
    tasksOrder.push_back(1);
    tasksOrder.push_back(2);
    tasksOrder.push_back(6);
    tasksOrder.push_back(4);
    lineup->createLineup(tasksOrder);

    for (int i =0; i<lineup->lineup.size(); i++) {
        cout<<"Task: "<<lineup->lineup[i].getId()<<". Start_1m: "<<lineup->lineup[i].getBeginning_1m()<<". Start_2m: "<<lineup->lineup[i].getBeginning_2m()<<". Time_1m: "<<lineup->lineup[i].getLen_1m()<<". Time_2m: "<<lineup->lineup[i].getLen_2m()<<endl;
    }
}

void test2() {
    //testowane dla maxDistBetweenBreaks = 0. Test ok!
    Lineup *lineup = new Lineup();

    Task *task1 = new Task(1,5,3,true);
    Task *task2 = new Task(2,1,4,true);
    Task *task3 = new Task(3,2,6,true);
    Task *task4 = new Task(4,1,1,true);
    Task *break1 = new Task(5,0,6,false);
    Task *break2 = new Task(6,0,6,false);

    lineup->lineup.push_back(*task1);
    lineup->lineup.push_back(*task2);
    lineup->lineup.push_back(*task3);
    lineup->lineup.push_back(*task4);
    lineup->lineup.push_back(*break1);
    lineup->lineup.push_back(*break2);

    vector<int>tasksOrder;
    tasksOrder.push_back(1);
    tasksOrder.push_back(2);
    tasksOrder.push_back(5);
    tasksOrder.push_back(4);
    tasksOrder.push_back(3);
    tasksOrder.push_back(6);
    lineup->createLineup(tasksOrder);

    for (int i =0; i<lineup->lineup.size(); i++) {
        cout<<"Task: "<<lineup->lineup[i].getId()<<". Start_1m: "<<lineup->lineup[i].getBeginning_1m()<<". Start_2m: "<<lineup->lineup[i].getBeginning_2m()<<". Time_1m: "<<lineup->lineup[i].getLen_1m()<<". Time_2m: "<<lineup->lineup[i].getLen_2m()<<endl;
    }
}

int main() {
    srand( time( NULL) );
    //test2();
    Generator::generate();
    //JohnsonsAlgorithm::createLineupJA();
    Population *population = new Population();
    population->createRandomPopulation();

    return 0;
}