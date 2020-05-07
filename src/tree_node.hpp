#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include "datasets.hpp"

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
    DataFrame dataframe_;  // Data frame for splitting.
    bool has_split_;  // Flag indicating whether splitting values have been set.
    int split_feature_;  // Index of splitting column.
    double split_threshold_;  // Numerical splitting threshold.

public:

    // Constructors:
    TreeNode(DataFrame dataframe);
    TreeNode(DataFrame dataframe, int split_feature, double split_threshold);
    TreeNode(TreeNode *parent, TreeNode *left, TreeNode *right, DataFrame dataframe, int split_feature, double split_threshold);
    TreeNode(TreeNode *parent, TreeNode *left, TreeNode *right);
    TreeNode();

    // Getters:
    bool hasSplit() const;
    bool hasLeft() const;
    bool hasRight() const;
    bool isLeaf() const;
    bool isRoot() const;
    int getSize() const;
    int getHeight() const;
    int getDepth() const;
    TreeNode * getParent() const;
    TreeNode * getLeft() const;
    TreeNode * getRight() const;
    DataFrame getDataFrame() const;
    int getSplitFeature() const;
    double getSplitThreshold() const;

    // Setters:
    void setLeft(TreeNode *left);
    void setRight(TreeNode *right);
    void setDataFrame(DataFrame dataframe);
    void setSplitFeature(int split_feature);
    void setSplitThreshold(double split_threshold);

    // Utilities:
    TreeNode * findRoot();
    void updateSizes();
    void updateHeights();
    void updateDepths();
    std::vector<TreeNode*> findLeaves();
    std::vector<TreeNode*> findLeaves(std::vector<TreeNode*> results);

};

#endif
