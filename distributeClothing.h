#ifndef DISTRIBUTE_CLOTHING_H
#define DISTRIBUTE_CLOTHING_H

#include <vector>
#include "dataStructures.h"

/**********************************************************************************************************

void distributeClothing(std::vector<struct _child*>* children,
                 std::vector<struct _clothes*>* clothing,
                 std::vector<struct _child*>* childrenClothingCombinations,
                 std::vector<int>* childrenSeparators
                 );
        
    function that will recursively call itself 
    on various itterations in an effort to check
    all possible combinations of children and clothing
    in a brute force manner. It will then return control
    to the main function or it will call an analysis 
    function to draw conclusions

**********************************************************************************************************/
void distributeClothing(std::vector<struct _child*>* children,
                 std::vector<struct _clothes*>* clothing,
                 std::vector<struct _child*>* childrenClothingCombinations,
                 std::vector<int>* childrenSeparators
                 );

#endif