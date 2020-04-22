#include <stdio.h>
#include <stdlib.h>
#include <vector>

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
   for (int i = 0; i < data.size(); i++)
   {
       if (data[i][col_ind] < split_thresh)
       {
           left.push_back(data[i]);
       }
       else
       {
           right.push_back(data[i]);
       }
   }
   std::vector<dataframe> two_datasets = {left, right};
   return two_datasets;
}

/*
Extract column of dataframe as a datavec. No native way in C++ to do so, as 2D array is really stored in memory as a 1D array.
Indexing supports actual index or -2 for last column (class, by convention)
*/
datavec get_column(dataframe data, int column_id){
    datavec data_column;
    for (int i = 0; i < data.size(); i++)
    {
        data_column.push_back(data[i][column_id]);
    }
    return data_column;
}

/* 

*/
double gini_index(dataframe data1, dataframe data2){
    double gini = 0.0;
    datavec class1, class2;

    return gini;
}