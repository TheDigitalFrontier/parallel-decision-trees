#include <iostream>
#include "tree_node.cpp"
#include "decision_tree.cpp"
#include "datasets.cpp"
#include "losses.cpp"

int main(){

    std::cout << "Loading test dataset." << std::endl;
    //DataLoader training_loader = DataLoader();
    //DataFrame training_data = training_loader.load();
    DataFrame training_data = DataFrame({
        {2.232, 2.456, 1},
        {2.277, 8.735, 2},
        {2.965, 6.846, 2},
        {2.252, 6.452, 2},
        {2.222, 9.944, 2},
        {2.322, 8.747, 2},
        {2.552, 7.833, 2},
        {2.242, 9.941, 2},
        {6.201, 6.452, 3},
        {7.403, 9.944, 3},
        {8.720, 8.747, 3},
        {6.804, 9.941, 3},
        {6.201, 9.452, 3},
        {8.403, 3.944, 4},
    });
    training_data.print();
    
    std::cout << "Building test classification tree." << std::endl;
    DecisionTree decision_tree = DecisionTree(training_data,false,"gini_impurity",-1,-1,-1,-1,-1);
    std::cout << "Size (before fitting) : " + std::to_string(decision_tree.getSize()) << std::endl;
    decision_tree.fit();
    std::cout << "Size (after fitting) : " + std::to_string(decision_tree.getSize()) << std::endl;
    std::vector<TreeNode*> tree_leaves = decision_tree.getLeaves();
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
    DataFrame *test_data = new DataFrame({
        {2.0, 0.0},  // Expected: 1.
        {2.0, 1.0},  // Expected: 1.
        {2.0, 2.0},  // Expected: 1.
        {2.0, 7.0},  // Expected: 2.
        {2.0, 8.0},  // Expected: 2.
        {2.0, 9.0},  // Expected: 2.
        {7.0, 7.0},  // Expected: 3.
        {7.0, 8.0},  // Expected: 3.
        {7.0, 9.0},  // Expected: 3.
        {7.0, 1.0},  // Expected: 4.
        {7.0, 2.0},  // Expected: 4.
    });
    DataVector test_predictions = decision_tree.predict(test_data);
    delete test_data;  // Remove dataframe from heap.
    std::cout << "Predictions :" << std::endl;
    std::cout << test_predictions << std::endl;

    return 0;
};
