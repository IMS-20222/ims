/**
 * @project Modeling and simulation - Simulation of anti air missile defense system Iron Dome
 *
 * @file main.cpp
 * @author Ladislav Vašina, xvasin11@stud.fit.vutbr.cz
 * @author Dominik Vágner, xvagne10@stud.fit.vutbr.cz
 *
 */

#include "main.h"
using namespace std;

int main(int argc, char *argv[]){
    Print(" model2 - SIMLIB/C++ example\n");
    SetOutput("model2.out");
    Init(0,1000);              // experiment initialization for time 0..1000
    (new Generator)->Activate(); // customer generator
    Run();                     // simulation
    Box.Output();              // print of results
    Table.Output();
    return 0;
}