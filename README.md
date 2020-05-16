# Assignment Five: PLLKIA010

## Makefile
The purpose of the Makefile is to automatically compile and link the C++ source files into a binary executable that can be run locally. Run these commands in sequence to interact with the program.
```make``` will compile the files into an executable called ```driver```
\\
```make run``` will run the executable and write the PCA results to file.\\

## pca.h

This is a header file that contains the ```PCA``` Class declaration. This class contains two methods and several data member variables.
\\
These variables store the number of observations and variables in the dataset, a string containing the name of the dataset, and two ```MatrixXd``` variables to store the processed data, and the covariance matrix respectively.
\\
This header file also contains the method declaration for the overloaded operator, which returns a reference to the supplied ```ostream``` object.

## pca.cpp

This file is the actual implementation of the methods declared in the ```PCA.h``` file. The implementation of the methods is explained below. \\
The Constructor is responsible for initialising the object with a string containing the name of the dataset. There is also a default Constructor that takes no arguments.
\\
read: This method opens and extracts the data from the .txt file, and stores the values in an (M,N) ```MatrixXd``` object, where M is the number of observations and N is the dimensions of the dataset (2).
\\
compute: This method heavily relies upon the ```Eigen``` library for much of its functionality. The purpose of this method is to implement Principal Component Analysis on the 2018-AvgRainfall dataset. The mean of each of the constituent data variables is computed, and subtracted from the respective data-points. The covariance matrix is computed by multiplying the transpose of the adjusted data matrix with itself, divided by one minus the number of observations. Using the ```EigenSolver``` class, the eigenvalues and eigenvectors of the data are computed. These correspond to the two Principal Components. The total variance is found by summing the relevant entries in the covariance matrix, and the variance of each Principal Component is computed by dividing its Eigenvalue by the total variance. The above results are all written to the supplied ```ostream``` in response to the questions posed in this assignment.

## driver.cpp

This file contains the main method, and provides an entry point into the program. It imports the ```clusterer.h``` file in order to provide the PCA functionality. The main method has an ```PCA``` object, and uses the overloaded operator to write the results to the supplied ```ostream```.

