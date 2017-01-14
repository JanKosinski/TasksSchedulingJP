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

int numberOfLoops = 1000;

void geneticAlgorithm() {
    Population *population = new Population();
    Population *copyOfPopulation;
    population->createRandomPopulation();
    copyOfPopulation = population;
    Lineup theBestLineup = population->lineups[0];
    cout << "The best lineup: " << theBestLineup.getCj() << endl;
    int loopNum = 0;
    while(loopNum<numberOfLoops) {
        copyOfPopulation = population;
        population->selection();
        if(population->lineups.size()<20) {  //populacja nam wyginela :D
            population = copyOfPopulation;
        }
        population->hybridization();
        population->sortPopulation();
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
    Generator::generate();
    Generator::printTasks();
    //JohnsonsAlgorithm::createLineupJA();
    geneticAlgorithm();

    return 0;
}