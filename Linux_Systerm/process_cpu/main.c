#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <sched.h>
 
void WasteTime()
{
    int abc = 10000000;
    while(abc--)
    {
        int tmp = 10000*10000;
    }
    sleep(1);

}

int main(int argc, char **argv)
{
    cpu_set_t mask;
    while(1)
    {
 
        CPU_ZERO(&mask);
        CPU_SET(0, &mask); 
        if (sched_setaffinity(0, sizeof(mask), &mask) < 0) {
            perror("sched_setaffinity");
        }
        WasteTime();

/*
        CPU_ZERO(&mask);
        CPU_SET(1, &mask); 
        if (sched_setaffinity(0, sizeof(mask), &mask) < 0) {
            perror("sched_setaffinity");
        }
        WasteTime();
*/     
    }
}
