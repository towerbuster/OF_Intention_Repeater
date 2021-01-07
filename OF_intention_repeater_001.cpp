/*************************************************************************************************************
Can be run online at : https://www.onlinegdb.com/online_c++_compiler (C++/C++14 seem to be faster than C++17)
Also : https://repl.it/languages/cpp
*************************************************************************************************************/

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <signal.h>
#include <chrono>

using namespace std;

unsigned long i=0; unsigned int M=0;

std::chrono::_V2::system_clock::time_point t1;
std::chrono::_V2::system_clock::time_point t2;

// When CTRL+C, this is executed
void signal_callback_handler(int signum) {
    t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = t2-t1;
    std::cout << "Total execution time " << diff.count() << " s\n";
    std::cout << "Number of intent repeats per second was " << std::to_string((int)(i/diff.count())) << "\n";
    cout << "i= " << i << endl;
    // Terminate program
    exit(signum);
}


int main()
{
    signal(SIGINT, signal_callback_handler);

    std::string intention, process_intention;
    
    t1 = std::chrono::high_resolution_clock::now();
    intention = "LOVE";
    while(true){
        process_intention = intention;
        i++;
        if (i%1000000==0) { M++; cout << M << "M\r"; }
    }
    return 0;
}
