//
// Created by Jan Kosinski on 27.12.2016.
// Funkcje zawarte w tym pliku nie zostaly przetestowane. JKO 28.12.2016
// Podstawowe testy zostaly przeprowadzone. Nie wykazaly bledow. JKO 29.12.2016
//

#include "Lineup.h"
#include "parameters.h"
#include <iostream>

bool distanceBetweenTechnicalBreaks = false;

void Lineup::setCj(int value) {
    this->cj = value;
}

int Lineup::getCj() {
    return this->cj;
}

std::vector<int> checkDistanceBetweenTechnicalBreaks(std::vector<Task>lineup) { // funkcja sprawdza czy maksymalny odstep x pomiedzy przerwami jest zachowany
    //TODO

}

void Lineup::createLineup(std::vector<int> tasksOrder) {
    std::vector<int>fixedBreaks;    // wektor zawierajacy kolejnosc zadan ze zmianami tak by zachowany byl max odstep x pomiedzy przerwami
    this->lineup.clear();   //czyscimy poprzednie uszeregowanie. W to miejsce bedziemy zapisywac nowe
    int currentTime = 0;    // czas zakonczenia ostatniego zadania na pierwszej maszynie
    int lastTaskLen_2m = 0;  // czas trwania ostatniego zadania na 2 maszynie
    bool test = false;
    for (int i = 0; i<tasksOrder.size(); i++) {     // iterujemy po wektorze reprezentujacym kolejnosc zadan
        test = false;
        for (int j = 0; j<tasks.size(); j++) {   // szukamy w biezacym uszeregowaniu zdania o id takim samym jak w wektorze reprezentujacym kolejnosc
            if (tasksOrder[i] == tasks[j].getId()) {
                test = true;
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
        //TEST
        if(test == false) {
            cout<<endl;
            for (int i = 0; i<tasksOrder.size(); i++) {
                cout<<tasksOrder[i]<<" ";
            }
            cout<<endl;
        }

        //TEST
    }
    //distanceBetweenTechnicalBreaks = false;     //zakladamy ze warunek z odstepami miedzy przerwami nie jest spelniony. Trzeba to sprawdzic
    //TODO napisać przesuwanie przerw na zasadzie (while(jest za daleko) swap nastepna przerwe z poprzedzajacym ja zadaniem)

    // zliczanie sumy czasów zakończenia zadań
    this->setCj(0);
    for (int i = 0 ; i<this->lineup.size(); i++) {
        if (this->lineup[i].isItTask()) {
            this->setCj(this->getCj()+this->lineup[i].getBeginning_2m()+this->lineup[i].getLen_2m());
        }
    }

    if (this->lineup.size()!=tasksOrder.size()) {
        cout<<"ALARM"<<endl;
    }
}

std::vector<int> Lineup::getOrder() {   //zwraca wektor kolejnosci
    std::vector <int>order;
    for (int i = 0; i<this->lineup.size(); i++) {
        order.push_back(this->lineup[i].getId());
    }
    return order;
}
