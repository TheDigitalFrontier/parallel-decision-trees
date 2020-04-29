#include "tree_node.hpp"

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
    /**
     * Get number of nodes (including self) in subtree rooted at this node.
     */
    return this->size_;
}

int TreeNode::getHeight()
{
    /**
     * Get height of subtree rooted at this node.
     */
    return this->height_;
}

int TreeNode::getDepth()
{
    /** 
     * Get distance between this node and the root (where root has depth zero).
     */
    return this->depth_;
}

TreeNode * TreeNode::getParent()
{
    /** 
     * Get pointer to parent node.
     */
    return this->parent_;
}

TreeNode * TreeNode::getLeft()
{
    /** 
     * Get pointer to left child.
     */
    return this->left_;
}

TreeNode * TreeNode::getRight()
{
    /** 
     * Get pointer to right child.
     */
    return this->right_;
}

int TreeNode::getSplitFeature()
{
    /** 
     * Get index of splitting column.
     */
    return this->split_feature_;
}

double TreeNode::getSplitThreshold()
{
    /** 
     * Get numberical splitting thresold.
     */
    return this->split_threshold_;
}

// Setters:

void TreeNode::setLeft(TreeNode *left)
{
    /** 
     * Set pointer to left child.
     */
    this->left_ = left;
    left->parent_ = this;
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

void TreeNode::setRight(TreeNode *right)
{
    /** 
     * Set pointer to right child.
     */
    this->right_ = right;
    right->parent_ = this;
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

void TreeNode::setSplitFeature(int split_feature)
{
    /** 
     * Set index of splitting column.
     */
    this->split_feature_ = split_feature;
}

void TreeNode::setSplitThreshold(double split_threshold)
{
    /** 
     * Set numberical splitting thresold.
     */
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
    /**
     * Helper function for recursively updating node size.
     */
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
    /**
     * Helper function for recursively updating node size.
     */
    // Update this node:
    int d;
    if ( this->parent_ != nullptr ){ d = this->parent_->depth_ + 1; } else { d = 0; }
    this->depth_ = d;
    // Recruse down:
    if (this->left_ != nullptr ){ this->left_->updateDepths(); }
    if (this->right_ != nullptr ){ this->right_->updateDepths(); }
}
