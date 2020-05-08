#include "losses.hpp"
#include "datasets.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <assert.h>

/**
 * Calculate classification accuracy of a DataVector of predictions compared to a DataVector of targets
 **/
double accuracy(DataVector targets, DataVector predictions){
    assert(targets.size() == predictions.size());
    int correct = 0;
    for (int i = 0; i < targets.size(); i++){
        if (targets.value(i) == predictions.value(i)){
            correct += 1;
        }
    }
    return (double)correct / targets.size();
}

