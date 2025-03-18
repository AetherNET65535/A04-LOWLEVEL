#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main (int argc, char *argv[])
{
    // CHECK: is user enter argument same with 2?
    if (argc != 2)
    {
        fprintf (2, "USAGE: sleep <ticks>\n");
        exit(1);
    }
    
    // CHANGE: ASCII to INTERGER
    int ticks = atoi(argv[1]);

    // CHECK: if ticks smaller than 0, set it to 0
    if (ticks < 0)
    {
        ticks = 0;
    }

    // CALL: sleep (thank you xv6, this make this code ez 5000%)
    sleep(ticks);

    exit(0);
}



    
   
