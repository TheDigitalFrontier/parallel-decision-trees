#include <iostream>
#include "tree_node.cpp"
#include "decision_tree.cpp"
#include "datasets.cpp"
#include "losses.cpp"

int main(){

    std::cout << "Loading test dataset." << std::endl;
    DataLoader test_loader = DataLoader();
    DataFrame test_data = test_loader.load();
    test_data.print();
    
    std::cout << "Building test classification tree." << std::endl;
    DecisionTree test_tree = DecisionTree(test_data,false,"gini_impurity",-1,8,8);
    std::cout << "Size (before fitting) : " + std::to_string(test_tree.getSize()) << std::endl;
    test_tree.fit();
    std::cout << "Size (after fitting) : " + std::to_string(test_tree.getSize()) << std::endl;
    std::vector<TreeNode*> tree_leaves = test_tree.getLeaves();
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

    return 0;
};
