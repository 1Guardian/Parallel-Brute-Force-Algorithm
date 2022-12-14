### Quick explanation:
  This project was for my advanced algorithms class, and required finding an optimal solution to an arbitrary problem without using an efficient algorithm.
  The goal was to use parallelization and multithreading as efficiently as possible to achieve the answer in the smallest time possible.

## IMPORTANT NOTES

- This program contains 2 algorithms inside of it. They both achieve the same end goal, but
the first algorithm uses memoization to create distribution combinations and then allows threads
to access these distributions to attempt to do the calculations faster and in parallel. However, when
the algorithm detects that the calculation would fill over 100 gb of ram with memoized pages, it will
switch to the slower algorithm. This algorithm is the same as the faster algorithm, but it uses no
memoization, thus making it much slower since each thread is calculating all combinations it will need.

Switch option: There is a way to force the slower algorithm to run, no matter what the input file and regardless
of whether or not the program will use more than 100gb of ram in memoization. To do this, just append the word
"slow" to the end of the command:

Example:
./clothing input.txt output.txt slow

This will enable you to run the program using only the slow algorithm, which will enable you to validate its 
answers without having to wait for the completion time of the algorithms it would likely be engaged on.
(in the example inputs, this seems to be the inputs where there is more than 50 items of clothing)

# PARALLELIZATION AND MEMORY USAGE

- This program is designed to run with multiple threads in parallel, and as such it will scan the 
host machine and create as many threads as the host system has. However, due to many clusters limiting
thread usage, you will need to run a Slurm script to grant the program more than 1 core. However, 
the program can't see how many cores have been allocated to it, so it will always create as many threads
as the cpu has threads, so if it is forced to run on one core, it will still create 24 threads and run
them all on one core. 

- The memory usage is the entire reason that the above dual algorithm system was created. Once again the program
will only look to see if the calculation will use more than 100gb of ram. Anything under that, and the
program will proceed with the fast algorithm. To change this, engaging the slow mode with the above 
mentioned word "slow" being appended to the end of the command.

# Clothing Distribution Program Overview

The program takes in a file consisting of a list of children with their corresponding sizes
and a list of clothing with their values and sizes and weather conditions as well. The goal is to 
distribute the clothing to the children as fair as possible. It will return a D-value corresponding
to what the most fair distribution is.

inputfile: file to be used for the distribution

outputfile: file to dump the answers into (overwrites file)

forceslowswitch: OPTIONAL SWITCH - this switch forces my program to stop using memoization and calculate
                                   all combinations from scratch each time. This switch exists to allow 
                                   you to test the slower method on smaller inputs to validate it. The value
                                   it needs to force the algorithm to switch is "slow"

./clothing inputfile outputfile slow


## Getting Started (Compiling)

To compile both the driver program and the Logger library, simple use of 'make'
will compile both for your use. 'make clean' will remove the created object files and the
executable binary that was compiled using the object files

## Impossible Conditions
The program also checks to ensure that the input set is actually possible (eg. it just checks to see 
that at the very least there are two times the number of children clothing items available), if it is
not, it will print a message indicating that fact and exit. If the calculation runs completely, and there
are no sets found, then a similar message will appear and indicate that the issue is likely that there
was enough clothing, but not enough summer and winter distribution to actually grant a winter and summer
item to each child, and thus no fair distribution could be found.
