//
// Created by Jan Kosinski on 27.12.2016.
//

#include <iostream>
#include "TechnicalBreak.h"


TechnicalBreak::TechnicalBreak(int len) {
    this->len_2m = len;
}

int TechnicalBreak::getBeginning_2m() {
    return this->begin_2m;
}

void TechnicalBreak::setBeginning_2m(int newBeginning) {
    this->begin_2m = newBeginning;
}

int TechnicalBreak::getLen_2m() {
    return this->len_2m;
}

int TechnicalBreak::getBeginning_1m() {
    std::cout<<"WARNING! Breaks only on 2m.  BE CAREFUL!"<<std::endl;
    return -1;
}

void TechnicalBreak::setBeginning_1m(int newBeginning) {
    std::cout<<"WARNING! Breaks only on 2m. BE CAREFUL!"<<std::endl;
}

int TechnicalBreak::getLen_1m() {
    std::cout<<"WARNING! Breaks only on 2m.  BE CAREFUL!"<<std::endl;
    return 0;
}