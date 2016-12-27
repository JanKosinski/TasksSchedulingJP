//
// Created by Jan Kosinski on 27.12.2016.
//

#include "Task.h"

Task::Task(int len_1m, int len_2m) {
    this->len_1m = len_1m;
    this->len_2m = len_2m;
}

int Task::getBeginning_2m() {
    return this->begin_2m;
}

void Task::setBeginning_2m(int newBeginning) {
    this->begin_2m = newBeginning;
}

int Task::getLen_2m() {
    return this->len_2m;
}

int Task::getLen_1m() {
    return this->len_1m;
}

void Task::setBeginning_1m(int newBeginning) {
    this->begin_1m = newBeginning;
}

int Task::getBeginning_1m() {
    return this->begin_1m;
}
