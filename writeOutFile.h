#ifndef WRITE_OUT_FILE_H
#define WRITE_OUT_FILE_H

#include <fstream>
#include <vector>
#include <sstream>

/**********************************************************************************************************

void writeOutFile(const char* outFile, 
                  std::vector<std::vector<int>>* finalChains,
                  std::vector<struct _child*>* childrenClothingCombinations,
                  std::vector<float>* dValues,
                  std::vector<std::string>* originalChildrenNumbers, 
                  std::vector<std::string>* originalClothingNumbers){
        
    This function  writes out to the supplied file name. 

**********************************************************************************************************/
void writeOutFile(const char* outFile, 
                  std::vector<std::vector<int>>* finalChains,
                  std::vector<struct _child*>* childrenClothingCombinations,
                  std::vector<float>* dValues,
                  std::vector<std::string>* originalChildrenNumbers, 
                  std::vector<std::string>* originalClothingNumbers);

#endif