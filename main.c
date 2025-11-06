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
        case highest: return 'H';
        case high: return 'h';
        case normal: return 'n';
        case low: return 'l';
        case lowest: return 'L';
        default: return 'N';
    }
}

priority getPrioEnum(char c){
    switch(c){
        case 'H': return highest;
        case 'h': return high;
        case 'n': return normal;
        case 'l': return low;
        case 'L': return lowest;
        default: return notSet;
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

//unitlities

//dstLen will always be MAX_ENTRIES for this programm
void strCopy(char * src, char * dst, int dstLen){
    for(int i = 0; i < dstLen - 1; i++){

        //if the string is done, end the function, end string with \0
        if(src[i] == '\0'){
            dst[i] = '\0';
            return;
        }

        //otherwise just copy char by char
        dst[i] = src[i];
    }
    //always end with \0
    dst[dstLen - 1] = '\0';
}

//Interactions with pqueue
int isEmpty(struct pqueue* pqueue){
    if(pqueue->count == 0) return 1;
    else return 0;
}

int isFull(struct pqueue* pqueue){
    if(pqueue->count == 10) return 1;
    else return 0;
}

int findSpot(struct pqueue* pqueue, struct entry entry){
    for(int i = 0; i < MAX_ENTRIES; i++){
        if(pqueue->entries[i].prio < entry.prio){
            return i;
        }
    }
    return -1; //should alsways find a spot, but lets make the compiler happy
}

void printEntryAmmount(pqueue * pqueue){
    char * word = (pqueue->count == 1) ? "entry" : "entries";
    printf("\npriority queue now contains %d %s", pqueue->count, word);
}

void enqueue(struct pqueue* pqueue, struct entry entry){

    if(isFull(pqueue)){
        printf("\npriority queue already full!");
        return;
    }

    int insertIndex = findSpot(pqueue, entry);

    //if the insertPoint is an existing index
    if(insertIndex <= pqueue->count - 1){
        //shift stuff starting from insertpoint
        //starts at the last filled index, goes down to the index that needs to be freed
        for(int i = pqueue->count - 1; i >= insertIndex ; i--){
            pqueue->entries[i + 1] = pqueue->entries[i];
        }
    }

    //update entry, count and print new count
    pqueue->entries[insertIndex] = entry;
    pqueue->count++;
    printEntryAmmount(pqueue);
}

void dequeue(struct pqueue* pqueue){

    if(pqueue->count == 0){
        printf("\npriority queue is empty!");
        return;
    }

    printf("\n Message: %s", pqueue->entries[0].message);

    for(int i = 0; i < pqueue->count - 1; i++){
        pqueue->entries[i] = pqueue->entries[i + 1];
    }

    pqueue->count--;
    printEntryAmmount(pqueue);
}

//output

void printQueue(struct pqueue* pqueue){

    if(isEmpty(pqueue)){
        printf("\n empty queue");
        return;
    }

    //run for all exiting entries
    for(int i = 0; i < pqueue->count; i++){
        entry e = pqueue->entries[i];
        printf("\n%c: %s", getPrioLetter(e.prio), e.message);
    }
}

//input

int menuInputValid(char c){
    char valid[4] = {'p', 'e', 'd', 'x'};
    for(int i = 0; i < 4; i++){
        if(c == valid[i]) return 1;
    }
    return 0;
}

char getMenu(){

    char input = '\n';
    printf("\nChoose action: print queue (p), enqueue entry (e), dequeue entry (d) or exit (x): ");
    scanf(" %c", &input);

    while(!menuInputValid(input)){
        printf("\nInput invalid! Try again: ");
        scanf(" %c", &input);
    }

    return input;
}

int entryPrioValid(char c){
    char valid[5] = {'L', 'l', 'n', 'h', 'H'};
    for(int i = 0; i < 5; i++){
        if(c == valid[i]) return 1;
    }
    return 0;
}

struct entry getNewEntry(){

    //create new entry to return
    entry newEntry;

    //get prio data
    char prio = '\n';
    printf("\nChoose priority: lowest (L), low (l), normal (n), high (h), highest (H): ");
    scanf(" %c", &prio);

    while(!entryPrioValid(prio)){
        printf("\nInput invalid! Try again: ");
        scanf(" %c", &prio);
    }

    newEntry.prio = getPrioEnum(prio);

    //get the message (always correct, no need for validation)
    char msg[MSG_LENGTH];
    printf("\nChoose message: ");
    scanf(" %31s", msg); //unfortunately does not work with MSG_LENGTH - 1

    strCopy(msg, newEntry.message, MSG_LENGTH);

    //return the new entry
    return newEntry;
};

//main

int main()
{
    pqueue pq = {};
    char action;

    do{
        action = getMenu();

        switch(action){
        case 'p':
            printQueue(&pq);
            break;
        case 'e':
            enqueue(&pq, getNewEntry());
            break;
        case 'd':
            dequeue(&pq);
            break;
        case 'x':
            break;
        }

    } while(action != 'x');

    return 0;
}
