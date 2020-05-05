#include "decision_tree.hpp"
#include "tree_node.hpp"
#include "datasets.hpp"

// Constructors:

DecisionTree::DecisionTree(DataFrame dataframe, bool regression)
{
    this->regression_ = regression;
    this->dataframe_ = dataframe;
    TreeNode *root = new TreeNode(this->dataframe_);
    this->root_ = root;
}

// Getters:

int DecisionTree::getSize() const
{
    /**
     * Get the number of nodes in the tree.
     */
    if ( this->root_ != nullptr )
    {
        return this->root_->getSize();
    } else {
        return 0;
    }
}

int DecisionTree::getHeight() const
{
    /**
     * Get the height of the tree.
     */
    if ( this->root_ != nullptr )
    {
        return this->root_->getHeight();
    } else {
        return 0;
    }
}

bool DecisionTree::isRegressionTree() const
{
    /** Return true if regression tree and false if classification tree. */
    return this->regression_;
}

TreeNode * DecisionTree::getRoot() const
{
    /**
     * Get the pointer to the root node.
     */
    return this->root_;
}

DataFrame DecisionTree::getDataFrame() const
{
    /**
     * Get the pointer to the dataframe.
     */
    return this->dataframe_;
}

// Setters:

/*
    int main()
    {
        return 0;
    }
*/
