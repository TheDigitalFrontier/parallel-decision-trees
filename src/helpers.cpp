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