#include <vector>
#include <iostream>

#include "dataStructures.h"
#include "distributeClothing.h" 

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
                 ){

    //theorhetical memory saving point:
    //only calculate each size once and 
    //give pointers to each size allocation
    //should also decrease time spent in this function
    bool small = false;
    bool medium = false;
    bool large = false;
    bool extraLarge = false;
    int smallEndIndex = -1;
    int mediumEndIndex = -1;
    int largeEndIndex = -1;
    int extraLargeEndIndex = -1;
    
    //for each child go through and give them all possible clothing
    //combinations and add it to the combinations vector
    for(int x = 0; x < children->size(); x++){

        //check to see if we already did this calculation
        if (children->at(x)->childSize == 0 && small != true || 
            children->at(x)->childSize == 1 && medium != true || 
            children->at(x)->childSize == 2 && large != true || 
            children->at(x)->childSize == 3 && extraLarge != true){

            //if we haven't update that we are doing it now
            if (children->at(x)->childSize == 0)
                small = true;
            if (children->at(x)->childSize == 1)
                medium = true;
            if (children->at(x)->childSize == 2)
                large = true;
            if (children->at(x)->childSize == 3)
                extraLarge = true;

            //make a subset of the relevant clothing
            std::vector<struct _clothes*> relevantClothing;

            //go through all the clothing and get all the clothing that
            //we will be able to use on the child in question
            for (int i = 0; i < clothing->size(); i++){

                //check if clothing size is the same as child or the clothing is all sizes fit
                if (clothing->at(i)->size == children->at(x)->childSize || clothing->at(i)->size == 4){
                    relevantClothing.push_back(clothing->at(i));
                }
            }

            //go through all useable clothes and find all subsets that
            //do not repeat

            std::vector<int> clothingNumbers;

            for (int k = 0; k < relevantClothing.size(); k++){
                clothingNumbers.push_back(relevantClothing[k]->number);
            }

            std::vector<std::vector<int>> subset;
            std::vector<int> empty;
            subset.push_back(empty);

            for (int i = 0; i < clothingNumbers.size(); i++)
            {
                std::vector<std::vector<int>> subsetTemp = subset;

                for (int j = 0; j < subsetTemp.size(); j++)
                    subsetTemp[j].push_back(clothingNumbers[i]);

                for (int j = 0; j < subsetTemp.size(); j++)
                    subset.push_back(subsetTemp[j]);
            }

            //push all the subsets into the child clothing matrix
            for (int i = 0; i < subset.size(); i++){

            //NEW
            int summer = -1000;
            int winter = -1000;

            //make the new child entry that will have clothes added to it
            struct _child* newChild = new struct _child(children->at(x)->childNumber, children->at(x)->childSize);

            //add the position of the array that the child is in
            if (childrenSeparators->size() == 0)
                newChild->childPosition = i;

                for (int j = 0; j < subset[i].size(); j++){
                    
                    //add the entries to child struct (and add value to total value of child)
                    for (int k = 0; k < relevantClothing.size(); k++){

                        if (relevantClothing.at(k)->number == subset[i][j]){
                            newChild->clothing.push_back(relevantClothing.at(k)->number);
                            newChild->totalValue += relevantClothing.at(k)->value;
                        }

                        if (relevantClothing.at(k)->weather == 0){
                            summer = 0;
                        }
                        else if (relevantClothing.at(k)->weather == 1){
                            winter = 0;
                        }
                    }

                }

                //add new child to the matrix
                childrenClothingCombinations->push_back(newChild);
            }

            //add the marker for the break of the child separator array
            childrenSeparators->push_back(childrenClothingCombinations->size());

            //update our pool markers for future sizes
            if (children->at(x)->childSize == 0)
                smallEndIndex = childrenSeparators->size()-1;
            if (children->at(x)->childSize == 1)
                mediumEndIndex = childrenSeparators->size()-1;
            if (children->at(x)->childSize == 2)
                largeEndIndex = childrenSeparators->size()-1;
            if (children->at(x)->childSize == 3)
                extraLargeEndIndex = childrenSeparators->size()-1;
        }

        //we already did the subsets for this size, so to save
        //on memory, we are just going to point to the 
        //child structs we already made, and treat them
        //as new child entries
        else {

            if (children->at(x)->childSize == 0){

                if (smallEndIndex == 0){
                    for (int i = 0; i < childrenSeparators->at(smallEndIndex); i++){
                        childrenClothingCombinations->push_back(childrenClothingCombinations->at(i));
                    }
                }
                else{
                    for (int i = childrenSeparators->at(smallEndIndex - 1); i < childrenSeparators->at(smallEndIndex); i++){
                        childrenClothingCombinations->push_back(childrenClothingCombinations->at(i));
                    }
                }
                //add the marker for the break of the child separator array
                childrenSeparators->push_back(childrenClothingCombinations->size());
            }
            if (children->at(x)->childSize == 1){

                if (mediumEndIndex == 0){
                    for (int i = 0; i < childrenSeparators->at(mediumEndIndex); i++){
                        childrenClothingCombinations->push_back(childrenClothingCombinations->at(i));
                    }
                }
                else{
                    for (int i = childrenSeparators->at(mediumEndIndex - 1); i < childrenSeparators->at(mediumEndIndex); i++){
                        childrenClothingCombinations->push_back(childrenClothingCombinations->at(i));
                    }
                }
                //add the marker for the break of the child separator array
                childrenSeparators->push_back(childrenClothingCombinations->size());
            }
            if (children->at(x)->childSize == 2){

                if (largeEndIndex == 0){
                    for (int i = 0; i < childrenSeparators->at(largeEndIndex); i++){
                        childrenClothingCombinations->push_back(childrenClothingCombinations->at(i));
                    }
                }
                else{
                    for (int i = childrenSeparators->at(largeEndIndex - 1); i < childrenSeparators->at(largeEndIndex); i++){
                        childrenClothingCombinations->push_back(childrenClothingCombinations->at(i));
                    }
                }
                //add the marker for the break of the child separator array
                childrenSeparators->push_back(childrenClothingCombinations->size());
            }
            if (children->at(x)->childSize == 3){

                if (extraLargeEndIndex == 0){
                    for (int i = 0; i < childrenSeparators->at(extraLargeEndIndex); i++){
                        childrenClothingCombinations->push_back(childrenClothingCombinations->at(i));
                    }
                }
                else{
                    for (int i = childrenSeparators->at(extraLargeEndIndex - 1); i < childrenSeparators->at(extraLargeEndIndex); i++){
                        childrenClothingCombinations->push_back(childrenClothingCombinations->at(i));
                    }
                }
                //add the marker for the break of the child separator array
                childrenSeparators->push_back(childrenClothingCombinations->size());
            }
        }

    }
    return;
} 