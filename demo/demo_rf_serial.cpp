#include <iostream>
#include "../src/datasets.cpp"
#include "../src/losses.cpp"
#include "../src/metrics.cpp"
#include "../src/tree_node.cpp"
#include "../src/decision_tree.cpp"
#include "../src/random_forest.cpp"

int main(){
    int ntree = 10;

    std::cout << "Load SONAR dataset:" << std::endl;
    DataLoader csv_loader = DataLoader("../data/sonar.all-data.numerical.csv");
    DataFrame df_sonar = csv_loader.load();

    std::cout << "Rows: " << df_sonar.length() << ", Cols: " << df_sonar.width() << std::endl;

    // Extract targets
    DataVector targets = df_sonar.col(-1);
    std::cout << "Targets size: " << targets.size() << std::endl;
    std::cout << targets << std::endl;

    // Fit RF on full dataset and verify accuracy is high on seen data
    std::cout << "Build and fit RandomForest binary classifier on Sonar" << std::endl;

    RandomForest rf1 = RandomForest(df_sonar, ntree, false, "gini_impurity", -1, -1, -1, -1, -1, 1337);
    rf1.fit();

    std::cout << "Tree fitted:" << rf1.isFitted() << std::endl;

    DataVector preds = rf1.predict(&df_sonar);
    std::cout << "Predictions size: " << preds.size() << std::endl;


    //std::cout << "Accuracy on full training set: " << accuracy(targets, preds) << std::endl;
    
    /* std::cout << "Perform prediction on new data:" << std::endl;
    DataVector pred_regression = rf_regression.predict(&test_data);
    std::cout << pred_regression << std::endl; */

    return 0;
};
