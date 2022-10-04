#ifndef SLOW_WRITE_OUT_FILE_H
#define SLOW_WRITE_OUT_FILE_H

#include <fstream>
#include <vector>
#include <sstream>

/**********************************************************************************************************

void slowWriteOutFile(const char* outFile, 
                  std::vector<std::vector<int>>* finalChains,
                  float dValues,
                  std::vector<std::string>* originalChildrenNumbers, 
                  std::vector<std::string>* originalClothingNumbers)
        
    This function  writes out to the supplied file name from the slower algorithm. 

**********************************************************************************************************/
void slowWriteOutFile(const char* outFile, 
                  std::vector<std::vector<int>>* finalChains,
                  float dValues,
                  std::vector<std::string>* originalChildrenNumbers, 
                  std::vector<std::string>* originalClothingNumbers);

#endif