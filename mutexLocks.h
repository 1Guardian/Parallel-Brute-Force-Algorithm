#ifndef MUTEX_LOCKS_H
#define MUTEX_LOCKS_H

#include <vector>


/**********************************************************************************************************

void slowCheckIndices(int* index)
    
    This function Protects the slowAlgorithmIndex object which is protected by the childreMutex
    Mutex. The counter allows the slower variant of the algorithm to run in parallel without needing
    to pass the exact size of the arrays that the threads would be inheriting from their parent.
    This is due to the fact that data must be passed to pthreads as void information and then
    cast back into a type. This circumvents that issue

**********************************************************************************************************/
void slowCheckIndices(int* index);

/**********************************************************************************************************

void slowAddToFinalCombinations(std::vector<std::vector<int>> childChain, float currentDValue)
    
    This function Protects the finalChains object from race conditions. When a new 
    value needs to be added to it, a thread calls this function and a mutex prevents
    the thread from accessing the structure if another thread is busy with it. If it
    is not, the thread locks the mutex and enters the function to add a value to finalChains,
    unlocking the mutex as it leaves for the next thread to stop spinning and enter.

**********************************************************************************************************/
void slowAddToFinalCombinations(std::vector<std::vector<int>> childChain, float currentDValue);

/**********************************************************************************************************

void addToFinalCombinations(std::vector<int> childChain, float currentDValue)
    
    This function Protects the finalChains object from race conditions. When a new 
    value needs to be added to it, a thread calls this function and a mutex prevents
    the thread from accessing the structure if another thread is busy with it. If it
    is not, the thread locks the mutex and enters the function to add a value to finalChains,
    unlocking the mutex as it leaves for the next thread to stop spinning and enter.

**********************************************************************************************************/
void addToFinalCombinations(std::vector<int> childChain, float currentDValue);

/**********************************************************************************************************

struct _child* getStartingChildCombination(int* status, int* Identifier)
    
    This function gets the child-clothing combinations that make up the first segment of the
    overall data table. This means, that whatever the first child found in the file is, will be
    processed through this function when a thread needs to get a new entry to begin working on.
    This function is called at the start of every thread's run.

**********************************************************************************************************/
struct _child* getStartingChildCombination(int* status, int* Identifier);

#endif