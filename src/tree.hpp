#ifndef TREE_HPP
#define TREE_HPP

class TreeNode
{
    /** 
     * An basic data structure representing a node in a decision tree.
     * Includes functionality for implementing decisions. 
     * */

private:

    // Attributes:
    int size_;  // Size of subtree, including self.
    TreeNode *parent_;  // Pointer to parent node.
    TreeNode *left_;  // Pointer to left child.
    TreeNode *right_;  // Pointer to right child.
    int split_feature_;  // Index of splitting column.
    double split_threshold_;  // Numberical splitting thresold.

public:
    
    // Constructors:
    TreeNode(TreeNode *parent, TreeNode *left, TreeNode *right, int split_feature, double split_threshold);
    TreeNode(TreeNode *parent, TreeNode *left, TreeNode *right);
    TreeNode(TreeNode *left, TreeNode *right);
    TreeNode(TreeNode *parent);
    TreeNode();

    // Getters:
    int getSize();
    TreeNode * getParent();
    TreeNode * getLeft();
    TreeNode * getRight();
    int getSplitFeature();
    double getSplitThreshold();

    // Setters:
    void setLeft(TreeNode *left);
    void setRight(TreeNode *right);
    void setSplitFeature(int split_feature);
    void setSplitThreshold(double split_threshold);

    // Utilities:
    TreeNode * findRoot();
    void updateSizes();

};

class DecisionTree
{
private:

    // Attributes:
    TreeNode *root_;

public:

    // Constructors:
    DecisionTree();
    DecisionTree(TreeNode *root);

    // Getters:
    int getSize();
    TreeNode * getRoot();

    // Setters:
    void setRoot(TreeNode *root);

    // Utilities:

};

#endif
