# Parallelization of Decision Trees
CS205: Computing Foundations for Computational Science
Harvard School of Engineering and Applied Sciences
Spring 2020
Team: Gabriel Pestre, Johannes Kolberg, Hardik Gupta, Will Seaton

### Summary
Supervised learning requires high computational costs and frequent training.

Identifying methods to speed up supervised learning will be a critical innovation path in coming years. A recent Stanford study quantified a new Moore's Law for AI by calculating that compute available for model training has been doubling every 3.4 months compared with every two years for processor development.[1](https://www.computerweekly.com/news/252475371/Stanford-University-finds-that-AI-is-outpacing-Moores-Law "Computer Weekly"). That same study said the time reduction to train ResNet image classification dropped from three hours in late 2017 to 88 seconds in mid-2019. Accelerating model training at all levels will unlock new capacity for data science and machine learning to help important problems or decrease necessary cost and time enough to provide greater access.

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
To run our Random Forest demonstration locally, please run the below commands in your Terminal.

// Clone our repository locally
$ git clone https://github.com/johannes-kk/cs205_final_project.git

// Navigate to Demo folder
$ cd cs205_final_project/demo/

// Compile the demo file
$ g++ -std=c++14 -O0 demo_rf_serial.cpp -o demo_rf_serial

// Run the executable
$ time ./demo_rf_serial

## Code Base Design
We built from the ground up C++ classes for data integration and manipulation. Since this was all of our first time implementing a project in C++, this allowed us to have greater control over parallelization options at every level. Our custom classes are located in datasets.hpp and include:
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

## OpenMP Parallelization
todo

## Cloud Infrastructure
We utilize an Amazon Web Service t2.2xlarge instance for our parallel implementation tests. todo

## Speed Up Achieved
todo@H

## Challenges
todo@J

## Future Work 
