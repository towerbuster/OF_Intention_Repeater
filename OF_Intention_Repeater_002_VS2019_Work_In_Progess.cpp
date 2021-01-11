/*************************************************************************************************************
Can NOT be run online at : https://www.onlinegdb.com/online_c++_compiler (C++/C++14 seem to be faster than C++17)
Also CAN NOT BE RUN AT : https://repl.it/languages/cpp
THIS SOURCE CODE IS TO BE COMPILED WITH VISUAL STUDIO 2019 (C++ PROJECT)
*************************************************************************************************************/

#include <iostream>
//#include <unistd.h>
#include <cstdlib>
#include <signal.h>
#include <chrono>
#include <string>
#include <thread>
//#include <cpuid.h>

using namespace std;

unsigned long long intention_repeats_counter = 0; unsigned long long M = 0;

bool stop = false;

std::chrono::steady_clock::time_point t1;
std::chrono::steady_clock::time_point t2;


int multiplication_factor = 128;


// When CTRL+C (SIGINT), this is executed, also when program is stopped (SIGTERM, eg. useful on repl.it but not on onlinegdb)
void signal_callback_handler(int signum) {
    stop = true;
    t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    std::cout << "Total execution time is " << diff.count() << " seconds" << " = " << diff.count() / 60 << " minutes" << " = " << diff.count() / 60 / 60 << " hours" << endl;
    unsigned long long average_intention_repeats_per_sec = (unsigned long long)((intention_repeats_counter * multiplication_factor) / diff.count());
    std::cout << "Number of average intention repeats per microsecond was " << std::to_string(((float)average_intention_repeats_per_sec) / 1000 / 1000) << endl;
    std::cout << "Number of average intention repeats per millisecond was " << std::to_string(average_intention_repeats_per_sec / 1000) << endl;
    std::cout << "Number of average intention repeats per second was " << std::to_string(average_intention_repeats_per_sec) << endl;
    std::cout << "Number of average intention repeats per minute was " << std::to_string(average_intention_repeats_per_sec * 60) << endl;
    std::cout << "Number of average intention repeats per minute was " << std::to_string(((float)(average_intention_repeats_per_sec * 60)) / 1000000) << " millions" << endl;
    std::cout << "Number of effective intention repeats = " << std::to_string(intention_repeats_counter * multiplication_factor) << endl;
    std::cout << "Number of effective intention repeats = " << std::to_string((((float)intention_repeats_counter) / 1000000) * multiplication_factor) << " millions" << endl;
    // Terminate program
    exit(signum);
}

bool show = false;
void task1()
{
    while (stop == false && show == true)
    {
        std::cout << M / 1000000 << "M\r";
    }
}


unsigned long long maxcounter = 0;

int main(int argc, char* argv[])
{
    signal(SIGINT, signal_callback_handler);
    signal(SIGTERM, signal_callback_handler);
    std::string intention, process_intention;
    intention = "DIVINE LOVE";

    //std::cout << endl << "*** START ARGUMENTS PARSING ***" << endl;
    for (int i = 1; i < argc; ++i) {
        std::cout << argv[i] << endl;
        std::string arg = argv[i];
        if (arg == "--intention") {
            //std::cout << "intention detected" << endl;
            if (i + 1 < argc) {
                i++;
                std::string intention_input_str = argv[i];
                //std::cout << "intention received = " << intention_input_str << endl;
                intention = intention_input_str;
            }
            else {
                // missing argument for --intention
            }
        }
        if (arg == "--showcounter") {
            //std::cout << "show counter detected" << endl;
            show = true;
        }
        if (arg == "--maxcounter") {
            //std::cout << "maxcounter detected" << endl;
            if (i + 1 < argc) {
                i++;
                std::string maxcounter_input_str = argv[i];
                //std::cout << "maxcounter received = " << maxcounter_input_str << endl;
                maxcounter = stoll(maxcounter_input_str);
            }
            else {
                // missing argument for --maxcounter
            }
        }
        if (arg == "--multiplicationfactor") {
            //std::cout << "multiplicationfactor detected" << endl;
            if (i + 1 < argc) {
                i++;
                std::string mf_input_str = argv[i];
                //std::cout << "multiplication factor received = " << mf_input_str << endl;
                multiplication_factor = stoi(mf_input_str);
            }
            else {
                // missing argument for --multiplicationfactor
            }
        }
        if (arg == "--h" || arg == "-h" || arg == "--help" || arg == "-help") {
            std::cout << "Options :" << endl << "-h or --h or --help or -help : Show this help." << endl;
            std::cout << "--intention \"THE INTENTION TO SEND\" : Set intention to send. " << endl;
            std::cout << "--showcounter : Show live counter (divided by 1 million), eg. 1M = 1 million." << endl;
            std::cout << "--maxcounter X : Set the maximum number of millions of times the intention is sent, eg 1 for 1 million. Not specifying this parameter (or 0) is equivalent to infinite." << endl;
        }
    }


    std::cout << endl << "*** PROCESSING ***" << endl;

    std::cout << "Multiplication factor = " << multiplication_factor << endl;

    thread thread1(task1);

    std::cout << "Intention : " << intention << endl;

    if (maxcounter == 0)
        std::cout << "Number of repeats : infinite" << endl;
    else
        std::cout << "Number of repeats : " << maxcounter << " millions" << endl;

    std::cout << "Start sending. CTRL+C to stop." << endl;
    t1 = std::chrono::steady_clock::now();

    std::string intention_copy = intention;
    for (int i = 0; i < multiplication_factor - 1; i++)
        intention += intention_copy;

    while (true) {
        process_intention = intention;
        intention_repeats_counter++;

        M++;

        if (maxcounter > 0) {
            if (M == maxcounter * 1000000) {
                stop = true;
                signal_callback_handler(SIGINT);
            }
        }
    }
    return 0;
}
