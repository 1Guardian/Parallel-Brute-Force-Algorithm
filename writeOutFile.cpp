#include <fstream>
#include <vector>
#include <sstream>
#include <cmath> 
#include <algorithm> 
#include <iostream>
#include "dataStructures.h"

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
                  std::vector<std::string>* originalClothingNumbers){

    //make sure we actually got an answer
    if (finalChains->size() == 0){
        std::cout << "\n========================================================================================\nNo distribution for the clothing could be found. There is likely too few articles of clothes\nto distribute two to each child, with one being a summer item and one being a winter item.\n\nExiting now.\n========================================================================================\n\n";
        exit(-1);
    }

    //find minimum of DValues and print child-clothing combination that corresponds
    std::ofstream ofs(outFile, std::ifstream::out);
    auto it = std::min_element(std::begin(*dValues), std::end(*dValues));
    int indexOfMinimumDValue = std::distance(std::begin(*dValues), it);
    
    for (int i =0; i < finalChains->at(indexOfMinimumDValue).size(); i++){
        ofs << originalChildrenNumbers->at(i) << "\t";
        for(int j = 0; j < childrenClothingCombinations->at(finalChains->at(indexOfMinimumDValue)[i])->clothing.size(); j++)
            ofs << originalClothingNumbers->at(childrenClothingCombinations->at(finalChains->at(indexOfMinimumDValue)[i])->clothing[j]) << "\t";
        ofs << std::endl;
    }

    ofs << "D\t" << dValues->at(indexOfMinimumDValue);

    return;
}