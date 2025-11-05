#include <stdio.h>
#include <stdlib.h>

//structs and enums

enum priority{
    notSet = 0,
    highest = 5,
    high = 4,
    normal = 3,
    low = 2,
    lowest = 1,
}typedef priority;

char getPrioLetter(priority p){
    switch(p){
        case notSet: return 'N';
        case highest: return 'H';
        case high: return 'h';
        case normal: return 'n';
        case low: return 'l';
        case lowest: return 'L';
    }
}

#define MSG_LENGTH 32

struct entry{
    priority prio;
    char message[MSG_LENGTH];
}typedef entry;

#define MAX_ENTRIES 10

struct pqueue{
    entry entries[MAX_ENTRIES];
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

    if(isFull(pqueue)){
        printf("priority queue already full!\n");
        return;
    }

    priority newEntryPrio = entry.prio;

    pqueue->entries[0] = entry;
    pqueue->count++;
}

void dequeue(struct pqueue* pqueue){

}

//output

void printQueue(struct pqueue* pqueue){

    //run for all exiting entries
    for(int i = 0; i < pqueue->count; i++){
        entry e = pqueue->entries[i];
        printf("%c: %s\n", getPrioLetter(e.prio), e.message);
    }
}

//input

char getMenu(){

}

struct entry getNewEntry(){

};

//main

int main()
{
    pqueue pq = {};
    printQueue(&pq);
    entry newEntry = {.prio = highest,.message = "ADD ME :)!"};
    enqueue(&pq, newEntry);
    printQueue(&pq);
    return 0;
}
