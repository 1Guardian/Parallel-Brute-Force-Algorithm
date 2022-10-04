#include <vector>
#include <iostream>
#include <cmath>
#include "dataStructures.h"
#include "mutexLocks.h"

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
                    int queueMemberId = 0){
    
    //gain access to the lowestDValue and the rValue
    extern float lowestDValue;
    extern float rValue;
    extern int childNumber;
    float StartingDValue = currentDValue;

    //stop condition to prevent overlooping and
    //return the final chained possible value
    if (depth == childNumber){

        //make a subset of the relevant clothing
        std::vector<struct _clothes*> relevantClothing;
        int x = depth;

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
        std::vector<std::vector<int>> subsetTemp = subset;

        for (int i = 0; i < std::pow(2, clothingNumbers.size()); i++){

            std::vector<int> subsetVector;
            subsetTemp.clear();

            for (int j = 0; j < clothingNumbers.size(); j++)
            {
                if ((i & (1 << j)) != 0)
                    subsetVector.push_back(clothingNumbers[j]);
            }

            subsetTemp.push_back(subsetVector);

            for (int j = 0; j < subsetTemp.size(); j++){

                currentDValue = StartingDValue;

                //reset the AvailableClothes Vector on each run
                for (int k =0; k < AvailableClothes->size(); k++){
                    if (AvailableClothes->at(k) >= depth){
                        AvailableClothes->at(k) = -1;
                    }
                }

                //go through each child and run all possible sub-combinations by recursing
                //into this function. To start, remove clothing from Available Clothing
                //that the current child of the recurse would take up.
                int summer = -1000;
                int winter = -1000;
                float Ci = 0;
                for(int l = 0; l < subsetTemp[j].size(); l++ ){

                    //make sure clothing article is available
                    if (AvailableClothes->at(subsetTemp[j][l]) == -1) {

                        AvailableClothes->at(subsetTemp[j][l]) = depth;

                        //update full clothing value
                        Ci += clothing->at(subsetTemp[j][l])->value;

                        //check for summer and winter status
                        if(clothing->at(subsetTemp[j][l])->weather == 1){
                            summer = 1;
                        }
                        else if(clothing->at(subsetTemp[j][l])->weather == 0){
                            winter = 1;
                        }
                    }

                    //if not available, break loop
                    else{
                        summer = 0;
                        break;
                    }
                }

                //check to see if any clothes are left over
                //if there are any, count run as bad as each item
                //must go to one child
                for (int k =0; k < AvailableClothes->size(); k++){
                    if (AvailableClothes->at(k) == -1){
                        summer = 0;
                        break;
                    }
                }

                //check the current accumulated D-Value against the lowest known D-Value
                //if it is larger, then return becasue we can't get lower
                //also update the counter for the current d-Value
                float childFairness = std::abs((rValue/((float)childNumber+1)) - Ci);
                currentDValue += childFairness;
                if (currentDValue >= lowestDValue){
                    summer = 0;
                    currentDValue -= childFairness;
                }


                //add value to child chain
                //if the child has both a summer
                //and winter object
                if (summer == 1 && winter == 1){

                    currentChildChain.push_back(subsetVector);

                    slowAddToFinalCombinations(currentChildChain, currentDValue);

                    //reset chain and value
                    currentDValue -= childFairness;
                    currentChildChain.pop_back();

                }
            }   
        }
    }

    //initial condition to begin whole brute force
    //checking system
    else if (depth == 0){

        currentDValue = StartingDValue;

        //reset the AvailableClothes Vector on each run
        for (int k =0; k < AvailableClothes->size(); k++){
            if (AvailableClothes->at(k) >= depth){
                AvailableClothes->at(k) = -1;
            }
        }

        //go through each child and run all possible sub-combinations by recursing
        //into this function. To start, remove clothing from Available Clothing
        //that the current child of the recurse would take up.
        int summer = -1000;
        int winter = -1000;
        float Ci = 0;
        for(int j = 0; j < queueMember->clothing.size(); j++ ){

            AvailableClothes->at(queueMember->clothing.at(j)) = 0;

            //update full clothing value
            Ci += clothing->at(queueMember->clothing.at(j))->value;

            //check for summer and winter status
            if(clothing->at(queueMember->clothing.at(j))->weather == 1){
                summer = 1;
            }
            else if(clothing->at(queueMember->clothing.at(j))->weather == 0){
                winter = 1;
            }
        }

        //check to see if we need to even look at the
        //possibilities for this chain. (If there are)
        //more children * 2 (1 winter and 1 summer minimum)
        //than there are available clothes, we can kill this
        //branch immediately
        int neededClothes = childNumber;
        int totalClothes = 0;
        for (int k = 0; k < AvailableClothes->size(); k++){
            if (AvailableClothes->at(k) == -1){
                totalClothes++;
            }
        }
        if (neededClothes * 2 > totalClothes){
            summer = 0;
            winter = 0;
        }

        //check the current accumulated D-Value against the lowest known D-Value
        //if it is larger, then return becasue we can't get lower
        //also update the counter for the current d-Value
        float childFairness = std::abs((rValue/((float)childNumber+1)) - Ci);
        currentDValue += childFairness;
        if (currentDValue >= lowestDValue){
            summer = 0;
            currentDValue -= childFairness;
        }
        
        //add value to child chain
        //if the child has both a summer
        //and winter object
        if (summer == 1 && winter == 1){
            currentChildChain.push_back(queueMember->clothing);

            //recurse
            slowBruteForceWalk(childrenClothingCombinations, 
                    childrenSeparators, 
                    AvailableClothes, 
                    finalChains,
                    clothing,
                    currentChildChain, 
                    currentDValue,
                    children,
                    1);

            //reset chain and value
            currentDValue -= childFairness;
            currentChildChain.pop_back();
        }
    }

    //all other sub-chains
    else {

        //make a subset of the relevant clothing
        std::vector<struct _clothes*> relevantClothing;
        int x = depth;

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
        std::vector<std::vector<int>> subsetTemp = subset;

        for (int i = 0; i < std::pow(2, clothingNumbers.size()); i++){

            std::vector<int> subsetVector;
            subsetTemp.clear();

            for (int j = 0; j < clothingNumbers.size(); j++)
            {
                if ((i & (1 << j)) != 0)
                    subsetVector.push_back(clothingNumbers[j]);
            }

            subsetTemp.push_back(subsetVector);

            for (int j = 0; j < subsetTemp.size(); j++){
                
                //reset the current DValue
                currentDValue = StartingDValue;

                //reset the AvailableClothes Vector on each run
                for (int k =0; k < AvailableClothes->size(); k++){
                    if (AvailableClothes->at(k) >= depth){
                        AvailableClothes->at(k) = -1;
                    }
                }

                //go through each child and run all possible sub-combinations by recursing
                //into this function. To start, remove clothing from Available Clothing
                //that the current child of the recurse would take up.
                int summer = -1000;
                int winter = -1000;
                float Ci = 0;
                for(int l = 0; l < subsetTemp[j].size(); l++ ){

                    //make sure clothing article is available
                    if (AvailableClothes->at(subsetTemp[j][l]) == -1) {

                        AvailableClothes->at(subsetTemp[j][l]) = depth;

                        //update full clothing value
                        Ci += clothing->at(subsetTemp[j][l])->value;

                        //check for summer and winter status
                        if(clothing->at(subsetTemp[j][l])->weather == 1){
                            summer = 1;
                        }
                        else if(clothing->at(subsetTemp[j][l])->weather == 0){
                            winter = 1;
                        }
                    }

                    //if not available, break loop
                    else{
                        summer = 0;
                        break;
                    }
                }

                //check to see if we need to even look at the
                //possibilities for this chain. (If there are)
                //more children * 2 (1 winter and 1 summer minimum)
                //than there are available clothes, we can kill this
                //branch immediately
                int neededClothes = childNumber - depth;
                int totalClothes = 0;
                for (int k = 0; k < AvailableClothes->size(); k++){
                    if (AvailableClothes->at(k) == -1){
                        totalClothes++;
                    }
                }
                if (neededClothes * 2 > totalClothes){
                    summer = 0;
                    winter = 0;
                }

                //check the current accumulated D-Value against the lowest known D-Value
                //if it is larger, then return becasue we can't get lower
                //also update the counter for the current d-Value
                float childFairness = std::abs((rValue/((float)childNumber+1)) - Ci);
                currentDValue += childFairness;
                if (currentDValue >= lowestDValue){
                    summer = 0;
                    currentDValue -= childFairness;
                }

                //add value to child chain
                //if the child has both a summer
                //and winter object
                if (summer == 1 && winter == 1){

                    currentChildChain.push_back(subsetVector);

                    //recurse
                    slowBruteForceWalk(childrenClothingCombinations, 
                            childrenSeparators, 
                            AvailableClothes, 
                            finalChains,
                            clothing,
                            currentChildChain, 
                            currentDValue,
                            children,
                            depth+1);

                    currentChildChain.pop_back();
                    currentDValue -= childFairness;
                }
            }
        }
    }


    //itterative loop to go through each child 
    return;
}

