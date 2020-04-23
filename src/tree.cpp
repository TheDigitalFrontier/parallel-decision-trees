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
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

TreeNode::TreeNode(TreeNode *parent, TreeNode *left, TreeNode *right)
{
    /** Build a TreeNode without splitting attributes. */
    this->parent_ = parent;
    this->left_ = left;
    this->right_ = right;
    //this->split_feature_ = NULL;
    //this->split_threshold_ = NULL;
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

TreeNode::TreeNode(TreeNode *left, TreeNode *right) : TreeNode(nullptr, left, right)
{
    /** Build a TreeNode with only child nodes. */
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

TreeNode::TreeNode(TreeNode *parent) : TreeNode(parent, nullptr, nullptr)
{
    /** Build a TreeNode with only a parent node. */
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

TreeNode::TreeNode() : TreeNode(nullptr, nullptr, nullptr)
{
    /** Build a TreeNode with null attributes. */
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

// Getters:

int TreeNode::getSize()
{
    return this->size_;
}

int TreeNode::getHeight()
{
    return this->height_;
}

int TreeNode::getDepth()
{
    return this->depth_;
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

void TreeNode::updateHeights()
{
    // Recruse down:
    if (this->left_ != nullptr ){ this->left_->updateHeights(); }
    if (this->right_ != nullptr ){ this->right_->updateHeights(); }
    // Update this node and return:
    int left_height;
    int right_height;
    if ( this->left_ != nullptr ){ left_height = this->left_->height_; } else { left_height = 0; }
    if ( this->right_ != nullptr ){ right_height = this->right_->height_; } else { right_height = 0; }
    this->height_ = std::max(left_height,right_height) + 1;
}

void TreeNode::updateDepths()
{
    // Update this node:
    int height;
    if ( this->parent_ != nullptr ){ height = this->parent_->depth_ + 1; } else { height = 0; }
    this->height_ = height;
    // Recruse down:
    if (this->left_ != nullptr ){ this->left_->updateDepths(); }
    if (this->right_ != nullptr ){ this->right_->updateDepths(); }
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
    if ( this->root_ != nullptr )
    {
        return this->root_->getSize();
    } else {
        return 0;
    }
}

int DecisionTree::getHeight()
{
    if ( this->root_ != nullptr )
    {
        return this->root_->getHeight();
    } else {
        return 0;
    }
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
    this->root_->updateHeights();
    this->root_->updateDepths();
}

/*
    int main()
    {
        return 0;
    }
*/
