//
// Created by Jan Kosinski on 19.01.2017.
//

#include "Loader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "parameters.h"


// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

void Loader::loadData() {
    try {
        std::fstream file;
        //file.open("/Users/jankosinski/ClionProjects/TasksScheduling1/input.txt");
        file.open("C:/Users/Loczi94/Desktop/TasksScheduling1/input.txt");
        std::string line;
        Task *newTask;
        string delimiter = " ";
        int counter = 0;
        string task_1m = "";
        string task_2m = "";
        if (file.good() == true) {
            while (getline(file, line)) {
                line = trim(line);
                if (counter == 0) {
                    //numOfTasks = stoi(line);    //wczytujemy liczbe zadan
                    numOfTasks = atoi(line.c_str());
                }
                else if (counter > 0 && counter <= numOfTasks) {
                    task_1m = line.substr(0, line.find(delimiter));
                    task_2m = line.substr(line.find(delimiter) + 1, line.length() - 1);
                    //newTask = new Task(counter, stoi(task_1m), stoi(task_2m), true);
                    newTask = new Task(counter, atoi(task_1m.c_str()), atoi(task_2m.c_str()), true);
                    tasks.push_back(*newTask);
                }
                else if (counter == numOfTasks+1) {
                    //numOfBreaks = stoi(line);
                    numOfBreaks = atoi(line.c_str());
                }
                else if (counter == numOfTasks+2) {
                    //maxDistBetweenBreaks = stoi(line);
                    maxDistBetweenBreaks = atoi(line.c_str());
                }
                else if (counter == numOfTasks+3) {
                    //breaksLen = stoi(line);
                    breaksLen = atoi(line.c_str());
                }
                else {
                    break;
                }
                counter++;
            }
            for (int i = 0; i<numOfBreaks; i++) {
                newTask = new Task(tasks.size()+1, 0, breaksLen, false);
                tasks.push_back(*newTask);
            }
            delete newTask;
            file.close();
        } else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
    }
    catch (...){
       cout<<"Nieprawidlowy plik"<<endl;
    }
}