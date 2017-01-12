//
// Created by Jan Kosinski on 29.12.2016.
// Funkcje w ponizszym pliku nie zostaly jeszcze przetestowane. JKO 29.12.2016
//
#include <vector>
#include <cstdlib>
#include <iostream>
#include "population.h"
#include "mutation.h"

using namespace std;

std::vector<int> lineupToTasksOrder(Lineup currentLineup) {
    std::vector<int>myNewOrder;
    for (int i = 0; i<currentLineup.lineup.size(); i++) {
        myNewOrder.push_back(currentLineup.lineup[i].getId());
    }
    return myNewOrder;
}

bool inVector(int value, std::vector<int>myVector) {  // sprawdza czy int znajduje sie w wektorze int
    for (int i = 0; i<myVector.size(); i++) {
        if (value == myVector[i]) {
            return true;
        }
    }
    return false;
}

int findPos(vector<int>vec, bool fromBeginning = true) {
    if (fromBeginning) {
        for (int i = 0; i<vec.size(); i++) {
            if (vec[i] == -1) {
                return i;
            }
        }
    }
    else {
        for (int j = vec.size()-1; j>=0; j--) {
            if (vec[j] == -1) {
                return j;
            }
        }
    }
    return -2;  // nie ma wiecej wartosci do wstawienia
}

vector<int> operator* (vector<int> mother, vector<int> father) {
    vector<int>output(mother.size(), -1);  //wektor wynikowy. Inicjujemy -1
    vector<int>temp;    //wektor tymczasowy. Sluzy jedynie do zamiany matki i ojca
    int valueToInsert;
    int idxToInsert;
    int random = (rand()%2)+0;  //losujemy czy zamieniamy matke z ojcem. Wazne by losowo bylo od kogo bierzemy poczatek a od kogo koniec
    if (random == 0) {  // zamieniamy matke z ojcem
        temp = mother;
        mother = father;    //zamiana
        father = temp;
    }

    for (int i = 0; i<mother.size(); i++) {

        //wstawiamy cechy od matki. Od poczatku
        if (findPos(output)==-2) {break;}   //oznacza ze wszystkie wartosci juz zostaly wstawione
        valueToInsert = mother[i];  //chcemy wstawic taka wartosc
        if(!(inVector(valueToInsert, output))) {  //jezeli nie ma jej jeszcze w wektorze wyjsciowym to wstaawiamy na pierwsza pozycje, na ktorej jest -1
            idxToInsert = findPos(output);  //znajduje pierwszy index w wektorze w ktory mozna wstawic wartosc
            output[idxToInsert] = valueToInsert;    //wstawia wartosc
        }

        //wstawiamy cechy od ojca. Od konca
        if (findPos(output)==-2) {break;}   //oznacza ze wszystkie wartosci juz zostaly wstawione.
        valueToInsert = father[father.size()-(i+1)];
        if(!(inVector(valueToInsert, output))) {
            idxToInsert = findPos(output, false);
            output[idxToInsert] = valueToInsert;    //wstawia wartosc
        }
    }

    return output;
}

void Population::hybridization() {
    this->sortPopulation();
    int random;
    int i = 0;
    std::vector<int> newLineup;
    int randomLineup;
    Lineup l;
    vector<Lineup>tempVectorOfLineups = this->lineups;      //przepisujemy osobniki, ktore przezyly selekcje
    while(tempVectorOfLineups.size()<populationSize) {      //dopoki nie osiagniemy pojemnosci srodowiska czyli populationSize
        randomLineup = (rand()%this->lineups.size())+0;     //szukamy losowego partnera dla danego osobnika
        while (randomLineup == i) {
            randomLineup = (rand()%this->lineups.size())+0; //nie moze przeciez krzyzowac sie ze soba
        }
        newLineup = lineupToTasksOrder(this->lineups[i])*lineupToTasksOrder(this->lineups[randomLineup]);   //krzyzujemy

        //MUTACJA!
        random = (rand()%100)+0;
        if (random<=3) {
            newLineup = mutation(newLineup);
        }
        //KONIEC MUTACJI

        l.createLineup(newLineup);
        tempVectorOfLineups.push_back(l);  //dodajemy do populacji
        i++;    //i nastepny osobnik
        if (i>this->lineups.size()-1) {   //pilnuje zeby i nie wyszlo poza zakres
            i = 0;
        }
    }
    this->lineups = tempVectorOfLineups;
}