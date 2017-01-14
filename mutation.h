//
// Created by Jan Kosinski on 12.01.2017.
//

#ifndef TASKSSCHEDULING_MUTATION_H
#define TASKSSCHEDULING_MUTATION_H
#include <vector>
#include <cstdlib>
#include <ctime>

std::vector<int> mutation(std::vector<int> inputOrder) {
    int inputSize = inputOrder.size();
    // mutacja polega na zamianie 2 zadan ze soba w wektorze kolejnosci
    int idx1 = (std::rand()%inputSize); //losujemy pierwszy index
    int idx2 = (std::rand()%inputSize); //i drugi
    while (idx1 == idx2) {  // jezeli wylosowany zostanie dwa razy ten sam index to losujemy dalej
        idx2 = (std::rand()%inputSize);
    }
    //zamieniamy wartosci pod oboma indeksami miejscami
    int a = inputOrder[idx1];
    inputOrder[idx1] = inputOrder[idx2];
    inputOrder[idx2] = a;

    return inputOrder;  //zwracamy wektor
}


#endif //TASKSSCHEDULING_MUTATION_H
