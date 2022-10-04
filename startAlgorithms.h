#ifndef START_ALGORITHMS_H
#define START_ALGORITHMS_H

#include <fstream>
#include <vector>
#include <sstream>

/**********************************************************************************************************

void startSlowAlgorithm(int largestMultiple){
        
    This function sets up all the data needed by the threads before they reach the dispatcher
    for the slow algorithm

**********************************************************************************************************/
void startSlowAlgorithm(int largestMultiple);

/**********************************************************************************************************

void startQuickAlgorithm(int largestMultiple){
        
    This function sets up all the data needed by the threads before they reach the dispatcher for the 
    quick algorithm

**********************************************************************************************************/
void startQuickAlgorithm(int largestMultiple);

#endif