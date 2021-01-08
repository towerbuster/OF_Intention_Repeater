/*************************************************************************************************************
COMPILED EXE NOT AVAILABLE FOR NOW
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

// When CTRL+C (SIGINT), this is executed, also when program is stopped (SIGTERM, eg. useful on repl.it but not on onlinegdb)
void signal_callback_handler(int signum) {
    stop = true;
    t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    std::cout << "Total execution time is " << diff.count() << " seconds" << " = " << diff.count()/60 << " minutes" << " = " << diff.count()/60/60 << " hours" << endl;
    unsigned long long average_intention_repeats_per_sec = (unsigned long long)(intention_repeats_counter / diff.count());
    std::cout << "Number of average intention repeats per microsecond was " << std::to_string(((float)average_intention_repeats_per_sec) / 1000 / 1000) << endl;
    std::cout << "Number of average intention repeats per millisecond was " << std::to_string(average_intention_repeats_per_sec/1000) << endl;
    std::cout << "Number of average intention repeats per second was " << std::to_string(average_intention_repeats_per_sec) << endl;
    std::cout << "Number of average intention repeats per minute was " << std::to_string(average_intention_repeats_per_sec * 60) << endl;
    std::cout << "Number of average intention repeats per minute was " << std::to_string(((float)(average_intention_repeats_per_sec * 60))/1000000) << " millions" << endl;
    std::cout << "Number of effective intention repeats = " << intention_repeats_counter << endl;
    std::cout << "Number of effective intention repeats = " << ((float)intention_repeats_counter)/1000000 << " millions" << endl;
    // Terminate program
    exit(signum);
}

bool show = false;
void task1()
{
    while (stop == false && show == true) 
    {
        std::cout << M/1000000 << "M\r";
    }
}

int main(int argc, char* argv[])
{
    signal(SIGINT, signal_callback_handler);
    signal(SIGTERM, signal_callback_handler);
    std::string intention, process_intention;
    intention = "DIVINE LOVE + POSITIVE ORGONE + BLUE SKY";

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--showcounter") {
            show = true;
        }
        if (std::string(argv[i]) == "--intention") {
            if (i + 1 < argc) { 
                i++;
                std::string input_intention = argv[i++]; 
                //std::cout << "intention received = " << input_intention << endl;
                intention = input_intention;
                //return 1;
            }
            else {
                std::cerr << "--intention option requires one argument." << std::endl;
                return 1;
            }
        }
    }

    std::cout << "Intention : " << intention << endl;
    std::cout << "Start sending. CTRL+C to stop." << endl;
    t1 = std::chrono::steady_clock::now();

    thread t1(task1);

    while (true) {
        process_intention = intention;
        intention_repeats_counter++;
        //if (intention_repeats_counter % 1000000 == 0) { M++; cout << M << "M\r"; } // This line slows the processing
        //std::cout << M++ << "\r";
        M++;

        /*if (M == 1000000000000) {
            stop = true;
            signal_callback_handler(SIGINT);
        }*/
    }
    return 0;
}


