#include "tree_node.hpp"
#include "datasets.hpp"
#include <assert.h>

// Constructors:

TreeNode::TreeNode(DataFrame dataframe)
{
    /** Build a TreeNode with only splitting attributes. */
    this->parent_ = nullptr;
    this->left_ = nullptr;
    this->right_ = nullptr;
    this->dataframe_ = dataframe;
    this->has_split_ = false;
    //this->split_feature_ = NULL;
    //this->split_threshold_ = NULL;
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

TreeNode::TreeNode(DataFrame dataframe, int split_feature, double split_threshold)
{
    /** Build a TreeNode with only a dataframe. */
    this->parent_ = nullptr;
    this->left_ = nullptr;
    this->right_ = nullptr;
    this->dataframe_ = dataframe;
    this->has_split_ = false;
    //this->split_feature_ = NULL;
    //this->split_threshold_ = NULL;
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

TreeNode::TreeNode(TreeNode *parent, TreeNode *left, TreeNode *right, DataFrame dataframe, int split_feature, double split_threshold)
{
    /** Build a TreeNode with all attributes. */
    this->parent_ = parent;
    this->left_ = left;
    this->right_ = right;
    this->dataframe_ = dataframe;
    this->has_split_ = true;
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
    //this->dataframe_ = NULL;
    this->has_split_ = false;
    //this->split_feature_ = NULL;
    //this->split_threshold_ = NULL;
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

TreeNode::TreeNode()
{
    /** Build a TreeNode with null attributes. */
    this->parent_ = nullptr;
    this->left_ = nullptr;
    this->right_ = nullptr;
    this->has_split_ = false;
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

// Getters:

bool TreeNode::hasSplit() const
{
    /** Checks if splitting values have been set. */
    return (this->has_split_);
}

bool TreeNode::hasLeft() const
{
    /** Checks if node has left child. */
    return (this->left_ != nullptr);
}

bool TreeNode::hasRight() const
{
    /** Checks if node has right child. */
    return (this->right_ != nullptr);
}

bool TreeNode::isLeaf() const
{
    /** Checks if node is a leaf (i.e. has no children). */
    return (!this->hasLeft()) and (!this->hasRight());
}

bool TreeNode::isRoot() const
{
    /** Checks if node is the root (i.e. has no parent). */
    return (this->parent_ == nullptr);
}

int TreeNode::getSize() const
{
    /**
     * Get number of nodes (including self) in subtree rooted at this node.
     */
    return this->size_;
}

int TreeNode::getHeight() const
{
    /**
     * Get height of subtree rooted at this node.
     */
    return this->height_;
}

int TreeNode::getDepth() const
{
    /**
     * Get distance between this node and the root (where root has depth zero).
     */
    return this->depth_;
}

TreeNode * TreeNode::getParent() const
{
    /**
     * Get pointer to parent node.
     */
    return this->parent_;
}

TreeNode * TreeNode::getLeft() const
{
    /**
     * Get pointer to left child.
     */
    return this->left_;
}

TreeNode * TreeNode::getRight() const
{
    /**
     * Get pointer to right child.
     */
    return this->right_;
}

DataFrame TreeNode::getDataFrame() const
{
    /**
     * Get dataframe.
     */
    return this->dataframe_;
}

int TreeNode::getSplitFeature() const
{
    /**
     * Get index of splitting column.
     */
    assert (this->hasSplit());
    return this->split_feature_;
}

double TreeNode::getSplitThreshold() const
{
    /** 
     * Get numerical splitting threshold.
     */
    assert (this->hasSplit());
    return this->split_threshold_;
}

// Setters:

void TreeNode::setLeft(TreeNode *left)
{
    /**
     * Set pointer to left child.
     */
    // Unlink any existing child:
    if ( this->left_ != nullptr ) { this->left_ ->parent_ = nullptr; }
    // Add then new child and link it:
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
    // Unlink any existing child:
    if ( this->right_ != nullptr ) { this->right_->parent_ = nullptr; }
    // Add then new child and link it:
    this->right_ = right;
    right->parent_ = this;
    TreeNode *root = this->findRoot();
    root->updateSizes();
    root->updateHeights();
    root->updateDepths();
}

void TreeNode::setDataFrame(DataFrame dataframe)
{
    /**
     * Set dataframe for splitting.
     */
    this->dataframe_ = dataframe;
}

void TreeNode::setSplitFeature(int split_feature)
{
    /**
     * Set index of splitting column.
     */
    this->has_split_ = true;
    this->split_feature_ = split_feature;
}

void TreeNode::setSplitThreshold(double split_threshold)
{
    /**
     * Set numerical splitting threshold.
     */
    this->has_split_ = true;
    this->split_threshold_ = split_threshold;
}

// Utilities:

TreeNode * TreeNode::findRoot()
{
    /**
     * Recursively find the the node with no parent.
     */
    TreeNode *node;
    node = this;
    while ( !node->isRoot() )
    {
        node = node->parent_;
    }
    return node;
}

void TreeNode::updateSizes()
{
    /**
     * Helper function for recursively updating node size.
     */
    // Recruse down:
    if (this->hasLeft()){ this->left_->updateSizes(); }
    if (this->hasRight()){ this->right_->updateSizes(); }
    // Update this node and return:
    this->size_ = 1;
    if (this->hasLeft()){ this->size_ += this->left_->size_; }
    if (this->hasRight()){ this->size_ += this->right_->size_; }
}

void TreeNode::updateHeights()
{
    /**
     * Helper function for recursively updating node size.
     */
    // Recruse down:
    if (this->hasLeft()){ this->left_->updateHeights(); }
    if (this->hasRight()){ this->right_->updateHeights(); }
    // Update this node and return:
    int left_height;
    int right_height;
    if (this->hasLeft()){ left_height = this->left_->height_; } else { left_height = 0; }
    if (this->hasRight()){ right_height = this->right_->height_; } else { right_height = 0; }
    this->height_ = std::max(left_height,right_height) + 1;
}

void TreeNode::updateDepths()
{
    /**
     * Helper function for recursively updating node size.
     */
    // Update this node:
    int d;
    if (!this->isRoot()){ d = this->parent_->depth_ + 1; } else { d = 0; }
    this->depth_ = d;
    // Recruse down:
    if (this->hasLeft()){ this->left_->updateDepths(); }
    if (this->hasRight()){ this->right_->updateDepths(); }
}



std::vector<TreeNode*> TreeNode::findLeaves()
{
    /**
     * Get leaves in subtree rooted at this node.
     */
    std::vector<TreeNode*> results;
    return this->findLeaves(results);
}

std::vector<TreeNode*> TreeNode::findLeaves(std::vector<TreeNode*> results)
{
    /**
     * Get leaves in subtree rooted at this node: recursive helper for getLeaves().
     */
    // If this is a leaf, add to results:
    if (this->isLeaf()){ results.push_back(this); }
    // (Otherwise): Recurse downward.
    if (this->hasLeft()){ results = this->left_->findLeaves(results); }
    if (this->hasRight()){ results = this->right_->findLeaves(results); }
    return results;
}
