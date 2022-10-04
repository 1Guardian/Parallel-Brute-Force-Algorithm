#include <iostream>
#include <vector>
#include <string>
#include <cmath> 
#include <algorithm> 
#include <fstream>
#include <sstream>
#include <thread>
#include <unistd.h>

#include "pthread.h"
#include "dataStructures.h"
#include "globalsAndMutex.hpp"
#include "takeInput.h"
#include "threadFunctions.h"
#include "mutexLocks.h"
#include "calculateDValues.h"
#include "distributeClothing.h"
#include "writeOutFile.h"
#include "slowThreadFunctions.h"
#include "slowWriteOutFile.h"
#include "startAlgorithms.h"

int main(int argc, char** argv)
{
    //setup the mutex 
    if (pthread_mutex_init(&finalChainsMutex, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }

    //check for hard switch to force algorithm
    bool switchOverride = false;
    if (argv[3] != NULL){
        if (std::string(argv[3]) == "slow")
            switchOverride = true;
    }

    //fake input for clothing size
    std::vector<int> clothingSize;

    //fake input for value of clothes
    std::vector<int> clothingPrice;

    //fake input for clothing season
    std::vector<int> clothingSeasons;

    //fake input for children
    std::vector<int> childrenSize;

    //vector for final 'D' values from algorithm
    std::vector<float> dValues;

    //vector for initial Children numbers (in the event they are swapped)
    std::vector<std::string> originalChildrenNumbers;

    //vector for initial clothing numbers (in the event they are swapped)
    std::vector<std::string> originalClothingNumbers;

    //get processor count and a safe number of splits
    const int processorCount = std::thread::hardware_concurrency();
    int largestMultiple = processorCount;

    //read in from the file supplied and convert
    //the data into the vectors used above
    takeInInput(argv[1], &clothingSize, &clothingPrice, &clothingSeasons, &childrenSize, &originalChildrenNumbers, &originalClothingNumbers);
    
    //number of children and clothes
    int numberOfChildren = childrenSize.size();
    int numberOfClothes = clothingSize.size();

    //make call to the data converter 
    convertData(&clothingSize[0], 
                 &clothingPrice[0], 
                 &clothingSeasons[0], 
                 &childrenSize[0], 
                 numberOfClothes,
                 numberOfChildren,
                 &children,
                 &clothing,
                 &childrenSeparators
                 );

    //update the RValue
    extern float rValue;
    extern float lowestDValue;
    for (int j =0; j < clothing.size(); j++){
        rValue += clothing.at(j)->value;
    }
    
    //make an array of negative values to represent
    //unused clothing items
    for (int i =0; i < clothing.size(); i++){
        AvailableClothes.push_back(-1);
    }

    //check to see if the slow
    //or the fast version of the
    //algorithm should be run
    int smallCount = 0;
    int mediumCount = 0;
    int largeCount = 0;
    int extralargeCount = 0;
    bool slowAlgorithm = false;
    
    for (int i = 0; i < clothingSize.size(); i++)
    {
        if (clothingSize.at(i) == 0)
            smallCount++;
        if (clothingSize.at(i) == 1)
            mediumCount++;
        if (clothingSize.at(i) == 2)
            largeCount++;
        if (clothingSize.at(i) == 3)
            extralargeCount++;
        if (clothingSize.at(i) == 4){
            smallCount++;
            extralargeCount++;
            largeCount++;
            mediumCount++;
        }
    }

    //if the calculation would completely fill the memory and still not be able to run, switch to the slower algorithm
    if ((48 * std::pow(2, smallCount) + 48 * std::pow(2, mediumCount) + 48 * std::pow(2, largeCount) + 48 * std::pow(2, extralargeCount)) > 100000000000){
        std::cout << "Calculation with pages would exceed 100 gb. Switching to slower algorithm to save memory." << std::endl;
        slowAlgorithm = true;
    }
    else if (switchOverride){
        std::cout << "Override Commandline Switch Engaged. Slower Algorithm Will Be Used." << std::endl;
        slowAlgorithm = true;
    }
    else {
        std::cout << "Calculation with pages will not exceed 100 gb. Switching to faster algorithm to increase performance." << std::endl;
    }

    if (slowAlgorithm){

        //start the slow variant of the algorithm
        startSlowAlgorithm(largestMultiple);

        //use slow writout function
        //(synonomous with the normal function
        //except it handles the values a bit differently)
        slowWriteOutFile(argv[2], &finalChains, lowestDValue, &originalChildrenNumbers, &originalClothingNumbers);

    }
    else{

        //now make the call to the itterative recursive function
        distributeClothing(&children,
                        &clothing,
                        &childrenClothingCombinations,
                        &childrenSeparators
                        );

        //start the quick variant of the algorithm
        startQuickAlgorithm(largestMultiple);

        //Do final d-Value Calculations
        calculateFinalDValues( &dValues,
                                &childrenClothingCombinations, 
                                &childrenSeparators, 
                                &AvailableClothes, 
                                &finalChains,
                                &clothing,
                                &children);

        //find the lowest D value and write out to file
        writeOutFile(argv[2], &finalChains, &childrenClothingCombinations, &dValues, &originalChildrenNumbers, &originalClothingNumbers);
    }

    return 0;
}