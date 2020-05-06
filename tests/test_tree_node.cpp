#include <iostream>
#include "../src/tree_node.cpp"
#include "../src/datasets.cpp"

int main(){

    std::cout << "Building test tree with a few nodes.";
    std::cout << "" << std::endl;

    TreeNode node0 = TreeNode();
    TreeNode node1 = TreeNode();
    TreeNode node2 = TreeNode();
    TreeNode node3 = TreeNode();
    TreeNode node4 = TreeNode();
    node0.setLeft(&node1);
    node1.setLeft(&node2);
    node1.setRight(&node3);
    node2.setLeft(&node4);

    std::cout << "Tree size: ";
    std::cout << node0.getSize() << std::endl;

    std::cout << "Tree height: ";
    std::cout << node0.getHeight() << std::endl;

    std::cout << "Node4 depth: ";
    std::cout << node4.getDepth() << std::endl;

    std::cout << "Count leaves: ";
    std::vector<TreeNode*> leaves = node0.findLeaves();
    std::cout << leaves.size() << std::endl;

    return 0;
};
