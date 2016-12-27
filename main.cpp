#include <iostream>
#include "parameters.h"
#include "TechnicalBreak.h"
#include <vector>
#include "Lineup.h"
#include "Task.h"

using namespace std;

int main() {
    vector<Event*>vec;
    Task *task1 = new Task(1,2);
    Lineup *l = new Lineup();
    TechnicalBreak *break1 = new TechnicalBreak(1);
    vec.push_back(task1);
    vec.push_back(break1);
    cout<<vec[0]->getLen_1m()<<endl;
    return 0;
}