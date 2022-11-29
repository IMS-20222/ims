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

argValues args;

// Function for easier program exiting
void exit_ims(string errorMessage) {
    fprintf(stderr,
            "%s%s \nALL ARGUMENTS ACCEPT INTEGERS ONLY%s%s\nUSAGE: ./main\n"
            " -R How many Qassams per day\n"
            " -Z How long it takes to fire all rockets per day [minutes] (max value is 1440)\n"
            " -J Percentage of human error in BMC\n"
            " -K Percentage of Qassam failure\n"
            " -M Percentage of Qassams that need operator intervention\n"
            " -N Uniform time of Qassam flight [seconds]\n"
            " -T Time to reload Iron Dome [minutes]%s\n", RED_BEGIN, errorMessage.c_str(), COLOR_END, CYAN_BEGIN,
            COLOR_END);
    exit(EXIT_FAILURE);
}

string optionToFind;

int main(int argc, char *argv[]) {
    // Argument parser
    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            optionToFind = string(argv[i]);
            // Help handler
            if (optionToFind == "-h" || optionToFind == "--help") {
                exit_ims("");
            }
            // Check -R option
            else if (optionToFind == "-R") {
                if (argv[i + 1] == nullptr) {
                    exit_ims("!!!You are missing argument for -R parameter!!!");
                }
                string tmp = argv[i + 1];
                if (tmp[0] == '-') {
                    exit_ims("!!!-R parameter can't be negative!!!");
                }
                args.R = atoi(argv[i + 1]);
            }
            // Check -Z option
            else if (optionToFind == "-Z") {
                if (argv[i + 1] == nullptr) {
                    exit_ims("!!!You are missing argument for -Z parameter!!!");
                }
                else if(atoi(argv[i + 1]) > 1440){
                    exit_ims("!!!-Z parameter can't be higher than 1440!!!");
                }
                string tmp = argv[i + 1];
                if (tmp[0] == '-') {
                    exit_ims("!!!-Z parameter can't be negative!!!");
                }
                args.Z = atoi(argv[i + 1]) * 60;
            }
            // Check -J option
            else if (optionToFind == "-J") {
                if (argv[i + 1] == nullptr) {
                    exit_ims("!!!You are missing argument for -J parameter!!!");
                }
                string tmp = argv[i + 1];
                if (atoi(argv[i + 1]) > 100  || tmp[0] == '-') {
                    exit_ims("!!!-J parameter must be between 0 and 100!!!");
                }
                args.J = stoul(argv[i + 1], nullptr, 10);
            }
            // Check -K option
            else if (optionToFind == "-K") {
                if (argv[i + 1] == nullptr) {
                    exit_ims("!!!You are missing argument for -K parameter!!!");
                }
                args.K = atoi(argv[i + 1]);
            }
            // Check -M option
            else if (optionToFind == "-M") {
                if (argv[i + 1] == nullptr) {
                    exit_ims("!!!You are missing argument for -M parameter!!!");
                }
                string tmp = argv[i + 1];
                if (atoi(argv[i + 1]) > 100  || tmp[0] == '-') {
                    exit_ims("!!!-M parameter must be between 0 and 100!!!");
                }
                args.M = atoi(argv[i + 1]);
            }
            // Check -N option
            else if (optionToFind == "-N") {
                if (argv[i + 1] == nullptr) {
                    exit_ims("!!!You are missing argument for -N parameter!!!");
                }
                string tmp = argv[i + 1];
                if (tmp[0] == '-') {
                    exit_ims("!!!-N parameter can't be negative!!!");
                }
                args.N = atoi(argv[i + 1]);
            }
            // Check -T option
            else if (optionToFind == "-T") {
                if (argv[i + 1] == nullptr) {
                    exit_ims("!!!You are missing argument for -N parameter!!!");
                }
                string tmp = argv[i + 1];
                if (tmp[0] == '-') {
                    exit_ims("!!!-T parameter can't be negative!!!");
                }
                args.T = atoi(argv[i + 1]) * 60;
            }
        }
    }
    cout << "*** ENTERED ARGS ***" << endl;
    cout << "R: " << args.R << " Qassams/day"<< endl;
    cout << "Z: " << args.Z << " sec" << endl;
    cout << "J: " << args.J << " %" << endl;
    cout << "K: " << args.K << " %" << endl;
    cout << "M: " << args.M << " %" << endl;
    cout << "N: " << args.N << " sec"<< endl;
    cout << "T: " << args.T << " sec"<< endl;
    cout << "*********************" << endl;


//    Print("***** MODEL1 *****\n");
//    Init(0,1000);              // inicializace experimentu
//    (new Generator)->Activate(); // generátor zákazníků, aktivace
//    Run();                     // simulace
//    Box.Output();              // tisk výsledků
//    Tabulka.Output();
        return 0;



//    Print(" model2 - SIMLIB/C++ example\n");
//    SetOutput("model2.out");
//    Init(0,1000);              // experiment initialization for time 0..1000
//    (new Generator)->Activate(); // customer generator
//    Run();                     // simulation
//    Box.Output();              // print of results
//    Table.Output();
//    return 0;
    }