#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main (int argc, char *argv[])
{
    //CHECK: is user enter argument samw with 1?
    if (argc != 1)
    {
        fprintf(2, "USAGE: pingpong\n");
        exit(1);
    }
    
}

