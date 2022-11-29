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
#include <string.h>
#include <iomanip>

#define RED_BEGIN "\033[0;31m"
#define CYAN_BEGIN "\033[1;36m"
#define COLOR_END "\033[0m"

#define DAY 86400 // seconds in day
#define QASSAM_CRITICAL 1.0/3.0
#define QASSAM_PRICE 800
#define TAMIR_PRICE 125000

using namespace std;


string optionToFind;

/**
 * Struct for storing program arguments
 * Arguments have default value in case user doesn't enter them
 */
struct argValues{
    // How many Qassams per day
    unsigned int R = 300;
    // How long it takes to fire all rockets per day [seconds]
    unsigned int Z = 21600;
    // Human error in BMC in %
    unsigned int J = 1;
    // Qassam failure rate in %
    unsigned int K = 20;
    // Qassams that need operator intervention in %
    unsigned int M = 5;
    // Uniform time of Qassam flight [seconds]
    unsigned int N = 30;
    // Time to reload Iron Dome [seconds]
    unsigned int T = 1200;
};

extern int criticalTargetHits;
extern int nonCriticalTargetHits;


extern int fellInGaza;
extern int flewToIsrael;
extern argValues args;

// Initialize radar store
Store radarStore("Radar", 1000); // p28

class IronDomeLauncher : public Process {
    public: int rocketMagazine = 20;

    void Behavior() {
        while(1){
        //start: TODO DELETE
        //rocketMagazine--;
        if (rocketMagazine == 0) {
            cout << Time << " RELOADING" << endl;
            cout << args.T << endl;
            Wait(args.T);
            cout << Time << " RELOAD FINISHED" << endl;
            rocketMagazine = 20;
        }
        Passivate();}
        //goto start; TODO DELETE
    }
    void GetRocketMagazine(int launcherID) {
        cout << launcherID << "# " <<Time <<" Left in mag " << rocketMagazine << endl;

    }

};



extern IronDomeLauncher *launcher01;
extern IronDomeLauncher *launcher02;
extern IronDomeLauncher *launcher03;


class Qassam : public Process { // TODO
    void Behavior() {
        // Qassam waiting to be fired - p1
        Wait(Uniform(0, args.Z)); // t2
        if (Random() < (args.K * 0.01)) {
            // Qassam is destroyed
            fellInGaza++;
            Cancel(); // t3
        } else { // t4
            // Qassam is not destroyed
            flewToIsrael++; // p29
            if (radarStore.Full()) { // t39
                if (Random() < (1 - QASSAM_CRITICAL)) { // t40
                    nonCriticalTargetHits++; // p34
                    Cancel();
                } else { // t41
                    criticalTargetHits++; // p35
                    Cancel();
                }
            } else { // p6
                Enter(radarStore, 1);
                if (Random() < (args.M * 0.01)) { // t7 Qassam needs operator intervention

                } else { // t6 Iron Dome will handle Qassam on its own
                    if (Random() < 1 - QASSAM_CRITICAL) { // t20
                        nonCriticalTargetHits++; // p6
                        Leave(radarStore, 1);
                        Cancel();
                    } else { // t21
                        if(launcher01->rocketMagazine) { // t23
                            launcher01->rocketMagazine--;
                            launcher01->GetRocketMagazine(1);
                            launcher01->Activate();
                        } else if(launcher02->rocketMagazine) { // t27
                            launcher02->rocketMagazine--;
                            launcher02->GetRocketMagazine(2);
                            launcher02->Activate();
                        } else if(launcher03->rocketMagazine) { // t31
                            launcher03->rocketMagazine--;
                            launcher03->GetRocketMagazine(3);
                            launcher03->Activate();
                        } else { // t42
                            criticalTargetHits++; // p36
                            Leave(radarStore, 1);
                            Cancel();
                        }
                    }
                }

                Leave(radarStore, 1);
                Cancel();
            }
        }
    }
};


class QassamGenerator : public Event {  // model of system's input
    void Behavior() {                  // --- behavior specification ---
        Qassam *qassam = new Qassam;
        qassam->Activate();
        //qassam->Output();
    }
};











//// global objects:
//Facility  Box("Box");
//Histogram Table("Table",0,25,20);
//
//class Customer : public Process {
//    double Prichod;                 // attribute of each customer
//    void Behavior() {               // --- behavior specification ---
//        Prichod = Time;               // incoming time
//        Seize(Box);                   // start of service
//        Wait(10);                     // time of service
//        Release(Box);                 // end of service
//        Table(Time-Prichod);          // waiting and service time
//    }
//};
//
//class Generator : public Event {  // model of system's input
//    void Behavior() {               // --- behavior specification ---
//        (new Customer)->Activate();   // new customer
//        Activate(Time+Exponential(1e3/150));  //
//    }
//};



////  deklarace  globálních  objektů
//Facility  Box("Linka");
//Histogram Tabulka("Tabulka",0,50,10);
//
//class Zakaznik : public Process { // třída zákazníků
//    double Prichod;                 // atribut každého zákazníka
//    void Behavior() {               // popis chování zákazníka
//        Prichod = Time;               // čas příchodu zákazníka
//        Seize(Box);                   // obsazení zařízení Box
//        Wait(10);                     // obsluha
//        Release(Box);                 // uvolnění
//        Tabulka(Time-Prichod);        // doba obsluhy a čekání
//    }
//};
//
//class Generator : public Event {  // generátor zákazníků
//    void Behavior() {               // popis chování generátoru
//        (new Zakaznik)->Activate();     // nový zákazník v čase Time
//        Activate(Time+Exponential(1e3/150)); // interval mezi příchody
//    }
//};