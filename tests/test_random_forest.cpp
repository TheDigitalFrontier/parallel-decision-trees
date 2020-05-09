#include <iostream>
#include "../src/datasets.cpp"
#include "../src/losses.cpp"
#include "../src/tree_node.cpp"
#include "../src/decision_tree.cpp"
#include "../src/random_forest.cpp"


int main(){

    int num_trees = 10;

    std::cout << "Define training data:" << std::endl;
    DataFrame training_data = DataFrame({
        {2.232, 2.456, 2.000, 0},
        {2.232, 2.456, 3.000, 1},
        {2.277, 8.735, 3.000, 2},
        {2.965, 6.846, 3.000, 2},
        {2.252, 6.452, 3.000, 2},
        {2.222, 9.944, 3.000, 2},
        {2.322, 8.747, 3.000, 2},
        {2.322, 7.667, 3.000, 2},
        {6.201, 6.342, 3.000, 3},
        {6.201, 7.442, 3.000, 3},
        {7.403, 9.944, 3.000, 3},
        {8.720, 8.747, 3.000, 3},
        {6.804, 9.941, 3.000, 3},
        {6.201, 9.452, 3.000, 3},
        {8.403, 3.944, 3.000, 4},
        {8.403, 3.944, 4.000, 5},
    });
    training_data.print();

    std::cout << "Define test data:" << std::endl;
    DataFrame test_data = DataFrame({
        {2.0, 0.0, 3.0},  // Expected: 1.
        {2.0, 1.0, 3.0},  // Expected: 1.
        {2.0, 2.0, 3.0},  // Expected: 1.
        {2.0, 7.0, 3.0},  // Expected: 2.
        {2.0, 8.0, 3.0},  // Expected: 2.
        {2.0, 9.0, 3.0},  // Expected: 2.
        {7.0, 7.0, 3.0},  // Expected: 3.
        {7.0, 8.0, 3.0},  // Expected: 3.
        {7.0, 9.0, 3.0},  // Expected: 3.
        {7.0, 1.0, 3.0},  // Expected: 4.
        {7.0, 2.0, 3.0},  // Expected: 4.
    });
    test_data.print();
    
    std::cout << "Build and train RandomForest for classification." << std::endl;
    RandomForest rf_classification = RandomForest(training_data,num_trees,false,"gini_impurity",-1,-1,-1,-1,-1);
    
    std::cout << "Perform prediction on new data:" << std::endl;
    DataVector pred_classification = rf_classification.predict(&test_data);
    std::cout << pred_classification << std::endl;
    
    std::cout << "Build and train RandomForest for regression." << std::endl;
    RandomForest rf_regression = RandomForest(training_data,num_trees,true,"mean_squared_error",-1,-1,-1,-1,-1);
    
    std::cout << "Perform prediction on new data:" << std::endl;
    DataVector pred_regression = rf_regression.predict(&test_data);
    std::cout << pred_regression << std::endl;

    return 0;
};
