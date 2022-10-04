#include <fstream>
#include <vector>
#include <sstream>
#include <cmath> 
#include <algorithm> 
#include <iostream>
#include "dataStructures.h"

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
                  std::vector<std::string>* originalClothingNumbers){

    //make sure we actually got an answer
    if (finalChains->size() == 0){
        std::cout << "\n========================================================================================\nNo distribution for the clothing could be found. There is likely too few articles of clothes\nto distribute two to each child, with one being a summer item and one being a winter item.\n\nExiting now.\n========================================================================================\n\n";
        exit(-1);
    }

    //find minimum of DValues and print child-clothing combination that corresponds
    std::ofstream ofs(outFile, std::ifstream::out);
    
    for (int i =0; i < finalChains->size(); i++){
        ofs << originalChildrenNumbers->at(i) << "\t";
        for(int j = 0; j < finalChains->at(i).size(); j++)
            ofs << originalClothingNumbers->at(finalChains->at(i).at(j)) << "\t";
        ofs << std::endl;
    }

    ofs << "D\t" << dValues;

    return;
}