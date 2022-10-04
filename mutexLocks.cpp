#include "mutexLocks.h"
#include <vector>
#include <iostream>
#include "dataStructures.h"

/**********************************************************************************************************

extern globals

Due to the nature of pthreads and how they are semi-unable to take data with them that
is outside of the semi-global scope, global variables was the best way to sustain functionality.
However, since they are globals and not structures or datatypes, they must be declared and accepted
only once and then referenced via extern by all other files, such as here.

**********************************************************************************************************/

//make children vector
extern std::vector<struct _child*> children;
extern pthread_mutex_t childrenMutex;

//make the clothing vector
extern std::vector<struct _clothes*> clothing;
extern pthread_mutex_t clothingMutex;

//struct used for keeping all possible combinations
//of children and clothing
extern std::vector<struct _child*> childrenClothingCombinations;

//vector to keep track of children number division boundaries
//will be the number of the first of the next set of children
extern std::vector<int> childrenSeparators;
extern pthread_mutex_t childSeparatorsMutex;

//vector to keep track of the available clothing remaining
extern std::vector<int> AvailableClothes;
extern pthread_mutex_t AvailableClothesMutex;

//random child chain for starting
extern std::vector<int> childChain;
extern pthread_mutex_t childChainMutex;

//vector of a vector of ints to keep track of final chain possibilities
extern std::vector<std::vector<int>> finalChains;
extern pthread_mutex_t finalChainsMutex;

//vector to act as a queue for the threads to dispatch
//from
extern std::vector<struct _child*> startingChildrenClothingCombinations;
extern pthread_mutex_t startingChildrenClothingCombinationsMutex;

//float to store the lowest D-Value. This will let me terminate
//threads much quicker (hopefully). It is being kept in the mutex
//globals section because it will need a mutex to protect it.
extern float lowestDValue;
extern pthread_mutex_t lowestDValueMutex;
extern int slowAlgorithmIndex;

/**********************************************************************************************************

void addToFinalCombinations(std::vector<int> childChain)
    
    This function Protects the finalChains object from race conditions. When a new 
    value needs to be added to it, a thread calls this function and a mutex prevents
    the thread from accessing the structure if another thread is busy with it. If it
    is not, the thread locks the mutex and enters the function to add a value to finalChains,
    unlocking the mutex as it leaves for the next thread to stop spinning and enter.

**********************************************************************************************************/
void addToFinalCombinations(std::vector<int> childChain, float currentDValue){

    //lock the mutex before entry
    while(pthread_mutex_lock(&finalChainsMutex) != 0);

    //update the final chain system
    if (currentDValue < lowestDValue){
        finalChains.push_back(childChain);
        lowestDValue = currentDValue;
    }

    //unlock the mutex 
    pthread_mutex_unlock(&finalChainsMutex);

}

/**********************************************************************************************************

void slowAddToFinalCombinations(std::vector<std::vector<int>> childChain, float currentDValue)
    
    This function Protects the finalChains object from race conditions. When a new 
    value needs to be added to it, a thread calls this function and a mutex prevents
    the thread from accessing the structure if another thread is busy with it. If it
    is not, the thread locks the mutex and enters the function to add a value to finalChains,
    unlocking the mutex as it leaves for the next thread to stop spinning and enter.

**********************************************************************************************************/
void slowAddToFinalCombinations(std::vector<std::vector<int>> childChain, float currentDValue){

    //lock the mutex before entry
    while(pthread_mutex_lock(&finalChainsMutex) != 0);

    //update the final chain system
    if (currentDValue < lowestDValue){
        finalChains.clear();
        finalChains.insert(finalChains.end(), childChain.begin(), childChain.end());
        lowestDValue = currentDValue;
    }

    //unlock the mutex 
    pthread_mutex_unlock(&finalChainsMutex);

}

/**********************************************************************************************************

void slowCheckIndices(int* index)
    
    This function Protects the slowAlgorithmIndex object which is protected by the childreMutex
    Mutex. The counter allows the slower variant of the algorithm to run in parallel without needing
    to pass the exact size of the arrays that the threads would be inheriting from their parent.
    This is due to the fact that data must be passed to pthreads as void information and then
    cast back into a type. This circumvents that issue

**********************************************************************************************************/
void slowCheckIndices(int* index){

    //lock the mutex before entry
    while(pthread_mutex_lock(&childrenMutex) != 0);

    //increment which position we are on
    slowAlgorithmIndex++;
    *index = slowAlgorithmIndex;

    //unlock the mutex 
    pthread_mutex_unlock(&childrenMutex);

}

/**********************************************************************************************************

struct _child* getStartingChildCombination(int* status, int* Identifier)
    
    This function gets the child-clothing combinations that make up the first segment of the
    overall data table. This means, that whatever the first child found in the file is, will be
    processed through this function when a thread needs to get a new entry to begin working on.
    This function is called at the start of every thread's run.

**********************************************************************************************************/
struct _child* getStartingChildCombination(int* status, int* Identifier){

    //pointer to point to the most recently selected child
    struct _child* ptr = NULL;

    //lock the mutex before entry
    while(pthread_mutex_lock(&startingChildrenClothingCombinationsMutex) != 0);

    //update the final chain system
    if (startingChildrenClothingCombinations.size() > 0){
          *Identifier = startingChildrenClothingCombinations.size() - 1;
          ptr = startingChildrenClothingCombinations[startingChildrenClothingCombinations.size() - 1];
          startingChildrenClothingCombinations.pop_back();
          *status = 0;
    }

    else {
        *status = -1;
    }

    //unlock the mutex 
    pthread_mutex_unlock(&startingChildrenClothingCombinationsMutex);

    //return
    return ptr;

}