#include <iostream>
#include "tree_node.cpp"
#include "decision_tree.cpp"
#include "datasets.cpp"

int main(){

    std::cout << "Loading test dataset." << std::endl;
    DataLoader test_loader = DataLoader();
    DataFrame test_data = test_loader.load();
    test_data.print();
    
    std::cout << "Building test decision tree." << std::endl;
    DecisionTree test_tree = DecisionTree(test_data);
    std::cout << "Size : " + std::to_string(test_tree.getSize()) << std::endl;

    return 0;
};
