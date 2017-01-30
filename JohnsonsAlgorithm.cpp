//
// Created by Loczi94 on 2017-01-05.
//
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "JohnsonsAlgorithm.h"
#include "parameters.h"
#include "Task.h"

using namespace std;

vector <Task> tasks1;
vector <Task> tasks2;

void JohnsonsAlgorithm::setCj(int value) {
    this->Cj = value;
}

int JohnsonsAlgorithm::getCj() {
    return this->Cj;
}

void quickSort1(int left, int right) {
    int i=left;
    int j=right;
    int pivot=tasks1[rand()%(right-left)+left].getLen_1m();
    do
    {
        while(tasks1[i].getLen_1m()<pivot) i++;
        while(tasks1[j].getLen_1m()>pivot) j--;
        if(i<=j)
        {
            swap(tasks1[i],tasks1[j]);
            i++;
            j--;
        }
    }
    while(i<=j);
    if(left<j) quickSort1(left,j);
    if(right>i) quickSort1(i,right);
}

void quickSort1_1(int left, int right) {
    int i=left;
    int j=right;
    int pivot=tasks1[rand()%(right-left)+left].getLen_2m();
    do
    {
        while(tasks1[i].getLen_2m()<pivot) i++;
        while(tasks1[j].getLen_2m()>pivot) j--;
        if(i<=j)
        {
            swap(tasks1[i],tasks1[j]);
            i++;
            j--;
        }
    }
    while(i<=j);
    if(left<j) quickSort1_1(left,j);
    if(right>i) quickSort1_1(i,right);
}

void quickSort2(int left, int right) {
    int i=left;
    int j=right;
    int pivot=tasks2[rand()%(right-left)+left].getLen_2m();
    do
    {
        while(tasks2[i].getLen_2m()>pivot) i++;
        while(tasks2[j].getLen_2m()<pivot) j--;
        if(i<=j)
        {
            swap(tasks2[i],tasks2[j]);
            i++;
            j--;
        }
    }
    while(i<=j);
    if(left<j) quickSort2(left,j);
    if(right>i) quickSort2(i,right);
}

void quickSort2_2(int left, int right) {
    int i=left;
    int j=right;
    int pivot=tasks2[rand()%(right-left)+left].getLen_1m();
    do
    {
        while(tasks2[i].getLen_1m()>pivot) i++;
        while(tasks2[j].getLen_1m()<pivot) j--;
        if(i<=j)
        {
            swap(tasks2[i],tasks2[j]);
            i++;
            j--;
        }
    }
    while(i<=j);
    if(left<j) quickSort2_2(left,j);
    if(right>i) quickSort2_2(i,right);
}


void printTest() {
    cout << "GROUP1" << endl;
    for (int i =0; i<tasks1.size(); i++) {
        cout<<"Task: "<<tasks1[i].getId()<<" Time_1m: "<<tasks1[i].getLen_1m()<<". Time_2m: "<<tasks1[i].getLen_2m()<<endl;
    }
    cout << "GROUP2" << endl;
    for (int i =0; i<tasks2.size(); i++) {
        cout<<"Task: "<<tasks2[i].getId()<<" Time_1m: "<<tasks2[i].getLen_1m()<<". Time_2m: "<<tasks2[i].getLen_2m()<<endl;
    }

}

void JohnsonsAlgorithm::printLineup() {
    for (int i=0; i<lineupJA.size(); i++){
        if (lineupJA[i].isItTask()){
            cout << endl << "Task: " << lineupJA[i].getId() << "\tStart1: " << lineupJA[i].getBeginning_1m() << "\tLen1: " << lineupJA[i].getLen_1m() << "\tStart2: " << lineupJA[i].getBeginning_2m() << "\tLen2: " << lineupJA[i].getLen_2m();
        }
        else{
            cout << endl << "Break: " << lineupJA[i].getId() << "\tStart1: " << lineupJA[i].getBeginning_1m() << "\tLen1: " << lineupJA[i].getLen_1m() << "\tStart2: " << lineupJA[i].getBeginning_2m() << "\tLen2: " << lineupJA[i].getLen_2m();
        }
    }
}

void JohnsonsAlgorithm::createLineupJA() {
    std::vector<int> order;
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].isItTask()) {
            if (tasks[i].getLen_1m() <= tasks[i].getLen_2m()) {
                tasks1.push_back(tasks[i]);
            } else {
                tasks2.push_back(tasks[i]);
            }
        }
    }
    quickSort1(0, tasks1.size() - 1);
    quickSort2(0, tasks2.size() - 1);
    int left = 0;
    int right;
    for (int i = 0; i < tasks1.size(); i++) {
        if (tasks1[i].getLen_1m() != tasks1[i + 1].getLen_1m()) {
            right = i;
            if (left != right) {
                quickSort1_1(left, right);
            }
            left = i + 1;
        }
    }
    left = 0;
    for (int i = 0; i < tasks2.size(); i++) {
        if (tasks2[i].getLen_2m() != tasks2[i + 1].getLen_2m()) {
            right = i;
            if (left != right) {
                quickSort2_2(left, right);
            }
            left = i + 1;
        }
    }
    printTest();
    for (int i = 0; i < tasks1.size(); i++) {
        order.push_back(tasks1[i].getId());
    }
    for (int i = 0; i < tasks2.size(); i++) {
        order.push_back(tasks2[i].getId());
    }
    for (int i=0; i < tasks.size(); i++) {
        if (!tasks[i].isItTask()) {
            order.push_back(tasks[i].getId());
        }
    }
    setValues(order);
    deleteEmptyBreaks();
}

