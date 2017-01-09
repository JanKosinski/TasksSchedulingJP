//
// Created by Jan Kosinski on 29.12.2016.
// Funkcje w ponizszym pliku nie zostaly jeszcze przetestowane. JKO 29.12.2016
//
#include <vector>
#include <cstdlib>
#include <iostream>
#include "population.h"

bool inVec(std::vector<int> vec, int value) {   //sprawdza czy podana wartosc (value) wystepuje w wektorze (vec)
    for (int i = 0; i<vec.size(); i++) {
        if (value == vec[i]) {
            return true;
        }
    }
    return false;
}

int takeValue(std::vector<int> input, std::vector<int> alreadyTaken) {  //pobiera pierwsza ceche z wektora input, ktora nie wystepuje w wektorze alreadyTaken, czyli juz wykorzystanych
    for (int i = 0; i<input.size(); i++) {
        if (!inVec(alreadyTaken, input[i])) {
            return input[i];
        }
    }
    std::cout<<"ERROR in takeValue"<<std::endl; // nie powinna wystepowac sytuacja w której w wektorze input nie ma wartosci ktora nie zostala jeszcze wykorzystana
    return -1;
}

std::vector<int> operator* (std::vector<int> a, std::vector<int> b) {
    std::vector<int>output;
    int random;
    int aCount = 0; //informuje o tym ile cech wzielismy z wektora a
    int bCount = 0; //informuje o tym ile cech wzielismy z wektora b
    //stosunek aCount do bCount powinien byc w przyblizeniu 1:1
    for (int i = 0; i<a.size(); i++) {
        random = (std::rand()%2) + 0;   // losujemy liczbe 0 albo 1
        if (bCount > (a.size()/2)) {    //jezeli liczba zaczerpnietych cech z wektora b jest wieksza niz polowa wszystkich
            aCount++;   //to pobieramy pierwsze nie uzyte jeszcze zadanie z wektora a
            output.push_back(takeValue(a, output));
        }
        else if (aCount > (a.size()/2)) {   //jezeli liczba zaczerpnietych cech z wektora a jest wieksza niz polowa wszystkich
            bCount++;   //to pobieramy pierwsze nie uzyte jeszcze zadanie z wektora b
            output.push_back(takeValue(b, output));
        }
        else {
            if (random == 0) {  //jezeli wylosowalismy 0 to bierzemy pierwsze nie uzyte jeszcze zadanie z wektora a
                aCount++;
                output.push_back(takeValue(a, output));
            }
            else if (random == 1) { //jezeli wylosowalismy 0 to bierzemy pierwsze nie uzyte jeszcze zadanie z wektora b
                bCount++;
                output.push_back(takeValue(b, output));
            }
            else {  //jezeli komunikat sie pojawi to znaczy ze losowane sa jakies liczby poza 0 i 1. Czyli blad. TESTOWO
                std::cout<<"ERROR during hybridization"<<std::endl;
            }
        }
    }
    return output;
}


std::vector<int> lineupToTasksOrder(Lineup currentLineup) {
    std::vector<int>myNewOrder;
    for (int i = 0; i<currentLineup.lineup.size(); i++) {
        myNewOrder.push_back(currentLineup.lineup[i].getId());
    }
    return myNewOrder;
}

//NIE DZIALA
void Population::hybridization() {
    int hyb_randomLineup;
    std::vector<int> hyb_newLineup;
    Lineup *l;
    for (int i = 0; i<this->lineups.size(); i++) {
        hyb_randomLineup = (std::rand()%lineups.size())+0;
        while (i == hyb_randomLineup) {
            hyb_randomLineup = (std::rand()%lineups.size())+0;
        }
        hyb_newLineup = lineupToTasksOrder(lineups[i])*lineupToTasksOrder(lineups[hyb_randomLineup]);
        l = new Lineup();
        l->createLineup(hyb_newLineup);
        this->lineups.push_back(*l);
    }
}