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
        case 'N': return notSet;
        case 'H': return highest;
        case 'h': return high;
        case 'n': return normal;
        case 'l': return low;
        case 'L': return lowest;
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

//remove only here for debugging
void printQueue(struct pqueue* pqueue);

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
            printf("found a sport at index[%d]\n", i);
            return i;
        }
    }
    return -1; //should alsways find a spot, but lets make the compiler happy
}

void enqueue(struct pqueue* pqueue, struct entry entry){

    if(isFull(pqueue)){
        printf("priority queue already full!\n");
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
    printf("priority queue now contains %d entry\n", pqueue->count);
}

void dequeue(struct pqueue* pqueue){

}

//output

void printQueue(struct pqueue* pqueue){

    //run for all exiting entries
    for(int i = 0; i < pqueue->count; i++){
        entry e = pqueue->entries[i];
        printf("Index[%d] %c: %s\n", i, getPrioLetter(e.prio), e.message);
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
    printf("Choose action: print queue (p), enqueue entry (e), dequeue entry (d) or exit (x): ");
    scanf(" %c", &input);

    while(!menuInputValid(input)){
        printf("Input invalid! Try again: ");
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
    printf("Choose priority: lowest (L), low (l), normal (n), high (h), highest (H): ");
    scanf(" %c", &prio);

    while(!entryPrioValid(prio)){
        printf("Input invalid! Try again: ");
        scanf(" %c", &prio);
    }

    newEntry.prio = getPrioEnum(prio);

    //get the message (always correct, no need for validation)
    char msg[MSG_LENGTH];
    printf("Choose message: ");
    scanf(" %31s", msg); //unfortunately does not work with MSG_LENGTH - 1

    strCopy(msg, newEntry.message, MSG_LENGTH);

    //return the new entry
    return newEntry;
};

//main

int main()
{
    char action = '\0';
    pqueue pq = {};

    while(action != 'x'){

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
    }
    return 0;
}
