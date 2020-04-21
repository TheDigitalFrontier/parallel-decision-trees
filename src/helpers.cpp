#include <stdio.h>
#include <stdlib.h>
#include <vector>

//double accuracy_score(double* target, double* prediction){
double accuracy_score(std::vector<double> targets, std::vector<double> predictions){
    // todo: verify that target and predict have same size

    int correct = 0;
    for (int i = 0; i < targets.size(); i++)
    {
        if (targets[i] == predictions[i])
        {
            correct += 1;
        }
        
    }
    return double(correct/targets.size());
}
