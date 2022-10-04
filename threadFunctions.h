#ifndef THREAD_FUNCTIONS_H
#define THREAD_FUNCTIONS_H

#include <fstream>
#include <vector>
#include <sstream>

/**********************************************************************************************************

void bruteForceWalk(std::vector<struct _child*>* childrenClothingCombinations, 
                    std::vector<int>* childrenSeparators, 
                    std::vector<int>* AvailableClothes, 
                    std::vector<std::vector<int>>* finalChains,
                    std::vector<struct _clothes*>* clothing,
                    std::vector<int> childChain, 
                    int depth = 0,
                    int starting = 0,
                    int ending = 0,
                    int largestMultiple = 0,
                    struct _child* queueMember = NULL,
                    int queueMemberId = 0)
        
    This function does the brute force attempts at generating our 'D' values
    It places them into a vector of structs with a boolean set to signify whether
    or not the output was good (as in completed a full chain)
    This function is currently implemented as a recursive call to itself 
    in between itterations. It can run in a single-threaded context, but it is 
    designed to run on multiple threads concurrently.

**********************************************************************************************************/
void bruteForceWalk(std::vector<struct _child*>* childrenClothingCombinations, 
                    std::vector<int>* childrenSeparators, 
                    std::vector<int>* AvailableClothes, 
                    std::vector<std::vector<int>>* finalChains,
                    std::vector<struct _clothes*>* clothing,
                    std::vector<int> childChain, 
                    float currentDValue,
                    int depth = 0,
                    int starting = 0,
                    int ending = 0,
                    int largestMultiple = 0,
                    struct _child* queueMember = NULL,
                    int queueMemberId = 0);

/**********************************************************************************************************

void* threadDispatchBruteForceWalk(void* voidInOutData)
        
    this function serves as the starting point for the
    pthread action. All pthreads will start here
    and call the "bruteForceWalk" function with their
    structs of data and they will only run in the range
    given by the parent

**********************************************************************************************************/
void* threadDispatchBruteForceWalk(void* voidInOutData);

#endif