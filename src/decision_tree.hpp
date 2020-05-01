#ifndef DECISION_TREE_HPP
#define DECISION_TREE_HPP

#include "tree_node.hpp"
#include "datasets.hpp"

class DecisionTree
{
private:

    // Attributes:
    TreeNode *root_;
    DataFrame dataframe_;

public:

    // Constructors:
    DecisionTree(DataFrame dataframe);

    // Getters:
    int getSize() const;
    int getHeight() const;
    TreeNode * getRoot() const;
    DataFrame getDataFrame() const;

    // Setters:

    // Utilities:

};

#endif
