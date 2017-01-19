//
// Created by Loczi94 on 2017-01-03.
//

#include <iostream>
#include "parameters.h"
#include "Task.h"
#include "Generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <string>
#include <sstream>

using namespace std;

int numOfTasks;     //liczba zadań
int numOfBreaks;     //liczba przerw technicznych (okresow niedostepnosci)
int breaksLen;       //czas trwania przerw
int maxTaskLen;      //maksymalny czas trwania jednej operacji zadania
int maxDistBetweenBreaks;
std::vector <Task> tasks;


void Generator::generate() {
    string choose="";
    //system( "cls" );
    cout << ":::GENERATOR:::" << endl;
    cout << "Wybierz opcje:" << endl;
    cout << "1 - generator automatyczny" << endl << "2 - generator manualny" << endl;
    cin >> choose;
    //system( "cls" );
    if (choose=="1") {
        Generator::automaticGenerativity();
    }
    else if (choose=="2") {
        Generator::manualGenerativity();
    }
    int len1=0;
    int len2=0;
    for (int i=1;i<numOfTasks+1;i++){
        len1=(rand()%maxTaskLen)+1;
        len2=(rand()%maxTaskLen)+1;
        Task tmp_task=Task(i, len1, len2, true);
        tasks.push_back(tmp_task);
    }
    for (int i=numOfTasks+1;i<numOfBreaks+numOfTasks+1;i++){
        Task tmp_task=Task(i, 0, breaksLen, false);
        tasks.push_back(tmp_task);
    }
}

void Generator::automaticGenerativity() {
    cout << "\t\t\t:::GENERATOR AUTOMATYCZNY:::" << endl << endl;
    numOfTasks=(rand()%16)+15;      // zakres <15;30>
    numOfBreaks=(((rand()%31)+20)*numOfTasks)/100;     // zakres <20% liczby zadań; 50% liczby zadań>
    maxTaskLen=5;
    breaksLen=(rand()%maxTaskLen)+1;    // zakres <1; maxTaskLen>
    maxDistBetweenBreaks=(rand()%((maxTaskLen)+1))+(2*maxTaskLen);    // zakres <2*maxTaskLen; 3*maxTaskLen>
    cout << "Liczba zadan:\t" << numOfTasks << endl;
    cout << "Liczba okresow niedostepnosci:\t" << numOfBreaks << endl;
    cout << "Czas trwania okresu niedostepnosci:\t" << breaksLen << endl;
    cout << "Maksymalny czas trwania jednej operacji zadania:\t" << maxTaskLen << endl;
    cout << "Maksymalny odstep czasu pomiedzy okresami niedostepnosci:\t" << maxDistBetweenBreaks << endl;
}

void Generator::manualGenerativity() {
    cout << "\t\t\t:::GENERATOR MANUALNY:::" << endl << endl;
    cout << "Liczba zadan:\t";
    cin >> numOfTasks;
    cout << "Liczba okresow niedostepnosci:\t";
    cin >> numOfBreaks;
    cout << "Czas trwania okresu niedostepnosci:\t";
    cin >> breaksLen;
    cout << "Maksymalny czas trwania jednej operacji zadania:\t";
    cin >> maxTaskLen;
    cout << "Maksymalny odstep czasu pomiedzy okresami niedostepnosci:\t";
    cin >> maxDistBetweenBreaks;

}

void Generator::printTasks() {
    for (int i = 0; i<tasks.size(); i++) {
        cout<<"TaskID: "<<tasks[i].getId()<<"\tTaskLen1m: "<<tasks[i].getLen_1m()<<"\tTaskLen2m: "<<tasks[i].getLen_2m()<<endl;
    }
    system( "read -n 1 -s -p \"Press any key to continue...\"" );
}