/**********************************************************************************************************

void* slowThreadDispatchBruteForceWalk(void* voidInOutData)
        
    this function serves as the starting point for the
    pthread action. All pthreads will start here
    and call the "slowBruteForceWalk" function with their
    structs of data and they will only run in the range
    given by the parent

**********************************************************************************************************/
void* slowThreadDispatchBruteForceWalk(void* voidInOutData){

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

    //get our starting and ending indices
    struct _firstIndices* ranges = (struct _firstIndices*)(voidInOutData);

    //make an available clothes vector
    std::vector<int> AvailableClothesCustom;

    for (int i =0; i < clothing.size(); i++){
        AvailableClothesCustom.push_back(-1);
    }

    //get all relevant passed values
    int startingRange = ranges->startingIndex;
    int endingRange = ranges->endingIndex;
    int commonMultiple = ranges->multiple;
    int x = 0;
    int currentRangeIndex = 0;
    std::vector<std::vector<int>> currentChildChain;

    //make a subset of the relevant clothing
    std::vector<struct _clothes*> relevantClothing;

    //go through all the clothing and get all the clothing that
    //we will be able to use on the child in question
    for (int i = 0; i < clothing.size(); i++){

        //check if clothing size is the same as child or the clothing is all sizes fit
        if (clothing.at(i)->size == children.at(x)->childSize || clothing.at(i)->size == 4){
            relevantClothing.push_back(clothing.at(i));
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
    std::vector<std::vector<int>> subsetTemp = subset;

	for (int i = 0; i < std::pow(2, clothingNumbers.size()); i++){

        std::vector<int> subsetVector;
        subsetTemp.clear();

		for (int j = 0; j < clothingNumbers.size(); j++)
		{
			if ((i & (1 << j)) != 0)
				subsetVector.push_back(clothingNumbers[j]);
		}

        subsetTemp.push_back(subsetVector);

        //control which thread does what without
        //passing the indices at all
        if (startingRange != currentRangeIndex){
            currentRangeIndex++;
            continue;
        }
        else{
            //get the index that we should be focusing on
            slowCheckIndices(&startingRange);
            currentRangeIndex++;
        }

        for (int j = 0; j < subsetTemp.size(); j++){

            //status int to make sure we got a queue member
            //and ID variable to hold the combination ID
            int status = 0;
            int Identifier = 0;

            //generate a very generic template type for the walk
            struct _child* queueMember = new struct _child(0, 0);

            //populate the generic
            for(int l = 0; l < subsetTemp[j].size(); l++)
                queueMember->clothing.push_back(subsetTemp[j][l]);

            if (status == 0){

                //call the brute-force walk
                slowBruteForceWalk(&childrenClothingCombinations, 
                            &childrenSeparators, 
                            &AvailableClothesCustom, 
                            &ranges->personalFinalChain,
                            &clothing,
                            currentChildChain,
                            0.0,
                            &children,
                            0,
                            startingRange,
                            endingRange,
                            commonMultiple,
                            queueMember,
                            Identifier);

            }
       }
    }
    
    return NULL;
}