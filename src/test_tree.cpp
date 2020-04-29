#include <iostream>
#include "tree_node.cpp"
#include "decision_tree.cpp"

int main(){

    std::cout << "Building test tree with a few nodes.";
    std::cout << "" << std::endl;

    TreeNode node1 = TreeNode();
    TreeNode node2 = TreeNode();
    TreeNode node3 = TreeNode();
    TreeNode node4 = TreeNode();
    node1.setLeft(&node2);
    node1.setRight(&node3);
    node2.setLeft(&node4);

    DecisionTree tree1(&node1);

    std::cout << "Tree size: ";
    std::cout << tree1.getSize();
    std::cout << "" << std::endl;

    std::cout << "Tree height: ";
    std::cout << tree1.getHeight();
    std::cout << "" << std::endl;

    std::cout << "Node4 depth: ";
    std::cout << node4.getDepth();
    std::cout << "" << std::endl;

    return 0;
};
