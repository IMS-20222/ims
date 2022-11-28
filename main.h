/**
 * @project Modeling and simulation - Simulation of anti air missile defense system Iron Dome
 *
 * @file main.h
 * @author Ladislav Vašina, xvasin11@stud.fit.vutbr.cz
 * @author Dominik Vágner, xvagne10@stud.fit.vutbr.cz
 *
 */

#include <iostream>
#include <string>
#include <simlib.h>

#define RED_BEGIN "\033[0;31m"
#define CYAN_BEGIN "\033[1;36m"
#define COLOR_END "\033[0m"
#define BUFFER_SIZE 2048

using namespace std;


// global objects:
Facility  Box("Box");
Histogram Table("Table",0,25,20);

class Customer : public Process {
    double Prichod;                 // attribute of each customer
    void Behavior() {               // --- behavior specification ---
        Prichod = Time;               // incoming time
        Seize(Box);                   // start of service
        Wait(10);                     // time of service
        Release(Box);                 // end of service
        Table(Time-Prichod);          // waiting and service time
    }
};

class Generator : public Event {  // model of system's input
    void Behavior() {               // --- behavior specification ---
        (new Customer)->Activate();   // new customer
        Activate(Time+Exponential(1e3/150));  //
    }
};