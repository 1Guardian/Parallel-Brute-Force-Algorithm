#include <vector>
#include <iostream>
#include <cmath>
#include "pthread.h"
#include "dataStructures.h"
#include "threadFunctions.h"
#include "mutexLocks.h"
#include "distributeClothing.h"
#include "slowThreadFunctions.h"

/**********************************************************************************************************

void startSlowAlgorithm(int largestMultiple){
        
    This function sets up all the data needed by the threads before they reach the dispatcher
    for the slow algorithm

**********************************************************************************************************/
void startSlowAlgorithm(int largestMultiple){

        //make children vector
        extern std::vector<struct _child*> children;
            
        //set extern global
        extern int childNumber;
        childNumber = children.size()-1;

        //Spawn some child threads based on the "largestMultiple"
        //number and begin the brute force walk after creating
        //the memory shares for the threads
        pthread_t threads[largestMultiple];

        //NOTE: NEW IDEA: ALL DATA IS NOW GLOBAL AND 
        //IS ONLY ACCESSED BY CHILD THREADS VIA MUTEX
        //LOCKED FUNCTIONS.
        //still need to make the range set for the children
        struct _firstIndices* threadRanges[largestMultiple]; 

        //make the void data and covert it and fill it
        for(int i = 0; i < largestMultiple; i++){

            //waiting for threads
            threadRanges[i] = (struct _firstIndices*) malloc(sizeof(struct _firstIndices));

            //fill with the initial indices
            threadRanges[i]->multiple = 1;
            threadRanges[i]->startingIndex = i;
            threadRanges[i]->endingIndex = 1;
        }

        //create the threads and dispatch them
        //then wait for each one to finish it's task
        for(int i = 0; i < largestMultiple; i++){

            //dispatch the thread
            pthread_create(&threads[i], NULL, slowThreadDispatchBruteForceWalk, (void*)threadRanges[i]);
        }
        for(int i = 0; i < largestMultiple; i++){

            //waiting for threads
            pthread_join(threads[i], NULL);
        }
}

/**********************************************************************************************************

void startQuickAlgorithm(int largestMultiple){
        
    This function sets up all the data needed by the threads before they reach the dispatcher for the 
    quick algorithm

**********************************************************************************************************/
void startQuickAlgorithm(int largestMultiple){

    //access the extern arrays for starting the algorithm

    //make children vector
    extern std::vector<struct _child*> children;

    //struct used for keeping all possible combinations
    //of children and clothing
    extern std::vector<struct _child*> childrenClothingCombinations;

    //vector to keep track of children number division boundaries
    //will be the number of the first of the next set of children
    extern std::vector<int> childrenSeparators;

    //vector to act as a queue for the threads to dispatch
    //from
    extern std::vector<struct _child*> startingChildrenClothingCombinations;

    //external reference for child count
    extern int childNumber;

    //setup the queue of clothing combinations 
    //for the threads to work on
    for(int i = 0; i < childrenSeparators[0]; i++){
        startingChildrenClothingCombinations.push_back(childrenClothingCombinations[i]);
    }

    //set extern global
    childNumber = childrenSeparators.size() - 1;

    //Spawn some child threads based on the "largestMultiple"
    //number and begin the brute force walk after creating
    //the memory shares for the threads
    pthread_t threads[largestMultiple];

    //NOTE: NEW IDEA: ALL DATA IS NOW GLOBAL AND 
    //IS ONLY ACCESSED BY CHILD THREADS VIA MUTEX
    //LOCKED FUNCTIONS.
    //still need to make the range set for the children
    struct _firstIndices* threadRanges[largestMultiple]; 

    //make the void data and covert it and fill it
    for(int i = 0; i < largestMultiple; i++){

        //waiting for threads
        threadRanges[i] = (struct _firstIndices*) malloc(sizeof(struct _firstIndices));

        //fill with the initial indices
        threadRanges[i]->multiple = largestMultiple;
        threadRanges[i]->startingIndex = i;
        threadRanges[i]->endingIndex = childrenSeparators.at(0);
    }

    //create the threads and dispatch them
    //then wait for each one to finish it's task
    for(int i = 0; i < largestMultiple; i++){

        //dispatch the thread
        pthread_create(&threads[i], NULL, threadDispatchBruteForceWalk, (void*)threadRanges[i]);
    }
    for(int i = 0; i < largestMultiple; i++){

        //waiting for threads
        pthread_join(threads[i], NULL);
    }
}