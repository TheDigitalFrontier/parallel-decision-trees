#include "decision_tree.hpp"
#include "tree_node.hpp"
#include "datasets.hpp"
#include "losses.hpp"
#include <algorithm>  // std::sort.
#include <assert.h>
#include <math.h>  // std::sqrt.
#include <time.h>  // std::time.

// Constructors:

DecisionTree::DecisionTree(DataFrame dataframe, bool regression, std::string loss, int mtry, int max_height, int max_leaves)
{
    /**
     * Initialize a DecisionTree with given training set and hyperparameters.
     *    dataframe  : Training data (with class labels in right-most column).
     *    regression : Type of tree: regression or classification.
     *    loss       : String indicating which type of loss to use.
     *    mtry       : Hyperparameter: Number of features to use at each split (or -1 for all in deterministic order; or 0 for sqrt(n_columns) ).
     *    max_height : Stopping condition: max height of tree (or -1 for no stopping on this condition).
     *    max_leaves : Stopping condition: max number of leaves (or -1 for no stopping on this condition).
    */
    // Check inputs:
    assert ((dataframe.length()>0) and dataframe.width()>0);  // Need at least one row and column (plus class column).
    assert ((max_height==-1) or (max_height>=1));  // -1 indicates no max depth.
    assert ((max_leaves==-1) or (max_leaves>=1));  // -1 indicates no max leaves.
    assert ((mtry>=-1) and (mtry<dataframe.width()));
    if (regression) {
        // Regression tree:
        if ( (loss=="mean_squared_error") ) {
            ; // pass.
        } else {
            throw std::invalid_argument( "Received invalid loss method for regression tree: "+loss );
        }
    } else {
        // Classification tree:
        if ( (loss=="misclassification_error") or (loss=="binary_cross_entropy") or (loss=="gini_impurity") ) {
            ; // pass.
        } else {
            throw std::invalid_argument( "Received invalid loss method for classification tree: "+loss );
        }
    }
    // Set properties constructor from inputs:
    this->dataframe_ = dataframe;
    this->regression_ = regression;
    this->loss_ = loss;
    this->mtry_ = mtry;
    this->max_height_ = max_height;
    this->max_leaves_ = max_leaves;
    // Initialize:
    TreeNode *root = new TreeNode(this->dataframe_);
    this->root_ = root;
    this->num_leaves_ = 1;
    this->num_features_ = dataframe.width()-1;  // Number of columns, excluding label column.
    this->leaves_ = {this->root_};
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

std::vector<TreeNode*> DecisionTree::getLeaves()
{
    /** Get leaves of fitted tree. */
    return this->leaves_;
}

DataFrame DecisionTree::getDataFrame() const
{
    /**
     * Get the pointer to the dataframe.
     */
    return this->dataframe_;
}

// Setters:

// Utilities:

double DecisionTree::calculateLoss(DataFrame* dataframe) const
{
    /** Calculate loss before split. */
    assert (dataframe->length()>0);  // Vector should be non-empty.
    LossFunction loss_func = LossFunction(this->loss_);
    double loss = loss_func.calculate(dataframe);
    return loss;
}

double DecisionTree::calculateSplitLoss(DataFrame* left_dataframe, DataFrame* right_dataframe) const
{
    /** Calculate loss on split dataset using weighted average of loss in each split. */
    int left_size = left_dataframe->length();
    int right_size = right_dataframe->length();
    int total_size = left_size + right_size;
    assert ( (left_size>0) and (right_size>0) );  // Both vectors should be non-empty.
    // Get loss for each vector:
    LossFunction loss_func = LossFunction(this->loss_);
    double left_loss = loss_func.calculate(left_dataframe->col(-1));  // Get class labels from last column.
    double right_loss = loss_func.calculate(right_dataframe->col(-1));  // Get class labels from last column.
    // Get weighted average of loss:
    double loss = (left_loss*left_size/total_size) + (right_loss*right_size/total_size);
    return loss;
}

std::pair<int,double> DecisionTree::findBestSplit(TreeNode *node) const
{
    /** Find best split at this node. */
    DataFrame dataframe = node->getDataFrame();
    assert (dataframe.length()>1);  // Must have enough data to split.
    std::pair<int,double> split;
    int m;  // How many features to try.
    std::vector<int> shuf_inds(this->num_features_);  // Vector of indices which may or may not be shuffled.
    if (this->mtry_==-1){
        // Deterministic:
        m = this->num_features_;
        // Add indices without actually shuffling:
        for (int i = 0; i < this->num_features_; i++){
            shuf_inds[i] = i;
        }
    } else {
        // Randomly select mtry features (or sqrt(n_features) if mtry==0):
        m = (this->mtry_==0) ? int(std::floor(sqrt(this->num_features_))) : this->mtry_;
        // Pre-allocate vector of column indices
        std::vector<int> shuf_inds(this->num_features_);
        // Create vector of column indices, equivalent to np.arange(0, df.shape[-1])
        std::generate(shuf_inds.begin(), shuf_inds.end(), [n = 0] () mutable { return n++; });
        // Set changing random generator (arrow of time is inexorable!)
        srand((unsigned) time(0));
        // Shuffle it:
        for (int i = 0; i < this->num_features_; i++){
            std::swap(shuf_inds[i], shuf_inds[i+(std::rand() % (this->num_features_-i))]);
        }
    }
    // Initialize temporary variables:
    int best_column, col = -1;
    double best_threshold, best_loss, loss;
    // Explore possible splits:
    for (int i = 0; i < m; i++){
        col = shuf_inds[i];
        std::vector<double> col_vals = dataframe.col(col)->vector();
        // Remove duplicates:
        std::sort(col_vals.begin(), col_vals.end());
        col_vals.erase(std::unique(col_vals.begin(), col_vals.end()), col_vals.end());
        // For each unique column value, try that col and val as split, get score:
        for (int j = 0; j < col_vals.size()-1; j++){
            double val = col_vals[j];  // Don't split on last value (because it will produce empty `right`).
            // Split dataset using current column and threshold, score, and update if best:
            std::vector<DataFrame*> dataset_splits = dataframe.split(shuf_inds[i], val, true); // equal_goes_left=true.
            loss = this->calculateSplitLoss(dataset_splits[0],dataset_splits[1]);
            if ((best_column==-1) or (loss<best_loss)){
                best_column = col;
                best_threshold = val;
                best_loss = loss;
            }
        }
    }
    // Return result:
    assert (best_column!=-1);  // Placeholder value should have been replaced.
    split = std::make_pair(best_column,best_threshold);
    return split;
}

void DecisionTree::fit_(TreeNode* node)
{
    DataFrame dataframe = node->getDataFrame();
    LabelCounter label_counter = LabelCounter(dataframe.col(-1));
    if ( label_counter.size()==1 ) {
        ;  // Prune if there is only one class left.
    } else if ( (this->max_height_!=-1) and (node->getDepth()+1>=this->max_height_) ) { 
        ;  // Prune if adding children would exceed max depth:
    } else if ( (this->max_leaves_!=-1) and (this->num_leaves_+1>=this->max_leaves_) ) { 
        ;  // Prune if adding children would exceed max leaves:
    } else if ( dataframe.length()<2 ) {
        ;  // Prune if there is not enough data to split.
    } else {
        // Find best split at this node:
        std::pair<int,double> split = this->findBestSplit(node);
        int split_feature = split.first;
        double split_threshold = split.second;
        node->setSplitFeature(split_feature);
        node->setSplitThreshold(split_threshold);
        // Apply best split at this node:
        this->num_leaves_ += 1;  // Each split causes net addition of 1 leaf.
        std::vector<DataFrame*> left_right = dataframe.split(split_feature,split_threshold,true);  // equal_goes_left=true.
        DataFrame *left_data = left_right[0];
        DataFrame *right_data = left_right[1];
        TreeNode *left_child = new TreeNode(*left_data);
        TreeNode *right_child = new TreeNode(*right_data);
        node->setLeft(left_child);
        node->setRight(right_child);
        // Recurse to (new) children:
        this->fit_(left_child);
        this->fit_(right_child);
    }
}

void DecisionTree::fit()
{
    // Fit recursively, beginning at root:
    fit_(this->root_);
    // Update list of leaves:
    this->leaves_ = this->root_->findLeaves();
}

/*
    int main()
    {
        return 0;
    }
*/
