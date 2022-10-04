#ifndef SLOW_THREAD_FUNCTIONS_H
#define SLOW_THREAD_FUNCTIONS_H

#include <fstream>
#include <vector>
#include <sstream>

/**********************************************************************************************************

void slowBruteForceWalk(std::vector<struct _child*>* childrenClothingCombinations, 
                    std::vector<int>* childrenSeparators, 
                    std::vector<int>* AvailableClothes, 
                    std::vector<std::vector<int>>* finalChains,
                    std::vector<struct _clothes*>* clothing,
                    std::vector<std::vector<int>> currentChildChain, 
                    float currentDValue,
                    std::vector<struct _child*>* children,
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
    designed to run on multiple threads concurrently. It is also the slower variant of
    the same algorithm under the name "bruteForceWalk". The main difference is that this
    version does multiple passes of the same calculations to save on memory since RAM is 
    not unlimited, and the data sets get very large.

**********************************************************************************************************/
void slowBruteForceWalk(std::vector<struct _child*>* childrenClothingCombinations, 
                    std::vector<int>* childrenSeparators, 
                    std::vector<int>* AvailableClothes, 
                    std::vector<std::vector<int>>* finalChains,
                    std::vector<struct _clothes*>* clothing,
                    std::vector<std::vector<int>> currentChildChain, 
                    float currentDValue,
                    std::vector<struct _child*>* children,
                    int depth = 0,
                    int starting = 0,
                    int ending = 0,
                    int largestMultiple = 0,
                    struct _child* queueMember = NULL,
                    int queueMemberId = 0);

/**********************************************************************************************************

void* slowThreadDispatchBruteForceWalk(void* voidInOutData)
        
    this function serves as the starting point for the
    pthread action. All pthreads will start here
    and call the "bruteForceWalk" function with their
    structs of data and they will only run in the range
    given by the parent

**********************************************************************************************************/
void* slowThreadDispatchBruteForceWalk(void* voidInOutData);

#endif