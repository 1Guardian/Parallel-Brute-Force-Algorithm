#include <vector>
#include <string>
#include <stdlib.h>
#include <cmath>

#include "dataStructures.h"
#include "calculateDValues.h"

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
                            std::vector<struct _child*>* children){

    //calculate the R value (the retail cost of all the clothing summed)
    int retailCost = 0;
    for (int j =0; j < clothing->size(); j++){
        retailCost += clothing->at(j)->value;
    }

    //total Children count
    int totalChildren = children->size();

    //calculate R/N Which is the fair share of each child
    float fairShare = (float)retailCost/(float)totalChildren;

    //find the 'D' value for each child
    for (int j = 0; j < finalChains->size(); j++){

        //temp D value
        float tempDValue = 0;

        //calculate error for each child
        for (int i = 0; i < finalChains->at(0).size(); i++){

            //get Ci (which is sum of all clothing that child has)
            float Ci = 0;
            for (int k = 0; k < childrenClothingCombinations->at(finalChains->at(j)[i])->clothing.size(); k++){

                Ci += clothing->at(childrenClothingCombinations->at(finalChains->at(j)[i])->clothing.at(k))->value;
            }

            tempDValue += std::abs(fairShare - Ci);
        }

        //add to final D values
        dValues->push_back(tempDValue); 
    }

}