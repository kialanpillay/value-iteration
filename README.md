# Assignment Six: PLLKIA010

## Makefile
The purpose of the Makefile is to automatically compile and link the C++ source files into a binary executable that can be run locally. Run these commands in sequence to interact with the program.
```make``` will compile the files into an executable called ```driver```


```make run``` will run the executable and write the Value Iteration algorithm results to the file ```output.txt```.

## value_iteration.h

This is a header file that contains the ```ValueIteration``` Class declaration. This class contains several methods and data member variables necessary for the implementation of the Value Iteration algorithm. ```vector``` variables are used to hold key data pertaining to the states and actions possible in the environment and the optimal values and policies that are computed at each iteration of the algorithm. An ```unordered_map``` stores the reward function value, indexed by the transition between states. The start and terminal state are stored in ```string``` members. Integral variables that track the total number of iterations before convergence, and the discount factor utilised in the algorithm.


## value_iteration.cpp

This file is the actual implementation of the methods declared in the ```value_iteration.h``` file. The implementation of the methods is explained below. 

**runAlgorithm**: This method is complete implementation of the Value Iteration algorithm. For each state in the state space, the possible transitions are detirmined, and the expected value of the state is computed using the Bellman optimality equation, which is the max of the sum of the reward for that transition and the discounted value of the successor state. This is the update equation for the algorithm. In each iteration, the maximum value is calculated for each state. The value estimates are iteratively adjusted until the algorithm reaches convergence, returning the optimal values for each of the states in the state space


**testConvergence**: This method returns a ```bool``` dertirmined by the the ith iteration's optimal values being equal to the (i-1)th iteration's optimal values. The algorithm converges when these values no longer change within a pre-selected episilon degree.


**mapState/mapCoordinates**: This methods do not belong to the class, and are helper methods defined in the ```.cpp``` file that convert a state to its coordinates in the grid-world environment, and the reverese operation, respectively.


**Transition**: This is a functor that determines whether a transition between states in the environment is valid, given the coordinates of the two states, and the set of actions. The functor is applied to each element in the state space to obtain a ```vector``` of transitions. 


**computePolicy**: This method determines the argmax of the Bellman Optimality equation, once the algorithm has converged and the optimal values for each state are computed. This returns a the mappingfrom the state space to the action space, giving the optimal policy that the agent should follow to maximise the reward obtained when it reaches the goal state.


**getAction**: This method returns the action (```string```) executed by the agent, given the previous state  and state that it currently occupies.


**getStateIndex**: This method returns the index of the state in the state space ```vector```, given a currently occupied state and action executed by the agent. 


**writeResults**: This method writes the results of the algorithm: the total iterations and the actions and states comprising the optimal policy to the supplied ```ostream```. It also conducts an experiment to ascertain whether modifying the reward function produces different optimal values for each state after computation, but leaves the optimal policy intact. 

## driver.cpp

This file contains the main method, and provides an entry point into the program. It imports the ```value_iteration.h``` file in order to provide the requisite reinforcement learning functionality. The main method has a ```ValueIteration``` object, and uses the overloaded operator to write the results to the supplied ```ostream``` object.

