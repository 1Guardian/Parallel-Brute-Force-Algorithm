#Vars
CC=g++
CFLAGS=-I.
DEPS = globalsAndMutex.hpp dataStructures.h mutexLocks.h threadedFunctions.h calculateDValues.h distributeClothing.h takeInput.h slowThreadFunctions.h slowWriteOutFile.h startAlgorithms.h
OBJ = main.o mutexLocks.o takeInput.o threadFunctions.o calculateDValues.o distributeClothing.o writeOutFile.o slowThreadFunctions.o slowWriteOutFile.o startAlgorithms.o
BIN = clothing

#Make Target Object files w/ suffix rules
.cpp.o:
	$(CC) -g -std=c++11 -pthread -c -o $@ $< $(CFLAGS)

#making the bin
$(BIN): $(OBJ)
	$(CC) -g -std=c++11 -pthread -o $@ $^ $(CFLAGS)

#Quick make protocol
quick: 
	make clean && make && clear 

#Clean
clean: 
	rm $(OBJ) $(BIN)