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
        {2.7810836,2.550537003,0}, 
        {1.465489372,2.362125076,0},
        {7.627531214,2.759262235,1}, 
        {3.396561688,4.400293529,0},
        {8.675418651,-0.242068655,1}, 
        {1.38807019,1.850220317,0}, 
        {3.06407232,3.005305973,0},  
        {5.332441248,2.088626775,1}, 
        {6.922596716,1.77106367,1},  
        {7.673756466,3.508563011,1},
        {7.673756466,3.301233593,1}
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
        std::cout << "After splitting on column "+std::to_string(leaf->getParent()->getSplitFeature())+" ";
        std::cout << "at value "+std::to_string(leaf->getParent()->getSplitThreshold())+" -- ";
        std::cout << "leaf "+std::to_string(i+1)+" :";
        std::cout << std::endl;
        std::cout << tree_leaves[i]->getDataFrame() << std::endl;
    }
    
    std::cout << "Perform prediction on new data." << std::endl;
    DataFrame *test_data = new DataFrame({
        {2.9810,2.5605,0}, 
        {1.3654,2.3621,0},
        {7.6275,2.8592,1}, 
        {3.3865,4.6002,0},
        {8.7754,-0.142,1}, 
    });
    DataVector test_predictions = decision_tree.predict(test_data);
    delete test_data;  // Remove dataframe from heap.
    std::cout << "Predictions :" << std::endl;
    std::cout << test_predictions << std::endl;

    return 0;
};
