/*************************************************************************************************************
Can be run online at : https://www.onlinegdb.com/online_c++_compiler (C++/C++14 seem to be faster than C++17)
Also : https://repl.it/languages/cpp
*************************************************************************************************************/

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <signal.h>
#include <chrono>
#include <cpuid.h>
#include <thread>


using namespace std;

unsigned long intention_repeats_counter=0; unsigned int M=0;

bool stop = false;

std::chrono::_V2::steady_clock::time_point t1;
std::chrono::_V2::steady_clock::time_point t2;

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
    std::cout << "Number of effective intention repeats = " << std::to_string((((float)intention_repeats_counter) / 1000000 / 1000) * multiplication_factor) << " billions" << endl;
    // Terminate program
    exit(signum);
}


bool show = true;
void task1()
{
    while (stop == false && show == true)
    {
        std::cout << (M / 1000000) * multiplication_factor << "M\r";
    }
}


int main()
{
    signal(SIGINT, signal_callback_handler);
    signal(SIGTERM, signal_callback_handler);
    signal(SIGKILL, signal_callback_handler);
    signal(SIGSTOP, signal_callback_handler);
    signal(SIGTSTP, signal_callback_handler);

    std::cout << endl << "*** PROCESSING ***" << endl;

    std::string intention, process_intention;
    
    t1 = std::chrono::steady_clock::now();
    
    intention = "LOVE";
    
    std::cout << "Multiplication factor = " << multiplication_factor << endl;

    thread thread1(task1);
    
    std::cout << "Start sending. CTRL+C to stop." << endl;
    
    std::string intention_copy = intention;
    for (int i = 0; i < multiplication_factor - 1; i++)
        intention += intention_copy;

    while(true) {
        process_intention = intention;
        intention_repeats_counter++;
        if (intention_repeats_counter%1000000==0) { M++; cout << M << "M\r"; }
    }
    return 0;
}
