//
// Created by Loczi94 on 2017-01-05.
//
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "JohnsonsAlgorithm.h"
#include "parameters.h"
#include "Task.h"

using namespace std;

vector <Task> tasks1;
vector <Task> tasks2;

void JohnsonsAlgorithm::setCj(int value) {
    this->Cj = value;
}

int JohnsonsAlgorithm::getCj() {
    return this->Cj;
}

void quickSort1(int left, int right) {
    int i=left;
    int j=right;
    int pivot=tasks1[rand()%(right-left)+left].getLen_1m();
    do
    {
        while(tasks1[i].getLen_1m()<pivot) i++;
        while(tasks1[j].getLen_1m()>pivot) j--;
        if(i<=j)
        {
            swap(tasks1[i],tasks1[j]);
            i++;
            j--;
        }
    }
    while(i<=j);
    if(left<j) quickSort1(left,j);
    if(right>i) quickSort1(i,right);
}

void quickSort1_1(int left, int right) {
    int i=left;
    int j=right;
    int pivot=tasks1[rand()%(right-left)+left].getLen_2m();
    do
    {
        while(tasks1[i].getLen_2m()<pivot) i++;
        while(tasks1[j].getLen_2m()>pivot) j--;
        if(i<=j)
        {
            swap(tasks1[i],tasks1[j]);
            i++;
            j--;
        }
    }
    while(i<=j);
    if(left<j) quickSort1_1(left,j);
    if(right>i) quickSort1_1(i,right);
}

void quickSort2(int left, int right) {
    int i=left;
    int j=right;
    int pivot=tasks2[rand()%(right-left)+left].getLen_2m();
    do
    {
        while(tasks2[i].getLen_2m()>pivot) i++;
        while(tasks2[j].getLen_2m()<pivot) j--;
        if(i<=j)
        {
            swap(tasks2[i],tasks2[j]);
            i++;
            j--;
        }
    }
    while(i<=j);
    if(left<j) quickSort2(left,j);
    if(right>i) quickSort2(i,right);
}

void quickSort2_2(int left, int right) {
    int i=left;
    int j=right;
    int pivot=tasks2[rand()%(right-left)+left].getLen_1m();
    do
    {
        while(tasks2[i].getLen_1m()>pivot) i++;
        while(tasks2[j].getLen_1m()<pivot) j--;
        if(i<=j)
        {
            swap(tasks2[i],tasks2[j]);
            i++;
            j--;
        }
    }
    while(i<=j);
    if(left<j) quickSort2_2(left,j);
    if(right>i) quickSort2_2(i,right);
}


void printTest() {
    cout << "GROUP1" << endl;
    for (int i =0; i<tasks1.size(); i++) {
        cout<<"Task: "<<tasks1[i].getId()<<" Time_1m: "<<tasks1[i].getLen_1m()<<". Time_2m: "<<tasks1[i].getLen_2m()<<endl;
    }
    cout << "GROUP2" << endl;
    for (int i =0; i<tasks2.size(); i++) {
        cout<<"Task: "<<tasks2[i].getId()<<" Time_1m: "<<tasks2[i].getLen_1m()<<". Time_2m: "<<tasks2[i].getLen_2m()<<endl;
    }

}

void JohnsonsAlgorithm::createLineupJA() {
    for (int i=0; i<tasks.size(); i++) {
        if (tasks[i].isItTask()) {
            if (tasks[i].getLen_1m()<=tasks[i].getLen_2m()) {
                tasks1.push_back(tasks[i]);
            }
            else {
                tasks2.push_back(tasks[i]);
            }
        }
    }
    quickSort1(0,tasks1.size()-1);
    quickSort2(0,tasks2.size()-1);
    int left=0;
    int right;
    for (int i=0; i<tasks1.size(); i++) {
        if (tasks1[i].getLen_1m()!=tasks1[i+1].getLen_1m()) {
            right=i;
            if (left!=right) {
                quickSort1_1(left,right);
            }
            left=i+1;
        }
    }
    left=0;
    for (int i=0; i<tasks2.size(); i++) {
        if (tasks2[i].getLen_2m()!=tasks2[i+1].getLen_2m()) {
            right=i;
            if (left!=right) {
                quickSort2_2(left,right);
            }
            left=i+1;
        }
    }
    printTest();
}

