#include <stdio.h>
#include <stdlib.h>
#include <vector>

//double accuracy_score(double* target, double* prediction){
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
double** derp(int column, double threshold){

}
*/


/*
Takes in a dataset and the column index number and threshold value
Returns two datasets: left is rows with that column's values < threshold
*/
std::vector<std::vector<std::vector<double>>> split_dataset(std::vector<std::vector<double>> dataset, int col_ind, double split_thresh){
    /*
    left, right = list(), list()
	for row in dataset:
		if row[index] < value:
			left.append(row)
		else:
			right.append(row)
	return left, right
    */
   printf("Step 1\n");
   std::vector<std::vector<double>> left, right;
   printf("Step 2\n");
   for (int i = 0; i < dataset.size(); i++)
   {
       if (dataset[i][col_ind] < split_thresh)
       {
           left[left.size()] = dataset[i];
       }
       else
       {
           right[right.size()] = dataset[i];
       }
   }
   printf("Step 3\n");
   std::vector<std::vector<std::vector<double>>> two_datasets = {left, right};
   printf("Step 4\n");
   return two_datasets;
}