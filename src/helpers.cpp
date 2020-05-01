#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <random>
#include <ctime>

// todo use namespace across the board, since many functions?
// using namespace std;

// Data type aliasing
using dataframe = std::vector<std::vector<double>>;
using datavec = std::vector<double>;

/*
Calculate the accuracy in percent of a vector of predictions compared to a vector of targets
*/
//double accuracy_score(std::vector<double> targets, std::vector<double> predictions){
double accuracy_score(datavec targets, datavec predictions){
    // todo: verify that target and predict have same size

    double correct = 0;
    for (int i = 0; i < targets.size(); i++){
        if (targets[i] == predictions[i]){
            correct += 1;
        } 
    }
    return correct/targets.size();
}

/*
Takes in a dataset and the column index number and threshold value
Returns two datasets: left is rows with that column's values < threshold
*/
//std::vector<std::vector<std::vector<double>>> split_dataset(std::vector<std::vector<double>> dataset, int col_ind, double split_thresh){ 
std::vector<dataframe> split_dataset(dataframe data, int col_ind, double split_thresh){ 
   dataframe left, right;
   for (int i = 0; i < data.size(); i++){
       // TODO Use <=, not <, so lowest observed col val as thresh yields non-empty df ???
       if (data[i][col_ind] < split_thresh){
           left.push_back(data[i]);
       }else{
           right.push_back(data[i]);
       }
   }
   std::vector<dataframe> two_datasets = {left, right};
   return two_datasets;
}

/*
Extract column of dataframe as a datavec. No native way in C++ to do so, as 2D array is really stored in memory as a 1D array.

C++ is finicky with negative indexing, and those don't work like in Python.
Hence, hardcoded so passing a negative index behaves as expected
*/
datavec get_column(dataframe data, int column_id){
    datavec data_column;
    // Check whether dataframe is empty, if so return empty datavec
    if (data.size() == 0){
        return data_column;
    }
    // Check whether negative index, if so ensure expected (from Python) behaviour
    int ind;
    if (column_id < 0){
        ind = data[0].size() + column_id;
    }else{
        ind = column_id;
    }
    // Create vector of column values
    for (int i = 0; i < data.size(); i++){
        data_column.push_back(data[i][ind]);
    }
    return data_column;
}

/* 
TODO: change to take as parameter std::vector<dataframe>, i.e. same as output of split_dataset, to calculate Gini score between an arbitrary number of dataframes
*/
double gini_index(dataframe data1, dataframe data2){
    double gini = 0.0;
    // Get class labels in the two dataframes (by convention last column)
    datavec class1 = get_column(data1, -1);
    datavec class2 = get_column(data2, -1);
    // Combine the two vectors of class labels
    datavec classes = class1;
    classes.insert(classes.end(), class2.begin(), class2.end());
    // Find unique class labels
    sort(classes.begin(), classes.end());
    classes.erase(unique(classes.begin(), classes.end()), classes.end());
    // for each class in set of unique class labels, calculate proportion and add to Gini
    double prop;
    for(double&cur_class: classes){
        // If class1 is not empty, iterate through it (perfect split means one df empty)
        if (class1.size() > 0){
            prop = double(std::count(class1.begin(), class1.end(), cur_class)) / class1.size();
            gini += (prop * (1.0 - prop));
        }
        if (class2.size() > 0){
            prop = double(std::count(class2.begin(), class2.end(), cur_class)) / class2.size();
            gini += (prop * (1 - prop));
        }
    }
    return gini;
}

/* 
Find the best split of a provided dataset, using a given scoring algorithm
Scoring algorithm must return type double and take two dataframes as parameters
As always, assumes last column is class labels
If no mtry provided, uses default of mtry equal to square root of number of columns
*/
datavec best_split(dataframe dataset, int mtry = 0, double (*scoring_function)(dataframe, dataframe) = gini_index){
    int num_cols = int(dataset[0].size())-1;
    // pre-allocate vector of column indices
    std::vector<int> shuf_inds(num_cols);
    // Create vector of column indices, equivalent to np.arange(0, df.shape[-1])
    std::generate(shuf_inds.begin(), shuf_inds.end(), [n = 0] () mutable { return n++; });
    // Set changing random generator (arrow of time is inexorable!)
    srand((unsigned) time(0));
    // Shuffle it
    for (int i = 0; i < num_cols; i++){
        std::swap(shuf_inds[i], shuf_inds[i+(std::rand() % (num_cols-i))]);
    }
    // Get number of columns to sample from
    if (mtry == 0){
        mtry = int(floor(sqrt(num_cols)));
    }else{
        mtry = int(std::min(mtry, num_cols));
    }
    // Iterate first mtry of shuffled cols
    double best_ind, best_val, best_score, score = -1.0;
    for (int i = 0; i < mtry; i++){
        // Extract all values of column in data to try all thresholds
        datavec col_vals = get_column(dataset, shuf_inds[i]);
        // Remove duplicates
        sort(col_vals.begin(), col_vals.end());
        col_vals.erase(unique(col_vals.begin(), col_vals.end()), col_vals.end());
        // For each unique column value, try that col and val as split, get score
        for (double&val: col_vals){
            // Split dataset using current column and threshold, score, and update if best
            std::vector<dataframe> dataset_splits = split_dataset(dataset, shuf_inds[i], val);
            score = scoring_function(dataset_splits[0], dataset_splits[1]);
            if (score > best_score){
                best_ind = shuf_inds[i];
                best_val = val;
                best_score = score;
            }
        }
    }
    // TODO raise error if best_ind, best_val etc. have not been updated from -1
    return datavec {best_ind, best_val, best_score};
}
