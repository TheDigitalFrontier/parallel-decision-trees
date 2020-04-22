#include <stdio.h>
#include <stdlib.h>
#include <vector>

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
    for (int i = 0; i < targets.size(); i++)
    {
        if (targets[i] == predictions[i])
        {
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
       if (data[i][col_ind] < split_thresh){
           left.push_back(data[i]);
       }
       else{
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
    // Check whether negative index, if so ensure expected (from Python) behaviour
    int ind;
    if (column_id < 0){
        ind = data[0].size() + column_id;
    }
    else{
        ind = column_id;
    }
    // Create vector of column values
    datavec data_column;
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
    std::vector<double> classes = class1;
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
