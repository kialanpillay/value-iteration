# Assignment Six: PLLKIA010

## Makefile
The purpose of the Makefile is to automatically compile and link the C++ source files into a binary executable that can be run locally. Run these commands in sequence to interact with the program.
```make``` will compile the files into an executable called ```driver```
\\
```make run``` will run the executable and write the Value Iteration algorithm results to file.\\

## value_iteration.h

This is a header file that contains the ```ValueIteration``` Class declaration. This class contains two methods and several data member variables.
\\

## value_iteration.cpp

This file is the actual implementation of the methods declared in the ```value_iteration.h``` file. The implementation of the methods is explained below. \\

## driver.cpp

This file contains the main method, and provides an entry point into the program. It imports the ```value_iteration.h``` file in order to provide the requisite reinforcement learning functionality. The main method has a ```ValueIteration``` object, and uses the overloaded operator to write the results to the supplied ```ostream```.

