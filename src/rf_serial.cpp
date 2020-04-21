#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timing.h"

int main(int argc, char** argv){
    // argc is count of arguments provided
    // argv is array of arguments

    printf("Hello world\n");

    // get algorithm parameters
    int ntrees, mtry;

    ntrees = (argc > 0) ? atoi(argv[0]) : 5;
    mtry = (argc > 1) ? atoi(argv[1]) : 2;

    // contrived dataset for testing: (input1, input2, class)
    double dataset[10][3] = {
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

    printf("Done, mtry = %d, ntrees = %d\n", ntrees, mtry);

    printf("Row 0: %f\n", dataset[0][0]);
}

