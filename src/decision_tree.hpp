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
    int getSize() const;
    int getHeight() const;
    bool isRegressionTree() const;
    TreeNode * getRoot() const;
    DataFrame getDataFrame() const;

    // Setters:

    // Utilities:

};

#endif
