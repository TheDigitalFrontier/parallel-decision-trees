#include "decision_tree.hpp"
#include "tree_node.hpp"

// Constructors:

DecisionTree::DecisionTree()
{
    this->root_ = nullptr;
}

DecisionTree::DecisionTree(TreeNode *root)
{
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

TreeNode * DecisionTree::getRoot() const
{
    /**
     * Get the pointer to the root node.
     */
    return this->root_;
}

// Setters:

void DecisionTree::setRoot(TreeNode *root)
{
    this->root_ = root;
    this->root_->updateSizes();
    this->root_->updateHeights();
    this->root_->updateDepths();
}

/*
    int main()
    {
        return 0;
    }
*/
