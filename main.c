#include <stdio.h>
#include <stdlib.h>

//structs and enums

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
    int count;
}typedef pqueue;

//functions

//Interactions with pqueue
int isEmpty(struct pqueue* pqueue){
    if(pqueue->count == 0) return 1;
    else return 0;
}

int isFull(struct pqueue* pqueue){
    if(pqueue->count == 10) return 1;
    else return 0;
}

void enqueue(struct pqueue* pqueue, struct entry entry){
    pqueue->entries[0] = entry;
}

void dequeue(struct pqueue* pqueue){

}

//output

void printQueue(struct pqueue* pqueue){

}

//input

char getMenu(){

}

struct entry getNewEntry(){

};

//main

int main()
{
    printf("Hello world!\n");
    return 0;
}
