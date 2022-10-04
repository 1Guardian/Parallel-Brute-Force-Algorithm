#ifndef TAKE_INPUT_H
#define TAKE_INPUT_H

#include <fstream>
#include <vector>
#include <sstream>

/**********************************************************************************************************

void takeInInput(std::vector<int>* clothingSize, 
                  std::vector<int>* clothingPrice, 
                  std::vector<int>* clothingSeasons, 
                  std::vector<int>* childrenSize,
                  std::vector<std::string>* originalChildrenNumbers, 
                  std::vector<std::string>* originalClothingNumbers){
        
    This function opens the target file and converts the input found within into a
    useable format for the program to begin divying up the input into various 
    vectors and threads.

**********************************************************************************************************/
void takeInInput(const char* inFile, 
                  std::vector<int>* clothingSize, 
                  std::vector<int>* clothingPrice, 
                  std::vector<int>* clothingSeasons, 
                  std::vector<int>* childrenSize,
                  std::vector<std::string>* originalChildrenNumbers, 
                  std::vector<std::string>* originalClothingNumbers
                  );

/**********************************************************************************************************

void convertData(int clothingSize[], 
                 int clothingPrice[], 
                 int clothingSeasons[], 
                 int childrenSize[], 
                 int numberOfClothes,
                 int numberOfChildren,
                 std::vector<struct _child*>* children,
                 std::vector<struct _clothes*>* clothing,
                 std::vector<int>* childrenSeparators
                 ){
        
    This function takes the input that is gleaned from the function that reads in
    from the supplied file and converts it into vectors so that my program can
    successfully use the data in the brute force run.

**********************************************************************************************************/
void convertData(int clothingSize[], 
                 int clothingPrice[], 
                 int clothingSeasons[], 
                 int childrenSize[], 
                 int numberOfClothes,
                 int numberOfChildren,
                 std::vector<struct _child*>* children,
                 std::vector<struct _clothes*>* clothing,
                 std::vector<int>* childrenSeparators
                 );

#endif