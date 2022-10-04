#include "takeInput.h"
#include "dataStructures.h"
#include <iostream>

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
                  ){

    //read in from file
    //FIXME: USE REAL FILE INPUT METHOD LATER
    //LINK FOR REFERENCE MATERIAL: https://en.cppreference.com/w/cpp/string/basic_string/getline
    //                             https://cplusplus.com/reference/fstream/ifstream/ifstream/
    std::ifstream ifs(inFile, std::ifstream::in);
    std::string temp;
    std::string fullFile = "";

    //Get each line from file one at a time
    while(std::getline(ifs, temp, '\r')) {
      fullFile += temp;
    }

    //you know the drill, into a string stream it goes
    std::stringstream ss(fullFile);

    std::vector<std::string> words;
    while (ss >> temp) {
        words.push_back(temp);
    }

    //now convert this into what the arrays used to look like
    int i = 1;
    int childBreak = 100000;
    while (i < words.size()){
        
        //check to see if we have transitioned to the children section yet
        if (words.at(i) == "Children"){
            childBreak = i;
            i++;
        }

        //check if we are in the child section yet and enter into child array if we are
        if(i > childBreak){

            //enter the children's original numbers
            originalChildrenNumbers->push_back(words[i]);

            //enter the children sizes
            if (words[i+1] == "S")
                childrenSize->push_back(0);
            else if (words[i+1] == "M")
                childrenSize->push_back(1);
            else if (words[i+1] == "L")
                childrenSize->push_back(2);
            else if (words[i+1] == "XL")
                childrenSize->push_back(3);
            i += 2;
        }

        //enter the clothes into 3 arrays for data transformation later
        else {

            //enter the clothing's original numbers
            originalClothingNumbers->push_back(words[i]);

            //enter the sizes first
            if (words[i+1] == "S")
                clothingSize->push_back(0);
            else if (words[i+1] == "M")
                clothingSize->push_back(1);
            else if (words[i+1] == "L")
                clothingSize->push_back(2);
            else if (words[i+1] == "XL")
                clothingSize->push_back(3);
            else if (words[i+1] == "A")
                clothingSize->push_back(4);
            else if (words[i+1] == "ALL")
                clothingSize->push_back(4);
            
            //enter the weather type now
            if (words[i+2] == "summer")
                clothingSeasons->push_back(1);
            else if (words[i+2] == "winter")
                clothingSeasons->push_back(0);

            //enter the price now 
            clothingPrice->push_back(std::stoi(words[i+3]));

            i += 4;
        }
    }

    if (clothingPrice->size()/2 < childrenSize->size()){
        std::cout << "\n========================================================================================\nToo few clothes to ensure that all children get at least a summer and winter item.\n\nExiting now.\n========================================================================================\n\n";
        exit(-1);
    }

    if (childrenSize->size() == 0){
        std::cout << "\n========================================================================================\nNo children were found in target file.\n\nExiting now.\n========================================================================================\n\n";
        exit(-1);
    }

    return;
}

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
                 ){

    //add the clothes to new clothes array    
    for(int i = 0; i < numberOfClothes; i++){

        clothing->push_back(new _clothes(i, clothingSize[i], clothingSeasons[i], clothingPrice[i]));

    }

    //add the children to children array
    for(int i = 0; i < numberOfChildren; i++){

        children->push_back(new _child(i, childrenSize[i]));

    }

    return;
}