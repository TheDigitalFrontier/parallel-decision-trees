# Decision Tree Parallelization
#### CS205: Computing Foundations for Computational Science
Harvard School of Engineering and Applied Sciences
Spring 2020
**Team**: Gabriel Pestre, Johannes Kolberg, Hardik Gupta, Will Seaton

### Summary
Supervised learning in today's high performance computing industry can require high computational costs and extended time during model training, prediction or elsewhere. Identifying methods to speed up supervised learning will be a critical innovation path in coming years. A recent Stanford study quantified a new Moore's Law for AI by calculating that compute available for model training has been doubling every 3.4 months compared with every two years for processor development.[1](https://www.computerweekly.com/news/252475371/Stanford-University-finds-that-AI-is-outpacing-Moores-Law "Computer Weekly"). That same study said the time reduction to train ResNet image classification dropped from three hours in late 2017 to 88 seconds in mid-2019. Accelerating model training at all levels will unlock new capacity for data science and machine learning to help important problems or decrease necessary cost and time enough to provide greater access.

To participate in this innovation, we wanted to assess the speed up possible by parallelizing various parts of some of today's most relied upon supervised learning models - decision trees and random forest. Because of the nature of these models, there are various places where parallelization can be applied for potential speed up. These locations include training, loss calculation, pruning, prediction and tuning.

## Project Structure
Our parallel implementation of random forest can be found in this repository.
- **src**: Source code for C++ serial implementation
- **src-openmp**: Source code for C++ and OpenMP parallel imnplementation
- **data**: Contains multiple sized datasets for demos
- **tests**: Contains our unit-test files
- **demo**: Contains our primary Random Forest demo
- **bin**: Contains compilation script
- **speedup**: Contains performance and plotting scripts

## How to Run Demo
To run our Random Forest demonstration locally, please run the below commands in your Terminal. Please ensure you are using a version of C++ compatible with c++14.

// Clone our repository locally

$ git clone https://github.com/johannes-kk/cs205_final_project.git

// Navigate to Demo folder

$ cd cs205_final_project/demo/

// Compile the demo file

$ g++ -std=c++14 -O0 demo_rf_serial.cpp -o demo_rf_serial

// Run the executable

$ time ./demo_rf_serial

Expected Output:

![alt text](https://github.com/johannes-kk/cs205_final_project/blob/readme/demo/RF_Serial_Demo.png "Output Preview")

## Code Base Design
We built from the ground up C++ classes for data integration and manipulation. Since this was all of our first time implementing a project in C/C++, this allowed us to have greater control over parallelization options at every level. Our custom classes are located in datasets.hpp and include:
- DataVectors: Represents an individual row or column as a <vector>
- DataFrames: Represents tabular data and associated interactions
- DataLoaders: Utility to build Data Frames from imported files
- SeedGenerators: Utility to generate pseudorandom seed numbers for standard sampling

Our models are comprised of three custom C++ classes representing model logic and two classes representing accuracy and loss calculations used during model training. Each class within a model's architecture as its own file. The classes and files include:
- TreeNode: Represents a single node in a Decision Tree. *File: tree_node.hpp.*
- DecisionTree: Represents a standard Decision Tree. Constructed to allow regression or classification. *File: decision_tree.hpp.*
- RandomForest: Represents a Random Forest model. *File: random_forest.hpp.*
- LossFunction: Enables loss calculation of various provided types. *File: losses.hpp.*
- LabelCounter: Utility to calculate occurrences in a label for classification *File: losses.hpp.*

We needed to write extensive methods from scratch to create a basic working version of a Decision Tree or Random Forest. The most important of these methods are written below:
- calculateLoss(): Calculates loss before split
- calculateSplitLoss(): Calculates loss on split dataset using weighted average of loss in each split
- findBestSplit(): Finds best split location for values of every column
- fit(): Fits decision tree to provided dataframe
- predict(): Predicts new values from provided test vector
- print(): Returns tree as string to std::cout

We provide loss and accuracy calculation options of five types for various model types. These types include:
- Misclassification Error
- Cross Entropy
- Gini Impurity
- Mean Squared Error
- Classification Accuracy

All code can be found in the *src* or *src-openmp* folders depending on your desire for serial or parallel.i

## Dependencies
We relied on several core C++ packages during our development. These packages include:
- <assert.h>
- <math.h>
- <cmath>
- <iostream>
- <fstream>
- <sstream>
- <iomanip>
- <vector>
- <random>
- <algorithm>
- <string>

## OpenMP Parallelization
We experimented with parallelizing several of the previously listed opportunities and the greatest speed up was achieved in three locations.

First, in the findBestSplit() function of the DecisionTree class, OpenMP was able to parallelize the identification and testing of split values for each column to more quickly identify the best split loss and subsequent split decision.

Second, in the predict() function of DecisionTree, OpenMP was able to parallelize the creation of a prediction for every row value such that the full set of predictions could be made much faster.

Third, in the fit() function of RandomForest, OpenMP was able to parallelize the creation of a random subsample of trees and branches so the model could learn multiple random fits at once.

## Cloud Infrastructure
We utilize an Amazon Web Service m5.4xlarge instance for our parallel implementation tests. Our instance was running Ubuntu Server 16.04 with 16 vCPUs, 64 GiB Memory and EBS Storage. We were able to leverage 2 threads per core and 8 cores for the single socket. The CPU was an Intel Xeon Platinum 8259CL with 2.5GHz, L2 cache of 1024K and L3 cache of 36608K.

## Speed Up Achieved
On our SONAR dataset, we see continually increasing speed-up on the order of 4-10x the greater the number of nodes. Above 100 trees, the speed up gains become minimal. For HMEQ, we see a first positive, then negative trend. Going from 10 to 50 trees, sees an increase from 6x to 8-9x speedup. But going from 50 trees to 100 or more begins to slow down the speed up achieved. 100 trees is limited to 4x speed up and 500 trees shows a speed *down* at 2 and 4 nodes before matching serial parity at 6 and 16 nodes. This suggests that for HMEQ, coordination costs are greater than efficiency gains until we get more computational power from more nodes.

![alt text](https://github.com/johannes-kk/cs205_final_project/blob/readme/speedup/SpeedUp_OpenMP.png "OpenMP Achieved Speed Up")

## Challenges
todo@J

## Future Work
