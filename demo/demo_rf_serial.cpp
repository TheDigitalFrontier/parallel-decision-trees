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

    // Fit RF on full dataset and verify accuracy is high on seen data
    std::cout << "Build and fit RandomForest binary classifier on Sonar" << std::endl;

    // Use all default values (meaning no seed)
    RandomForest rf1 = RandomForest(df_sonar, ntree);

    std::cout << "RF1 accuracy full train: " << accuracy(df_sonar.col(-1), rf1.predict(&df_sonar)) << std::endl;
    
    // Create train and test data
    std::vector<DataFrame> train_and_test = df_sonar.train_test_split(0.2, 1337);
    DataFrame df_train = train_and_test[0];
    DataFrame df_test = train_and_test[1];

    // Fit RF on train and evalute on test, with lower accuracy
    RandomForest rf2 = RandomForest(df_train,ntree,false,"gini_impurity",-1,-1,-1,-1,-1,42);

    std::cout << "RF2 accuracy train: " << accuracy(df_train.col(-1), rf2.predict(&df_train)) << std::endl;
    std::cout << "RF2 accuracy test: " << accuracy(df_test.col(-1), rf2.predict(&df_test)) << std::endl;

    return 0;
};
