#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

class TreeNode
{
    /** 
     * An basic data structure representing a node in a decision tree.
     * Includes functionality for implementing decisions. 
     * */

private:

    // Attributes:
    int size_;  // Size of subtree, including self.
    int height_;  // Height of subtree rooted at this node.
    int depth_;  // Distance between this node and the root (where root has depth zero).
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
    int getHeight();
    int getDepth();
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
    void updateHeights();
    void updateDepths();

};

#endif
