//
// Created by Jan Kosinski on 08.01.2017.
//

#include "Population.h"
#include <random>
#include <iostream>
#include "parameters.h"

int populationSize = 200;
int minPopulationSize = 70;

void Population::createRandomPopulation() {
    //tworzymy wektor zawierajacy wszystkie id zadan i przerw
    std::vector<int>tasksIds;
    for (int i = 0; i<tasks.size(); i++) {
        tasksIds.push_back(tasks[i].getId());
    }
    //wektor stworzony


    auto engine = std::default_random_engine{}; //stackOverflow rzadko sie myli

    //tworzenie losowych uszeregowan i dodawanie do populacji
    Lineup *lineup = new Lineup();
    std::vector<int>newOrder;
    for (int j = 0; j<populationSize; j++) {
        newOrder = tasksIds;
        std::shuffle(std::begin(newOrder), std::end(newOrder), engine);
        lineup->createLineup(newOrder);
        this->lineups.push_back(*lineup);
    }
    delete lineup;
}

bool operator<( const Lineup& c1, const Lineup& c2 ) { return c1.cj > c2.cj; }

void Population::sortPopulation() {
    std::sort(this->lineups.begin(), this->lineups.end());
    std::reverse(this->lineups.begin(), this->lineups.end());
}

void Population::createProbabilities() {
    this->probabilities.clear();
    vector<int>output;
    int currentProbability;
    double currentValue;
    double minCjValue = this->lineups[0].getCj();  // bo sa posortowane
    double maxCjValue = this->lineups[this->lineups.size()-1].getCj();
    double sum = 0;
    //sumusjemy
    for (int i = 0; i<this->lineups.size(); i++) {
        sum += this->lineups[i].getCj();
    }
    //
    for (int i = 0; i<this->lineups.size(); i++) {
        currentValue = this->lineups[i].getCj();
        currentProbability = (((currentValue-minCjValue)/(maxCjValue-minCjValue)))*100; //normalizacja
        switch(currentProbability) {
            case 100:
                currentProbability = 95;
                break;
            case 0:
                currentProbability = 5;
        }
        this->probabilities.push_back(currentProbability);
    }
}

void Population::selection() {
    vector<Lineup>newPopulation;
    this->sortPopulation();
    this->createProbabilities();
    int random;
    for (int i = 0; i<this->lineups.size(); i++) {
        random = (rand()%100)+0;
        if (this->probabilities[i]<=random) {   //jezeli wylosowana zostala liczba ktora miesci sie w okreslonym prawdopodobienstwie
            newPopulation.push_back(this->lineups[i]);  //dodajemy rozwiazanie
        }
    }
    this->lineups = newPopulation;  //zapisujemy nowa populacje
}

