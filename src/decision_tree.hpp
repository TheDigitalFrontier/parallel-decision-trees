#ifndef DECISION_TREE_HPP
#define DECISION_TREE_HPP

#include "tree_node.hpp"
#include "datasets.hpp"

class DecisionTree
{
private:

    // Attributes:
    bool regression_;  // Use regression==false for a classification tree.
    TreeNode *root_;
    DataFrame dataframe_;

public:

    // Constructors:
    DecisionTree(DataFrame dataframe, bool regression=false);

    // Getters:
    int getSize() const;  // Number of nodes in tree.
    int getHeight() const;  // Height of tree.
    bool isRegressionTree() const;  // Type of tree (classification or regression).
    TreeNode * getRoot() const;  // Root node in tree.
    DataFrame getDataFrame() const;  // Training data.

    // Setters:

    // Utilities:
    void fit() const;  // Perform fitting.

};

#endif
