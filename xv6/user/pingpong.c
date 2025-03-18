#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main (int argc, char *argv[])
{
    //CHECK: is user enter argument samw with 1?
    if (argc != 1)
    {
        fprinf(2, "USAGE: pingpong\n");
        exit(1);
    }

    char my_pipe[2];

    if (fork() == 0) // CHILD
    {
        char child_signal[1]; 
        read(my_pipe[0], child_signal, 1); // READ: yes, just read
        printf("%d: received ping\n", getpid());
        write(my_pipe[1], "C", 1); // SEND: i am ur son
    }
    else
    {
        char parent_signal[1];
        write(my_pipe[0], "P", 1); // SEND: i am ur dad
        read(my_pipe[1], parent_signal, 1); // READ: just read
        printf("%d: received pong\n", getpid());
    }
    

