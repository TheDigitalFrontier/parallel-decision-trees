#include <iostream>
#include "../src/tree_node.cpp"
#include "../src/decision_tree.cpp"
#include "../src/datasets.cpp"
#include "../src/losses.cpp"

int main(){

    std::cout << "Loading test dataset." << std::endl;
    //DataLoader training_loader = DataLoader();
    //DataFrame training_data = training_loader.load();
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
    
    std::cout << "Building test classification tree." << std::endl;
    DecisionTree classification_tree = DecisionTree(training_data,false,"gini_impurity",-1,-1,-1,-1,-1);
    std::cout << "Size (before fitting) : " + std::to_string(classification_tree.getSize()) << std::endl;
    std::cout << "Size (after fitting) : " + std::to_string(classification_tree.getSize()) << std::endl;
    std::vector<TreeNode*> tree_leaves = classification_tree.getLeaves();
    TreeNode *leaf;
    for (int i = 0; i < tree_leaves.size(); i++)
    {
        leaf = tree_leaves[i];
        if (leaf->isRoot()) {
            std::cout << "At root node";
        } else {
            std::cout << "After splitting on column "+std::to_string(leaf->getParent()->getSplitFeature())+" ";
            std::cout << "at value "+std::to_string(leaf->getParent()->getSplitThreshold());
            
        }
        std::cout << " -- leaf "+std::to_string(i+1)+" :" << std::endl;
        std::cout << tree_leaves[i]->getDataFrame() << std::endl;
    }
    
    std::cout << "Perform prediction on new data." << std::endl;
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
    DataVector test_predictions = classification_tree.predict(&test_data);
    std::cout << "Predictions :" << std::endl;
    std::cout << test_predictions << std::endl;

    // Print classification tree:
    std::cout << classification_tree << std::endl;

    // Print regression tree:
    DecisionTree regression_tree = DecisionTree(training_data,true,"mean_squared_error",-1,-1,-1,-1,-1);
    std::cout << regression_tree << std::endl;

    return 0;
};
