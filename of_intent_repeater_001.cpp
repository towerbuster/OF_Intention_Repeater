/******************************************************************************
Can be run online at : https://www.onlinegdb.com/online_c++_compiler
*******************************************************************************/

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <signal.h>

using namespace std;

int i=0; int M=0;

void signal_callback_handler(int signum) {
   cout << "i= " << i << endl;
   // Terminate program
   exit(signum);
}

int main()
{
    signal(SIGINT, signal_callback_handler);

    std::string intention, process_intention;
    
    intention = "LOVE. AMOUR. GRATITUDE. ENERGIE BENEFIQUE.";
    while(true){
        process_intention = intention;
        i++;
        if (i%1000000==0) { M++; cout << M << "M\r"; }
    }
    return 0;
}
