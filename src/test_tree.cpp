#include <iostream>
#include "tree.cpp"

int main(){

    std::cout << "Building test tree with a few nodes.";
    std::cout << "" << std::endl;

    TreeNode node1 = TreeNode();
    TreeNode node2 = TreeNode();
    TreeNode node3 = TreeNode();
    node1.setLeft(&node2);
    node1.setRight(&node3);

    DecisionTree tree1(&node1);

    std::cout << "Tree size: ";
    std::cout << tree1.getSize();
    std::cout << "" << std::endl;

    return 0;
};
