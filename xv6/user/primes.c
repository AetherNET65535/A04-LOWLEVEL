##pragma GCC diagnostic ignored "-Winfinite-recursion"

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define READ 0
#define WRITE 1

void sieve_algo (int left[2])
{
    close(left[WRITE]);

    int prime, temp, pid, right[2];

    // if cant read any number...QAQ
    if (read(left[READ], &prime, sizeof(int)) == 0)
    {
        close(left[READ]);
        exit(0);
    }

    printf("prime: %d\n", prime);
    pipe(right);

    if ((pid = fork()) > 0)
    {
        close(right[READ]);

        while(read(left[READ], &temp, sizeof(int)))
        {
            if (temp % prime != 0)
            {
                write(right[WRITE], &temp, sizeof(int));
            }
        }
        close(right[WRITE]);
        wait(0);
        exit(0);
    }
    else if (pid == 0)
    {
        sieve_algo(right);
        exit(0);
    }
    else
    {
        fprintf(2, "fork error...\n");
        close(right[READ]);
        close(right[WRITE]);
        close(left[READ]);
        exit(1);
    }
    return;
}

int main(int argc, char* argv[])
{
    int pid, p[2];
    pipe(p); // give 'p' a acess to this p (prob kernel will give him, idk)

    if ((pid = fork()) > 0) // parent
    {
        close(p[READ]);

        for (int i = 2; i <= 35; i++)
        {
            write(p[WRITE], &i, sizeof(int));
        }

        close(p[WRITE]);
        wait(0); // wait child kill himself
        exit(0); // kys
    }
    else if (pid == 0) // child
    {
        sieve_algo(p);
        exit(0);
    }
    else // 5000% have error
    {
        fprintf(2, "fork error\n");
        exit(1);
    }
}
