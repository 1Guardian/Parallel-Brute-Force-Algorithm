#ifndef GLOBALS_AND_MUTEX_H
#define GLOBALS_AND_MUTEX_H

#include <vector>
#include <string>
#include <unistd.h>
#include <iostream>
#include <cfloat>

/**********************************************************************************************************

extern globals

(This is their real definition)

Due to the nature of pthreads and how they are semi-unable to take data with them that
is outside of the semi-global scope, global variables was the best way to sustain functionality.
However, since they are globals and not structures or datatypes, they must be declared and accepted
only once and then referenced via extern by all other files, such as here.

**********************************************************************************************************/

//debug variable
int updater = 0;

//make children vector
std::vector<struct _child*> children;
pthread_mutex_t childrenMutex = PTHREAD_MUTEX_INITIALIZER;

//make the clothing vector
std::vector<struct _clothes*> clothing;
pthread_mutex_t clothingMutex = PTHREAD_MUTEX_INITIALIZER;

//struct used for keeping all possible combinations
//of children and clothing
std::vector<struct _child*> childrenClothingCombinations;

//vector to keep track of children number division boundaries
//will be the number of the first of the next set of children
std::vector<int> childrenSeparators;
pthread_mutex_t childSeparatorsMutex = PTHREAD_MUTEX_INITIALIZER;

//vector to keep track of the available clothing remaining
std::vector<int> AvailableClothes;
pthread_mutex_t AvailableClothesMutex = PTHREAD_MUTEX_INITIALIZER;

//random child chain for starting
std::vector<int> childChain;
pthread_mutex_t childChainMutex = PTHREAD_MUTEX_INITIALIZER;

//vector of a vector of ints to keep track of final chain possibilities
std::vector<std::vector<int>> finalChains;
pthread_mutex_t finalChainsMutex;

//vector to act as a queue for the threads to dispatch
//from
std::vector<struct _child*> startingChildrenClothingCombinations;
pthread_mutex_t startingChildrenClothingCombinationsMutex;

//float to store the lowest D-Value. This will let me terminate
//threads much quicker (hopefully). It is being kept in the mutex
//globals section because it will need a mutex to protect it.
float lowestDValue = FLT_MAX;
pthread_mutex_t lowestDValueMutex;

//this is an index counter
//to allow the slower algorithm
//to be multithreaded due to array
//casting issues
int slowAlgorithmIndex = 0;

//rValue
float rValue;

//number of children
int childNumber;

#endif