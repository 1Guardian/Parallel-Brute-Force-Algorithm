#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <vector>
#include <string>

/**********************************************************************************************************

struct _firstIndices

This structure allows the threads to keep indices in order in the event
that I want the program to split any portion of the table into shared
partitions for the threads to work on in parallel. It is currently not used
but will likely be in the future.

**********************************************************************************************************/
struct _firstIndices {

    ///int for holding the starting index
    int startingIndex = -1;

    //int for holding the ending index
    int endingIndex = -1;

    //multiple for increasing each time
    int multiple = -1;

    //vector to test if this will stay alive
    std::vector<std::vector<int>> personalFinalChain;
};

/**********************************************************************************************************

struct _clothes

This structure contains all the information needed for a singular piece of clothing.
Together in vectors or arrays, they form the entire input set of clothing for the brute
force run.

**********************************************************************************************************/
struct _clothes {

    //clothing size
    //  s = 0
    //  m = 1
    //  l = 2
    // xl = 3
    //  a = 4
    int size = -1;

    //type of apparel
    // winter = 0
    // summer = 1
    int weather = -1;

    //value of item
    int value = -1;

    //clothing number in array 
    //(im lazy)
    int number = -1;

    //constructor
    _clothes(int arrayNumber, int inputSize, int inputWeather, int inputValue){
        size = inputSize;
        weather = inputWeather;
        value = inputValue;
        number = arrayNumber; 
    }
};

/**********************************************************************************************************

struct _childChain

This structure is used to keep track of the chains that are being made at any given time.
Once they make it through all depth levels in a given thread, they get submitted to the
"finalChains" structure for final processing and DValue calulations.

**********************************************************************************************************/
struct _childrenChain{

    //sentinel to control addition 
    bool success = true;

    //actual chained string for printing
    //(can be removed easily to reduce complexity)
    std::string chain = "";

    //total value found in this chain
    int totalValue = 0;

    //Dvalue total of chain
    float currentDValue = 0;

};

/**********************************************************************************************************

struct _child

This structure contains all the information needed for a singular child.
Together in vectors or arrays, they form the entire input set of children for the brute
force run.

**********************************************************************************************************/
struct _child {

    //number of child
    int childNumber = -1;

    //size of child
    //  s = 0
    //  m = 1
    //  l = 2
    // xl = 3
    int childSize = -1;

    //values to hold the children's clothes
    std::vector<int> clothing;

    //total Value of clothing
    int totalValue = 0;

    //a quick patch to make determining the child
    //position much easier
    long childPosition = -1;

    //constructor
    _child(int number, int inputSize){
        childNumber = number;
        childSize = inputSize;
    }

};

#endif