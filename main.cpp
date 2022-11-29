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
            " -N Normal time of Qassam flight [seconds]\n"
            " -T Time to reload Iron Dome [minutes]%s\n", RED_BEGIN, errorMessage.c_str(), COLOR_END, CYAN_BEGIN,
            COLOR_END);
    exit(EXIT_FAILURE);
}

// Function for printing out program arguments values
void outputProgramArgs() {
    cout << "******************************* ENTERED ARGS *******************************" << endl;
    cout << setfill('.') << setw(60) << left << "R How many Qassams per day: " << right << ' ' <<  args.R << " Qassams/day"<< endl;
    cout << setw(60) << left << "Z How long it takes to fire all rockets per day: "  << right << ' ' << args.Z << " sec" << endl;
    cout << setw(60) << left << "J Percentage of human error in BMC: "  << right << ' ' << args.J << " %" << endl;
    cout << setw(60) << left << "K Percentage of Qassam failure: "  << right << ' ' << args.K << " %" << endl;
    cout << setw(60) << left << "M Percentage of Qassams that need operator intervention: "  << right << ' ' << args.M << " %" << endl;
    cout << setw(60) << left << "N Uniform time of Qassam flight: "  << right << ' ' << args.N << " sec"<< endl;
    cout << setw(60) << left << "T Time to reload Iron Dome: "  << right << ' ' << args.T << " sec"<< endl;
    cout << "****************************************************************************" << endl;
}


int fellInGaza;
int flewToIsrael;

int criticalTargetHits;
int qassamAimedAtNonCriticalTarget;
int qassamsDodgedIronDome;
int qassamsShotDown;
int failedInterceptionByTamir;
int missFiredTamirsDueToHumanError;
int rocketsTimedOut;

IronDomeLauncher *launcher01;
IronDomeLauncher *launcher02;
IronDomeLauncher *launcher03;

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
                string tmp = argv[i + 1];
                if (atoi(argv[i + 1]) > 100  || tmp[0] == '-') {
                    exit_ims("!!!-K parameter must be between 0 and 100!!!");
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
                } else if (atoi(argv[i + 1]) == 0) {
                    exit_ims("!!!-N parameter must be higher than 0!!!");
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
    outputProgramArgs();

    Init(0, DAY);
    RandomSeed(time(nullptr));

    //Generating R Qassams
    for(unsigned int i = 0; i < args.R; i++){
        (new QassamGenerator)->Activate();
    }
    // Generating battery of launchers (3)
    launcher01 = new IronDomeLauncher;
    launcher02 = new IronDomeLauncher;
    launcher03 = new IronDomeLauncher;

    Run();
    cout << "\nFELL_IN_GAZA   FLEW_TO_ISRAEL" << endl;
    cout << fellInGaza << "             " << flewToIsrael << endl;
    cout << "AIMED_ON_CRITICAL_TARGET" << endl;
    cout << flewToIsrael - qassamAimedAtNonCriticalTarget << endl;
    cout << "NOT_AIMED_ON_CRITICAL_TARGET" << endl;
    cout << qassamAimedAtNonCriticalTarget << endl;
    cout << "\nCRIT_HIT   MISSED_CRITICAL_TARGET_WE_DONT_CARE_ABOUT_THEM" << endl;
    cout << criticalTargetHits << "            " << qassamAimedAtNonCriticalTarget << endl;
    cout << "CRIT_HIT_%" << endl;
    cout << (double)criticalTargetHits / (double)(flewToIsrael - qassamAimedAtNonCriticalTarget) * 100 << " %" << endl;
    cout << "\nQASSAMS_SHOT_DOWN" << endl;
    cout << qassamsShotDown << endl;
    cout << "\nFAILED_INTERCEPTION_BY_TAMIR" << endl;
    cout << failedInterceptionByTamir << endl;
    cout << "\nQASSAMS_DODGED_IRON_DOME" << endl;
    cout << qassamsDodgedIronDome << endl;
    cout << "\nMISSFIRED_TAMIRS_DUE_HUMAN_ERROR" << endl;
    cout << missFiredTamirsDueToHumanError << endl;
    cout << "\nROCKETS_TIMED_OUT" << endl;
    cout << rocketsTimedOut << endl;
    cout << endl;



    return 0;
}



//    Print("***** MODEL1 *****\n");
//    Init(0,1000);              // inicializace experimentu
//    (new Generator)->Activate(); // generátor zákazníků, aktivace
//    Run();                     // simulace
//    Box.Output();              // tisk výsledků
//    Tabulka.Output();
//        return 0;



//    Print(" model2 - SIMLIB/C++ example\n");
//    SetOutput("model2.out");
//    Init(0,1000);              // experiment initialization for time 0..1000
//    (new Generator)->Activate(); // customer generator
//    Run();                     // simulation
//    Box.Output();              // print of results
//    Table.Output();
//    return 0;