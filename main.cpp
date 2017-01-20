#include <iostream>
#include "parameters.h"
#include <vector>
#include "Lineup.h"
#include "Task.h"
#include <time.h>
#include <cstdlib>
#include "Generator.h"
#include "JohnsonsAlgorithm.h"

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
        cout<<"TaskID: "<<theBestLineup.lineup[i].getId()<<"TaskBeg1m: "<<theBestLineup.lineup[i].getBeginning_1m()<<"TaskBeg2m: "<<theBestLineup.lineup[i].getBeginning_2m()<<endl;
    }
    delete population;
}

int main() {
    srand( time( NULL) );
    Loader::loadData();
    geneticAlgorithm();
    //Generator::generate();
    //Generator::printTasks();
    //JohnsonsAlgorithm *JA;
    //JA = new JohnsonsAlgorithm();
    //JA->createLineupJA();
    //JA->printLineup();
    return 0;
}