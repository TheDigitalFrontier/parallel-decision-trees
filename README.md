# Decision Tree Parallelization
CS205: Computing Foundations for Computational Science
Harvard School of Engineering and Applied Sciences
Spring 2020
Team: Gabriel Pestre, Johannes Kolberg, Hardik Gupta, Will Seaton

### Summary
Supervised learning in today's high performance computing industry can require high computational costs and extended time during model training, prediction or elsewhere. Identifying methods to speed up supervised learning will be a critical innovation path in coming years. A recent Stanford study quantified a new Moore's Law for AI by calculating that compute available for model training has been doubling every 3.4 months compared with every two years for processor development.[1](https://www.computerweekly.com/news/252475371/Stanford-University-finds-that-AI-is-outpacing-Moores-Law "Computer Weekly"). That same study said the time reduction to train ResNet image classification dropped from three hours in late 2017 to 88 seconds in mid-2019. Accelerating model training at all levels will unlock new capacity for data science and machine learning to help important problems or decrease necessary cost and time enough to provide greater access.

To participate in this innovation, we wanted to assess the speed up possible by parallelizing various parts of some of today's most relied upon supervised learning models - decision trees and random forest. These models require....

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
- LossFunction: Enables loss calculation of types Misclassification, Cross Entropy, Gini and MSE. *File: losses.hpp.*
- LabelCounter: Utility to calculate occurrences in a label for classification *File: losses.hpp.*

All code can be found in the *src* or *src-openmp* folders depending on your desire for serial or parallel.

## OpenMP Parallelization
todo

## Cloud Infrastructure
We utilize an Amazon Web Service m5.4xlarge instance for our parallel implementation tests. Our instance was running Ubuntu Server 16.04 with 16 vCPUs, 64 GiB Memory and EBS Storage. We were able to leverage 2 threads per core and 8 cores for the single socket. The CPU was an Intel Xeon Platinum 8259CL with 2.5GHz, L2 cache of 1024K and L3 cache of 36608K.

## Speed Up Achieved
todo@H

## Challenges
todo@J

## Future Work 
