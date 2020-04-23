#include "tree.hpp"

/**
 * TreeNode
 */

// Constructors:

TreeNode::TreeNode(TreeNode *parent, TreeNode *left, TreeNode *right, int split_feature, double split_threshold)
{
    /** Build a TreeNode with all attributes. */
    this->parent_ = parent;
    this->left_ = left;
    this->right_ = right;
    this->split_feature_ = split_feature;
    this->split_threshold_ = split_threshold;
    this->findRoot()->updateSizes();
}

TreeNode::TreeNode(TreeNode *parent, TreeNode *left, TreeNode *right)
{
    /** Build a TreeNode without splitting attributes. */
    this->parent_ = parent;
    this->left_ = left;
    this->right_ = right;
    //this->split_feature_ = NULL;
    //this->split_threshold_ = NULL;
    this->findRoot()->updateSizes();
}

TreeNode::TreeNode(TreeNode *left, TreeNode *right) : TreeNode(nullptr, left, right)
{
    /** Build a TreeNode with only child nodes. */
    this->findRoot()->updateSizes();
}

TreeNode::TreeNode(TreeNode *parent) : TreeNode(parent, nullptr, nullptr)
{
    /** Build a TreeNode with only a parent node. */
    this->findRoot()->updateSizes();
}

TreeNode::TreeNode() : TreeNode(nullptr, nullptr, nullptr)
{
    /** Build a TreeNode with null attributes. */
    this->findRoot()->updateSizes();
}

// Getters:

int TreeNode::getSize()
{
    return this->size_;
}

TreeNode * TreeNode::getParent()
{
    return this->parent_;
}

TreeNode * TreeNode::getLeft()
{
    return this->left_;
}

TreeNode * TreeNode::getRight()
{
    return this->right_;
}

int TreeNode::getSplitFeature()
{
    return this->split_feature_;
}

double TreeNode::getSplitThreshold()
{
    return this->split_threshold_;
}

// Setters:

void TreeNode::setLeft(TreeNode *left)
{
    this->left_ = left;
    left->parent_ = this;
    this->findRoot()->updateSizes();
}

void TreeNode::setRight(TreeNode *right)
{
    this->right_ = right;
    right->parent_ = this;
    this->findRoot()->updateSizes();
}

void TreeNode::setSplitFeature(int split_feature)
{
    this->split_feature_ = split_feature;
}

void TreeNode::setSplitThreshold(double split_threshold)
{
    this->split_threshold_ = split_threshold;
}

// Utilities:

TreeNode * TreeNode::findRoot()
{
    /**
     * Recursively find the the node with no parent.
     */
    TreeNode *root;
    root = this;
    while ( root->parent_ != nullptr )
    {
        root = root->parent_;
    }
    return root;
}

void TreeNode::updateSizes()
{
    /**
     * Helper function for recursively updating node size.
     */
    // Recruse down:
    if (this->left_ != nullptr ){ this->left_->updateSizes(); }
    if (this->right_ != nullptr ){ this->right_->updateSizes(); }
    // Update this node and return:
    this->size_ = 1;
    if ( this->left_ != nullptr ){ this->size_ += this->left_->size_; }
    if ( this->right_ != nullptr ){ this->size_ += this->right_->size_; }
}

/**
 * DecisionTree
 */

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

int DecisionTree::getSize()
{
    return this->root_->getSize();
}

TreeNode * DecisionTree::getRoot()
{
    return this->root_;
}

// Setters:

void DecisionTree::setRoot(TreeNode *root)
{
    this->root_ = root;
    this->root_->updateSizes();
}

/*
    int main()
    {
        return 0;
    }
*/
