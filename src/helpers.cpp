#include <stdio.h>
#include <stdlib.h>
#include <vector>

/*
Calculate the accuracy in percent of a vector of predictions compared to a vector of targets
*/
double accuracy_score(std::vector<double> targets, std::vector<double> predictions){
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
std::vector<std::vector<std::vector<double>>> split_dataset(std::vector<std::vector<double>> dataset, int col_ind, double split_thresh){ 
   std::vector<std::vector<double>> left, right;
   for (int i = 0; i < dataset.size(); i++)
   {
       if (dataset[i][col_ind] < split_thresh)
       {
           left.push_back(dataset[i]);
       }
       else
       {
           right.push_back(dataset[i]);
       }
   }
   std::vector<std::vector<std::vector<double>>> two_datasets = {left, right};
   return two_datasets;
}