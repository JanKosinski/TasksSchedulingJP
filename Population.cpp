//
// Created by Jan Kosinski on 08.01.2017.
//

#include "Population.h"
#include <random>
#include <iostream>


int populationSize = 100; // rozmiar populacji
int bests = 40;
int randoms = 10;

void Population::createRandomPopulation() {
    //tworzymy wektor zawierajacy wszystkie id zadan i przerw
    std::vector<int>tasksIds;
    for (int i = 0; i<tasks.size(); i++) {
        //std::cout<<tasks[i].getId()<<" ";
        tasksIds.push_back(tasks[i].getId());
    }
    //std::cout<<std::endl<<std::endl;
    //wektor stworzony

    //tworzymy 100 osobnikow (wektorow z losowo ulozona kolejnoscia zadan)

    auto engine = std::default_random_engine{}; //cholera wie co to. Ale stackOverflow rzadko sie myli

    //tworzenie losowych uszeregowan i dodawanie do populacji
    Lineup *lineup = new Lineup();
    std::vector<int>newOrder;
    for (int j = 0; j<populationSize; j++) {
        newOrder = tasksIds;
        std::shuffle(std::begin(newOrder), std::end(newOrder), engine);
        lineup->createLineup(newOrder);
        this->lineups.push_back(*lineup);
    }
}

bool operator<( const Lineup& c1, const Lineup& c2 ) { return c1.cj > c2.cj; }

void Population::sortPopulation() {
    std::sort(this->lineups.begin(), this->lineups.end());
    std::reverse(this->lineups.begin(), this->lineups.end());
}

bool isInVector(int value, std::vector<int>myVector) {  // sprawdza czy int znajduje sie w wektorze int
    for (int i = 0; i<myVector.size(); i++) {
        if (value == myVector[i]) {
            return true;
        }
    }
    return false;
}

void Population::selection() {
    //40 najlepszych + 10 losowych
    vector<int>idxAlreadyUsed;  // indeksy uszeregowan juz uzyte
    vector<Lineup>newPopulation;
    int randIdx;
    for (int i = 0; i<bests; i++) {
        newPopulation.push_back(this->lineups[i]);
        idxAlreadyUsed.push_back(i);
    }
    for (int j = 0; j<randoms; j++) {
        randIdx = (std::rand()%(populationSize-bests-randoms))+(bests+randoms);
        while(isInVector(randIdx, idxAlreadyUsed )) {  //randIdx is in idxAlreadyUsed
            randIdx = (std::rand()%(populationSize-bests-randoms))+(bests+randoms);
        }
        idxAlreadyUsed.push_back(randIdx);
        newPopulation.push_back(this->lineups[randIdx]);
    }
}

