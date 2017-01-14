//
// Created by Jan Kosinski on 27.12.2016.
// Funkcje zawarte w tym pliku nie zostaly przetestowane. JKO 28.12.2016
// Podstawowe testy zostaly przeprowadzone. Nie wykazaly bledow. JKO 29.12.2016
//

#include "Lineup.h"
#include "parameters.h"
#include <iostream>

std::vector<int> toTasksOrder(Lineup currentLineup) {
    std::vector<int>myNewOrder;
    for (int i = 0; i<currentLineup.lineup.size(); i++) {
        myNewOrder.push_back(currentLineup.lineup[i].getId());
    }
    return myNewOrder;
}

void Lineup::setCj(int value) {
    this->cj = value;
}

int Lineup::getCj() {
    return this->cj;
}

bool checkDistanceBetweenTechnicalBreaks(vector<Task>lineup) { // funkcja sprawdza czy maksymalny odstep x pomiedzy przerwami jest zachowany
    int prvBreakEnd = 0;
    for (int i = 0; i<lineup.size(); i++) {
        if (!lineup[i].isItTask()) {
            if (prvBreakEnd!=0 && (lineup[i].getBeginning_2m()-prvBreakEnd)>maxDistBetweenBreaks) {
                return false;
            }
            prvBreakEnd = lineup[i].getBeginning_2m()+lineup[i].getLen_2m();
        }
    }
    return true;
}

vector<int> swapTasks(vector<int>inputOrder, int idx1, int idx2) {
    int a = inputOrder[idx1];
    inputOrder[idx1] = inputOrder[idx2];
    inputOrder[idx2] = a;
    return inputOrder;
}

vector<int> changeOrder(Lineup lineup) {
    int prvBreakEnd = 0;
    vector<int>newOrder;
    //vector<int>test;    //TEST
    for (int i = 0; i<lineup.lineup.size(); i++) {
        if (!lineup.lineup[i].isItTask()) {
            if (prvBreakEnd!=0 && (lineup.lineup[i].getBeginning_2m()-prvBreakEnd)>maxDistBetweenBreaks) {
                newOrder = toTasksOrder(lineup);
                newOrder = swapTasks(newOrder, (i-1) , i);
                return newOrder;
            }
            prvBreakEnd = lineup.lineup[i].getBeginning_2m()+lineup.lineup[i].getLen_2m();
        }
    }
    return newOrder;
}

void Lineup::createLineup(std::vector<int> tasksOrder) {
    this->lineup.clear();   //czyscimy poprzednie uszeregowanie. W to miejsce bedziemy zapisywac nowe
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
                this->lineup.push_back(tasks[j]);   // dodajemy zadanie do nowo powstalego uszeregowania
                lastTaskLen_2m = tasks[j].getLen_2m();   //ustawiamy zmienna informujaca nas o czasie trwania ostatniego zadania na 2m
                break;  // jezeli znajdziemy konczymy szukanie
            }
        }
    }

    while (!checkDistanceBetweenTechnicalBreaks(this->lineup)) {
        createLineup(changeOrder(*this));
    }

    // zliczanie sumy czasów zakończenia zadań
    this->setCj(0);
    for (int i = 0 ; i<this->lineup.size(); i++) {
        if (this->lineup[i].isItTask()) {
            this->setCj(this->getCj()+this->lineup[i].getBeginning_2m()+this->lineup[i].getLen_2m());
        }
    }
}

std::vector<int> Lineup::getOrder() {   //zwraca wektor kolejnosci
    std::vector <int>order;
    for (int i = 0; i<this->lineup.size(); i++) {
        order.push_back(this->lineup[i].getId());
    }
    return order;
}
