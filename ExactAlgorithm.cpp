//
// Created by Loczi94 on 2017-01-24.
//

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "ExactAlgorithm.h"
#include "parameters.h"
#include "Task.h"

using namespace std;

void ExactAlgorithm::setCj(int value) {
    this->Cj = value;
}

int ExactAlgorithm::getCj() {
    return this->Cj;
}

void ExactAlgorithm::setTheBestCj(int value) {
    this->theBestCj = value;
}

int ExactAlgorithm::getTheBestCj() {
    return this->theBestCj;
}


std::vector<int> toTasksOrder(ExactAlgorithm EA) {
    std::vector<int>myNewOrder;
    for (int i = 0; i<EA.lineupEA.size(); i++) {
        myNewOrder.push_back(EA.lineupEA[i].getId());
    }
    return myNewOrder;
}

bool checkDistanceBetweenTechnicalBreaksEA(vector<Task>lineup) { // funkcja sprawdza czy maksymalny odstep x pomiedzy przerwami jest zachowany
    int prvBreakEnd = 0;
    for (int i = 0; i<lineup.size(); i++) {
        if (!lineup[i].isItTask()) {
            //if (prvBreakEnd!=0 && (lineup[i].getBeginning_2m()-prvBreakEnd)>maxDistBetweenBreaks) {
            if ((lineup[i].getBeginning_2m()-prvBreakEnd)>maxDistBetweenBreaks) {
                return false;
            }
            prvBreakEnd = lineup[i].getBeginning_2m()+lineup[i].getLen_2m();
        }
    }
    return true;
}

vector<int> swapTasksEA(vector<int>inputOrder, int idx1, int idx2) {
    int a = inputOrder[idx1];
    inputOrder[idx1] = inputOrder[idx2];
    inputOrder[idx2] = a;
    return inputOrder;
}

vector<int> changeOrder(ExactAlgorithm EA) {
    int prvBreakEnd = 0;
    vector<int>newOrder;
    for (int i = 0; i<EA.lineupEA.size(); i++) {
        if (!EA.lineupEA[i].isItTask()) {
            //if (prvBreakEnd!=0 && (JA.lineupJA[i].getBeginning_2m()-prvBreakEnd)>maxDistBetweenBreaks) {
            if ((EA.lineupEA[i].getBeginning_2m()-prvBreakEnd)>maxDistBetweenBreaks) {
                newOrder = toTasksOrder(EA);
                newOrder = swapTasksEA(newOrder, (i-1) , i);
                return newOrder;
            }
            prvBreakEnd = EA.lineupEA[i].getBeginning_2m()+EA.lineupEA[i].getLen_2m();
        }
    }
    return newOrder;
}


void ExactAlgorithm::setValues(std::vector<int> tasksOrder) {
    this->lineupEA.clear();   //czyscimy poprzednie uszeregowanie. W to miejsce bedziemy zapisywac nowe
    int currentTime = 0;    // czas zakonczenia ostatniego zadania na pierwszej maszynie
    int lastTaskLen_2m = 0;  // czas trwania ostatniego zadania na 2 maszynie
    for (int i = 0; i<tasksOrder.size(); i++) {     // iterujemy po wektorze reprezentujacym kolejnosc zadan
        for (int j = 0; j<tasks.size(); j++) {   // szukamy w biezacym uszeregowaniu zdania o id takim samym jak w wektorze reprezentujacym kolejnosc
            if (tasksOrder[i] == tasks[j].getId()) {
                if (lastTaskLen_2m > tasks[j].getLen_1m()) {   // jezeli czas trwania poprzedniego zadania na drugiej maszynie jest wiekszy niz obecnego na pierwszej
                    currentTime += lastTaskLen_2m - tasks[j].getLen_1m(); //trzeba wstawic zadanie tak zeby jego operacja na 2m mogla zaczac sie zaraz po zakonczeniu pierwszej
                }
                tasks[j].setBeginning_1m(currentTime);  //ustawiamy czas rozpoczecia zadania na pierwszej maszynie
                currentTime += tasks[j].getLen_1m();    //ustawiamy zmienna currentTime na czas zakonczenia ostatniego zadania na pierwszej maszynie
                tasks[j].setBeginning_2m(currentTime);  //zmienna currentTime warunkuje od razu kiedy powinno zaczynac sie zadanie na drugiej maszynie
                this->lineupEA.push_back(tasks[j]);   // dodajemy zadanie do nowo powstalego uszeregowania
                lastTaskLen_2m = tasks[j].getLen_2m();   //ustawiamy zmienna informujaca nas o czasie trwania ostatniego zadania na 2m
                break;  // jezeli znajdziemy konczymy szukanie
            }
        }
    }

    /*while (!checkDistanceBetweenTechnicalBreaksEA(this->lineupEA)) {
        setValues(changeOrder(*this));
    }*/

    if (checkDistanceBetweenTechnicalBreaksEA(this->lineupEA)) {
        // zliczanie sumy czasów zakończenia zadań
        this->setCj(0);
        for (int i = 0 ; i<this->lineupEA.size(); i++) {
            if (this->lineupEA[i].isItTask()) {
                this->setCj(this->getCj()+this->lineupEA[i].getBeginning_2m()+this->lineupEA[i].getLen_2m());
            }
        }
        if (theBestLineupEA.size()==0) {
            theBestLineupEA=lineupEA;
            setTheBestCj(this->getCj());
        }
        else if (this->getCj()<this->theBestCj) {
            theBestLineupEA=lineupEA;
            setTheBestCj(this->getCj());
        }
    }

}

void ExactAlgorithm::generatePermutations(std::vector <int> order, int pointer) {
    if (pointer==(order.size()-1)){
        for (int i=0; i<order.size(); i++){
            cout << order[i] << " ";
        }
        cout<< endl;
        ExactAlgorithm::setValues(order);
    }
    for (int i=pointer; i<order.size(); i++) {
        vector <int> permutation = order;
        permutation[pointer] = order[i];
        permutation[i] = order[pointer];
        ExactAlgorithm::generatePermutations(permutation,pointer+1);
    }
}

void ExactAlgorithm::printLineup() {
    for (int i=0; i<theBestLineupEA.size(); i++){
        if (theBestLineupEA[i].isItTask()){
            cout << endl << "Task: " << theBestLineupEA[i].getId() << "\tStart1: " << theBestLineupEA[i].getBeginning_1m() << "\tLen1: " << theBestLineupEA[i].getLen_1m() << "\tStart2: " << theBestLineupEA[i].getBeginning_2m() << "\tLen2: " << theBestLineupEA[i].getLen_2m();
        }
        else{
            cout << endl << "Break: " << theBestLineupEA[i].getId() << "\tStart1: " << theBestLineupEA[i].getBeginning_1m() << "\tLen1: " << theBestLineupEA[i].getLen_1m() << "\tStart2: " << theBestLineupEA[i].getBeginning_2m() << "\tLen2: " << theBestLineupEA[i].getLen_2m();
        }
    }
}

