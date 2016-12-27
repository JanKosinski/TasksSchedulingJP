#include <iostream>
#include "parameters.h"
#include <vector>
#include "Lineup.h"
#include "Task.h"

using namespace std;

int main() {
    Task *task1 = new Task(1,2, true);
    Lineup *l = new Lineup();
    l->lineup.push_back(task1);
    cout<<l->lineup[0]->getLen_1m()<<" "<<l->lineup[0]->getLen_2m()<<endl;
    return 0;
}