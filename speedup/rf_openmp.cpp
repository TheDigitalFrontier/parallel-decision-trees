#include <iostream>
#include "../src-openmp/datasets.cpp"
#include "../src-openmp/losses.cpp"
#include "../src-openmp/metrics.cpp"
#include "../src-openmp/tree_node.cpp"
#include "../src-openmp/decision_tree.cpp"
#include "../src-openmp/random_forest.cpp"

int main(){
    int ntree = 100;
    std::cout << "ntree: " << ntree << std::endl;
    
    DataLoader csv_loader = DataLoader("../data/sonar.all-data.numerical.csv");
    DataFrame df_sonar = csv_loader.load();

    // Create train and test data
    std::vector<DataFrame> train_and_test = df_sonar.train_test_split(0.2, 1337);
    DataFrame df_train = train_and_test[0];
    DataFrame df_test = train_and_test[1];

    // Fit RF on train and evalute on test, with lower accuracy
    RandomForest rf = RandomForest(df_train,ntree,false,"gini_impurity",-1,-1,-1,3,-1,69);

    std::cout << "Accuracy train: " << accuracy(df_train.col(-1), rf.predict(&df_train)) << std::endl;
    std::cout << "Accuracy test:  " << accuracy(df_test.col(-1), rf.predict(&df_test)) << std::endl;

    return 0;
};