void JohnsonsAlgorithm::deleteEmptyBreaks(){
    int move=0;
    int space1=0;
    int space2=0;
    int new_beginning_1m;
    int new_beginning_2m;
    int before_break;
    for (int i=0; i<lineupJA.size()-1; i++) {
        if (!lineupJA[i].isItTask() && i!=0) {
            before_break=lineupJA[i-1].getBeginning_1m()+lineupJA[i-1].getLen_1m();
            lineupJA[i].setBeginning_1m(before_break);
        }
        if (lineupJA[i+1].getBeginning_1m()>(lineupJA[i].getBeginning_1m()+lineupJA[i].getLen_1m())){   // Jesli jest pusta przestrzen przed operacja na 1 maszynie
            if (lineupJA[i+1].getBeginning_2m()>(lineupJA[i].getBeginning_2m()+lineupJA[i].getLen_2m())){ // Jesli jest pusta przestrzen przed operacja na 2 maszynie
                space1=lineupJA[i+1].getBeginning_1m()-(lineupJA[i].getBeginning_1m()+lineupJA[i].getLen_1m());
                space2=lineupJA[i+1].getBeginning_2m()-(lineupJA[i].getBeginning_2m()+lineupJA[i].getLen_2m());
                move=min(space1,space2);
                new_beginning_1m=lineupJA[i+1].getBeginning_1m()-move;
                new_beginning_2m=lineupJA[i+1].getBeginning_2m()-move;
                lineupJA[i+1].setBeginning_1m(new_beginning_1m);
                lineupJA[i+1].setBeginning_2m(new_beginning_2m);
            }
        }
    }
}

/////////////////////////////////////////////////////////

std::vector<int> toTasksOrder(JohnsonsAlgorithm JA) {
    std::vector<int>myNewOrder;
    for (int i = 0; i<JA.lineupJA.size(); i++) {
        myNewOrder.push_back(JA.lineupJA[i].getId());
    }
    return myNewOrder;
}

bool checkDistanceBetweenTechnicalBreaksJA(vector<Task>lineup) { // funkcja sprawdza czy maksymalny odstep x pomiedzy przerwami jest zachowany
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

vector<int> swapTasksJA(vector<int>inputOrder, int idx1, int idx2) {
    int a = inputOrder[idx1];
    inputOrder[idx1] = inputOrder[idx2];
    inputOrder[idx2] = a;
    return inputOrder;
}

vector<int> changeOrder(JohnsonsAlgorithm JA) {
    int prvBreakEnd = 0;
    vector<int>newOrder;
    for (int i = 0; i<JA.lineupJA.size(); i++) {
        if (!JA.lineupJA[i].isItTask()) {
            //if (prvBreakEnd!=0 && (JA.lineupJA[i].getBeginning_2m()-prvBreakEnd)>maxDistBetweenBreaks) {
            if ((JA.lineupJA[i].getBeginning_2m()-prvBreakEnd)>maxDistBetweenBreaks) {
                newOrder = toTasksOrder(JA);
                newOrder = swapTasksJA(newOrder, (i-1) , i);
                return newOrder;
            }
            prvBreakEnd = JA.lineupJA[i].getBeginning_2m()+JA.lineupJA[i].getLen_2m();
        }
    }
    return newOrder;
}

void JohnsonsAlgorithm::setValues(std::vector<int> tasksOrder) {
    this->lineupJA.clear();   //czyscimy poprzednie uszeregowanie. W to miejsce bedziemy zapisywac nowe
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
                this->lineupJA.push_back(tasks[j]);   // dodajemy zadanie do nowo powstalego uszeregowania
                lastTaskLen_2m = tasks[j].getLen_2m();   //ustawiamy zmienna informujaca nas o czasie trwania ostatniego zadania na 2m
                break;  // jezeli znajdziemy konczymy szukanie
            }
        }
    }

    while (!checkDistanceBetweenTechnicalBreaksJA(this->lineupJA)) {
        setValues(changeOrder(*this));
    }

    // zliczanie sumy czasów zakończenia zadań
    this->setCj(0);
    for (int i = 0 ; i<this->lineupJA.size(); i++) {
        if (this->lineupJA[i].isItTask()) {
            this->setCj(this->getCj()+this->lineupJA[i].getBeginning_2m()+this->lineupJA[i].getLen_2m());
        }
    }
}

