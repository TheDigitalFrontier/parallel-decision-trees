#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <array>
#include <vector>
#include "timing.h"
#include "timing.c"

#include "helpers.cpp"
// includes data type aliases "dataframe" and "datavec"

int main(int argc, char** argv){
    // argc is count of arguments provided
    // argv is array of arguments
    int ntrees, mtry;
    timing_t tstart, tend;

    printf("Starting...\n");
    // record starting time in tstart
    get_time(&tstart);

    // get parameters if specified, otherwise use defaults
    ntrees = (argc > 1) ? atoi(argv[1]) : 5;
    mtry = (argc > 2) ? atoi(argv[2]) : 2;
    printf("ntrees = %d, mtry = %d\n", ntrees, mtry);

    // contrived dataset for testing: (input1, input2, class)
    // https://www.geeksforgeeks.org/multidimensional-arrays-c-cpp/
    //double dataset[10][3] = {
    //std::array<std::array<double, 3>, 10> dataset = {{
    //https://en.cppreference.com/w/cpp/container/vector 
    
    dataframe contrived_data = {
    //std::vector<std::vector<double>> contrived_data = {
        {2.7810836,2.550537003,0}, 
        {1.465489372,2.362125076,0}, 
        {3.396561688,4.400293529,0}, 
        {1.38807019,1.850220317,0}, 
        {3.06407232,3.005305973,0}, 
        {7.627531214,2.759262235,1}, 
        {5.332441248,2.088626775,1}, 
        {6.922596716,1.77106367,1}, 
        {8.675418651,-0.242068655,1}, 
        {7.673756466,3.508563011,1}
    };

    printf("Rows: %lu\n", contrived_data.size());
    printf("Cols: %lu\n", contrived_data[0].size());

    /* ---------- BEGIN ---------- */
    // UNIT TEST contrived dataset works as intended
    // should print 4.400293529
    printf("Row 3, Col 2: %f\n\n", contrived_data[2][1]);

    // UNIT TEST accuracy scoring from helpers.cpp
    //std::vector<double> tar = {0, 1, 1, 0, 0};
    datavec tar {0, 1, 1, 0, 0};
    // should print 5/5 == 1.0:
    std::vector<double> pred1 = {0, 1, 1, 0, 0};
    printf("Accuracy pred1: %f\n", accuracy_score(tar, pred1));
    // should print 3/5 = =0.6:
    std::vector<double> pred2 = {0, 0, 1, 1, 0};
    printf("Accuracy pred2: %f\n\n", accuracy_score(tar, pred2));

    // UNIT TEST split_dataset from helpers.cpp
    int split_col = 0;
    double split_thresh = 3.1;
    printf("Splitting contrived dataset on column %d threshold %f\n", split_col, split_thresh);
    //std::vector<std::vector<std::vector<double>>> dataset_splits = split_dataset(contrived_data, split_col, split_thresh);
    std::vector<dataframe> dataset_splits = split_dataset(contrived_data, split_col, split_thresh);
    dataframe left = dataset_splits[0];
    dataframe right = dataset_splits[1];
    printf("Left set %lu rows, right set %lu rows\n\n", left.size(), right.size());

    /* ---------- WRAP UP ---------- */
    // record end time
    get_time(&tend);
    // print results
    printf("Done in %Lg s\n", timespec_diff(tstart, tend));
}

