#include <iostream>
#include "../src/datasets.cpp"
#include "../src/losses.cpp"
#include "../src/metrics.cpp"
#include "../src/tree_node.cpp"
#include "../src/decision_tree.cpp"
#include "../src/random_forest.cpp"

int main(){
    int ntree = 100;
    std::cout << "ntree: " << ntree << std::endl;
    
    DataLoader csv_loader = DataLoader("../data/hmeq_clean.csv");
    DataFrame df_csv = csv_loader.load();

    // Create train and test data
    std::vector<DataFrame> train_and_test = df_csv.train_test_split(0.2, 1337);
    DataFrame df_train = train_and_test[0];
    DataFrame df_test = train_and_test[1];

    // Fit RF on train and evalute on test, with lower accuracy
    RandomForest rf2 = RandomForest(df_train,ntree,false,"gini_impurity",-1,-1,-1,3,-1,42);

    std::cout << "Accuracy train: " << accuracy(df_train.col(-1), rf2.predict(&df_train)) << std::endl;
    std::cout << "Accuracy test:  " << accuracy(df_test.col(-1), rf2.predict(&df_test)) << std::endl;

    return 0;
};
