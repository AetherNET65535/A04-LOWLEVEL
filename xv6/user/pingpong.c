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

    int my_pipe[2];
    pipe(my_pipe);

    char msg[32];

    if (fork() == 0) // CHILD
    {
        char child_signal[1];

        read(my_pipe[1], child_signal, 1); // READ: yes, just read
        int len = sprintf(msg, "%d: received ping\n", getpid());
        write(1, msg, len);
        write(my_pipe[1], "C", 1); // SEND: i am ur son

        close(my_pipe[1]); // CLOSE: son dont need to write
        close(my_pipe[0]); // CLOSE: son dont need to read rn
    }
    else
    {
        char parent_signal[1];

        write(my_pipe[1], "P", 1); // SEND: i am ur dad
        read(my_pipe[0], parent_signal, 1); // READ: just read, dad will wait son
        int len = sprintf(msg, "%d: received pong\n", getpid());
        write(1, msg, len);

        close(my_pipe[0]); // CLOSE: dad dont need to read rn        
        exit(0);
    }
}

