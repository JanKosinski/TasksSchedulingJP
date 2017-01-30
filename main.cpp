#include <iostream>
#include "parameters.h"
#include <vector>
#include "Lineup.h"
#include "Task.h"
#include <time.h>
#include <cstdlib>
#include "Generator.h"
#include "JohnsonsAlgorithm.h"
#include "ExactAlgorithm.h"

using namespace std;

#include "Population.h"
#include "parameters.h"
#include "Loader.h"

int numberOfLoops = 10000;


void geneticAlgorithm() {
    Population *population = new Population();
    Population *copyOfPopulation;
    population->createRandomPopulation();
    copyOfPopulation = population;
    Lineup theBestLineup = population->lineups[0];
    cout << "The best lineup: " << theBestLineup.getCj() << endl;
    int prvBestLineupValue = 0;
    int curentBestLineupValue = 0;
    int loopNum = 0;
    while(loopNum<numberOfLoops) {
        copyOfPopulation = population;
        population->selection();
        if(population->lineups.size()<20) {  //populacja nam wyginela :D
            population = copyOfPopulation;
        }
        population->hybridization();
        population->sortPopulation();
        if (loopNum%50 == 0) {
            curentBestLineupValue = max(theBestLineup.getCj(), population->lineups[0].getCj());
            if (prvBestLineupValue!=0 && prvBestLineupValue == curentBestLineupValue) {
                break;
            }
            prvBestLineupValue = curentBestLineupValue;
        }
        if (theBestLineup.getCj()>population->lineups[0].getCj()) {
            theBestLineup = population->lineups[0];
            cout << "The best lineup: " << theBestLineup.getCj() << endl;
        }
        loopNum++;
    }
    cout<<endl;
    for (int i = 0; i<theBestLineup.lineup.size(); i++) {
        cout<<"TaskID: "<<theBestLineup.lineup[i].getId()<<" TaskBeg1m: "<<theBestLineup.lineup[i].getBeginning_1m()<<" Len_1M: "<< theBestLineup.lineup[i].getLen_1m()<<" TaskBeg2m: "<<theBestLineup.lineup[i].getBeginning_2m()<<" Len_2M: "<<theBestLineup.lineup[i].getLen_2m()<<endl;
    }
    delete population;
}

void RunJohnsonsAlgorithm() {
    JohnsonsAlgorithm *JA;
    JA = new JohnsonsAlgorithm();
    JA->createLineupJA();
    JA->printLineup();
    cout << endl << "Cj = " << JA->getCj() << endl;
}

void RunExactAlgorithm() {
    vector <int> listOfNumbersOfTasks;
    for (int i=1; i<=tasks.size(); i++){
        listOfNumbersOfTasks.push_back(i);
    }
    ExactAlgorithm *EA;
    EA = new ExactAlgorithm();
    EA->generatePermutations(listOfNumbersOfTasks,0);
    EA->printLineup();
    cout << endl << "Cj = " << EA->getTheBestCj() << endl;
}

int main() {
    srand( time( NULL) );
    //Loader::loadData();
    Generator::generate();
    Generator::printTasks();
    //cout << endl << endl << "JOHNSONS ALGORITHM" << endl << endl;
    //RunJohnsonsAlgorithm();
    cout << endl << endl << "EXACT ALGORITHM" << endl << endl;
    RunExactAlgorithm();
    cout << endl << endl << "GENETIC ALGORITHM" << endl << endl;
    geneticAlgorithm();

    return 0;
}