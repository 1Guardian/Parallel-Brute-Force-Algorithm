#ifndef CALCULATE_D_VALUES_H
#define CALCULATE_D_VALUES_H

#include <vector>
#include <string>

#include "dataStructures.h"

/**********************************************************************************************************

void calculateFinalDValues( std::vector<float>* dValues,
                            std::vector<struct _child*>* childrenClothingCombinations, 
                            std::vector<int>* childrenSeparators, 
                            std::vector<int>* AvailableClothes, 
                            std::vector<std::vector<int>>* finalChains,
                            std::vector<struct _clothes*>* clothing,
                            std::vector<int> childChain)
    
    This function is used to calculate the final D-values of the given child-clothing
    combinations. The lowest D value is the desired outcome, but before that is 
    determined, all possible D-Values are pushed to the vector that is passed by pointer.

**********************************************************************************************************/
void calculateFinalDValues( std::vector<float>* dValues,
                            std::vector<struct _child*>* childrenClothingCombinations, 
                            std::vector<int>* childrenSeparators, 
                            std::vector<int>* AvailableClothes, 
                            std::vector<std::vector<int>>* finalChains,
                            std::vector<struct _clothes*>* clothing,
                            std::vector<struct _child*>* children);

#endif 