//
// Created by Jan Kosinski on 08.01.2017.
//

#include "Population.h"

#include "parameters.h"
#include <algorithm>
#include "Task.h"
#include <vector>
#include "Lineup.h"
#include <random>
#include <iostream>


int populationSize = 100; // rozmiar populacji

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