#include <stdio.h>
#include <stdlib.h>

enum priority{
    highest = 4,
    high = 3,
    normal = 2,
    low = 1,
    lowest = 0
}typedef priority;

struct entry{
    priority prio;
    char message[32];
}typedef entry;

struct pqueue{
    entry entries[10];
    int isEmtpty;
}typedef pqueue;

int main()
{
    printf("Hello world!\n");
    return 0;
}
