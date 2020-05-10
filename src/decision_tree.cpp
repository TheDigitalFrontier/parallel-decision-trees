#include "decision_tree.hpp"
#include "tree_node.hpp"
#include "datasets.hpp"
#include "losses.hpp"
#include <iostream>
#include <cmath>  // std::floor.
#include <math.h>  // std::sqrt.
#include <algorithm>  // std::sort.
#include <stack>  // std::stack.
#include <assert.h>
#include <time.h>  // std::time.

// Constructors:

DecisionTree::DecisionTree(
    DataFrame dataframe, bool regression, std::string loss,
    int mtry, int max_height, int max_leaves, int min_obs, double max_prop, int seed
)
{
    /**
     * Initialize a DecisionTree with given training set and hyperparameters.
     *    dataframe  : Training data (with class labels in right-most column).
     *    regression : Type of tree: regression or classification.
     *    loss       : String indicating which type of loss to use.
     *    mtry       : Hyperparameter: Number of features to use at each split (or -1 for all in deterministic order; or 0 for sqrt(n_columns) ).
     *    max_height : Stopping condition: max height of tree (or -1 for no stopping on this condition).
     *    max_leaves : Stopping condition: max number of leaves (or -1 for no stopping on this condition).
     *    min_obs    : Stopping condition: minimum number of observations in a leaf (or -1 for no stopping on this condition).
     *    max_prop   : Stopping condition: maximum proportion of majority class in a leaf (or -1 for no stopping on this condition).
     *    seed       : Non-negative seed (for repeatable results), or -1 (for non-deterministic sequence).
    */
    // Check inputs:
    assert ((dataframe.length()>0) and dataframe.width()>0);  // Need at least one row and column (plus class column).
    assert ((max_height==-1) or (max_height>=1));  // -1 indicates no max depth.
    assert ((max_leaves==-1) or (max_leaves>=1));  // -1 indicates no max leaves.
    assert ((min_obs==-1) or (min_obs>=1));  // -1 indicates no min observation number.
    assert ((max_prop==-1) or (max_prop>0));  // -1 indicates no max proportion.
    assert ((max_prop==-1) or (max_prop<=1));  // Proportion cannot be larger than 1.
    assert ((max_prop==-1) or (!regression));  // Proportion is only defined for classification, not regression.
    assert ((mtry>=-1) and (mtry<dataframe.width()));  // num_features = dataframe.width()-1  (column of labels is not a feature).
    if (regression) {
        // Regression tree:
        if ( (loss=="mean_squared_error") ) {
            ; // pass.
        } else {
            throw std::invalid_argument( "Received invalid loss method for regression tree: "+loss );
        }
    } else {
        // Classification tree:
        if ( (loss=="misclassification_error") or (loss=="cross_entropy") or (loss=="gini_impurity") ) {
            ; // pass.
        } else {
            throw std::invalid_argument( "Received invalid loss method for classification tree: "+loss );
        }
    }
    // Set properties constructor from inputs:
    this->dataframe_ = dataframe;
    this->num_features_ = dataframe.width()-1;  // Number of columns, excluding label column.
    this->regression_ = regression;
    this->loss_ = loss;
    this->mtry_ = (mtry==-1) ? this->num_features_ : mtry;
    this->max_height_ = max_height;
    this->max_leaves_ = max_leaves;
    this->min_obs_ = min_obs;
    this->max_prop_ = max_prop;
    this->meta_seed_ = seed;
    // Initialize:
    TreeNode *root = new TreeNode(this->dataframe_);
    this->root_ = root;
    this->num_leaves_ = 1;
    this->leaves_ = {this->root_};
    this->fitted_ = false;
    this->seed_gen = SeedGenerator(this->meta_seed_);
    // Perform training:
    fit_(this->root_);  // Fit recursively, beginning at root:
    // Update list of leaves:
    this->leaves_ = this->root_->findLeaves();
    this->fitted_ = true;
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

bool DecisionTree::isFitted() const
{
    /** Return true if tree has been trained and false otherwise. */
    return this->fitted_;
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

std::string DecisionTree::to_string() const
{
    /** Return the DecisionTree as a string. */
    int indent = 4;
    std::string out = "";
    if (this->isRegressionTree()) {
        out += "REGRESSION TREE : ";
    } else {
        out += "CLASSIFICATION TREE : ";
    }
    out += std::to_string(this->getSize()) + " nodes; ";
    out += std::to_string(this->num_leaves_) + " leaves; ";
    out += "height: " + std::to_string(this->getHeight()) + " : ";
    out += "\n";
    // Prepare stack of nodes to process:
    //   Each pair has a node and an integer representing type (0==root; -1==left; +1==right).
    std::stack<std::pair<int,TreeNode*>> stk;
    int type = 0;
    TreeNode* node = this->getRoot();
    std::pair<int,TreeNode*> pr = std::make_pair(type,node);
    stk.push(pr);
    while (stk.size()>0)
    {
        // Get top element, then remove it:
        pr = stk.top();
        stk.pop();
        type = pr.first;
        node = pr.second;
        // Add children (if they exist) to be processed next:
        if (node->hasRight()) { stk.push(std::make_pair(1,node->getRight())); }
        if (node->hasLeft()) { stk.push(std::make_pair(-1,node->getLeft())); }
        // Add this node to string:
        out.append(indent,' ');
        for (int i = 0; i < node->getDepth(); i++)
        {
            out.append(indent,' ');
        }
        //  Add node text:
        if (type==-1) {
            out += "(L) ";
        } else if (type==1) {
            out += "(R) ";
        } else {
            out += "(-) ";
        }
        if (node->hasSplit()) {
            out += "Intermediate node with ";
            out += std::to_string(node->getDataFrame().length());
            out += " observation(s); split on column ";
            out += std::to_string(node->getSplitFeature());
            out += " with threshold ";
            out += std::to_string(node->getSplitThreshold());
            out += " .";
        } else {
            out += "LEAF NODE WITH ";
            out += std::to_string(node->getDataFrame().length());
            out += " OBSERVATION(S); ";
            if (this->isRegressionTree()){
                // Regression tree:
                out += "mean value: ";
                out += std::to_string(node->getDataFrame().col(-1).mean());
            } else {
                // Classification tree:
                out += "majority class: ";
                out += std::to_string(LabelCounter(node->getDataFrame().col(-1)).get_most_frequent());
            }
            out += " .";
        }
        out += "\n";
    }
    return out;
}

void DecisionTree::print() const
{
    /** Print the DecisionTree. */
    std::cout << this->to_string() << std::endl;
}

// Overloaded operators:

std::ostream& operator<<(std::ostream& os, const DecisionTree& tree)
{
    /** Print the DecisionTree to stream */
    os << tree.to_string();
    return os;
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

std::pair<int,double> DecisionTree::findBestSplit(TreeNode *node)
{
    /** Find best split at this node. */
    DataFrame dataframe = node->getDataFrame();
    // Must have enough data to split
    assert (dataframe.length()>1);
    std::pair<int,double> split;
    // Vector of indices which may or may not be shuffled.
    std::vector<int> shuf_inds(this->num_features_);
    // Create vector of column indices, equivalent to np.arange(0, df.shape[-1])
    std::generate(shuf_inds.begin(), shuf_inds.end(), [n = 0] () mutable { return n++; });
    // Shuffle if mtry_ < num_features_ else deterministic
    if (this->mtry_ < this->num_features_) {
        // Set changing random generator (arrow of time is inexorable!)
        srand((unsigned) this->seed_gen.new_seed());
        // Shuffle it:
        for (int i = 0; i < this->num_features_; i++){
            std::swap(shuf_inds[i], shuf_inds[i+(std::rand() % (this->num_features_-i))]);
        }
    }
    // Initialize temporary variables:
    bool first_pass = true;
    int best_column = -1; 
    int col;
    double best_threshold = -1.0;
    double best_loss, loss;
    // Explore possible splits:
    for (int i = 0; i < this->mtry_; i++){
        col = shuf_inds[i];
        std::vector<double> col_vals = dataframe.col(col).vector();
        // Remove duplicates:
        std::sort(col_vals.begin(), col_vals.end());
        col_vals.erase(std::unique(col_vals.begin(), col_vals.end()), col_vals.end());
        // For each unique column value, try that col and val as split, get score:
        for (int j = 0; j < col_vals.size()-1; j++){
            // Don't split on last value (because it will produce empty `right`).
            double val = col_vals[j];
            // But splitting on first value works as <= means left won't be empty
            // Split dataset using current column and threshold, score, and update if best:
            // equal_goes_left=true.
            std::vector<DataFrame> dataset_splits = dataframe.split(col, val, true);
            loss = this->calculateSplitLoss(&dataset_splits[0],&dataset_splits[1]);
            if ((first_pass) or (loss<best_loss)){
                first_pass = false;
                best_column = col;
                best_threshold = val;
                best_loss = loss;
            }
        }
    }
    // Placeholder value should have been replaced.
    // assert (best_column!=-1);
    split = std::make_pair(best_column, best_threshold);
    return split;
}

void DecisionTree::fit_(TreeNode* node)
{
    DataFrame dataframe = node->getDataFrame();
    LabelCounter label_counter = LabelCounter(dataframe.col(-1));
    double proportion = label_counter.get_values().max()/label_counter.size();
    if ( label_counter.size()==1 ) {
        return;  // Prune if there is only one class left.
    } else if ( dataframe.length()<2 ) {
        return;  // Prune if there is not enough data to split.
    } else if ( (this->max_height_!=-1) and (node->getDepth()+1>=this->max_height_) ) {
        return;  // Prune if adding children would exceed max depth:
    } else if ( (this->max_leaves_!=-1) and (this->num_leaves_+1>=this->max_leaves_) ) {
        return;  // Prune if adding children would exceed max leaves:
    } else if ( (this->min_obs_!=-1) and (dataframe.length()<=this->min_obs_) ) {
        return;  // Prune if node is below minimum leave size.
    } else if ( (this->max_prop_!=-1) and (  proportion>=this->max_prop_) ) {
        return;  // Prune if proportion of majority label is above threshold.
    }
    // Find best split at this node:
    std::pair<int,double> split = this->findBestSplit(node);
    int split_feature = split.first;
    double split_threshold = split.second;
    // To handle scenario where all columns within mtry have just 1 unique value
    if (split_feature == -1 && split_threshold == -1.0)
    {
        return;
    }
    node->setSplitFeature(split_feature);
    node->setSplitThreshold(split_threshold);
    // Calculate results of best split:
    std::vector<DataFrame> dataset_splits = dataframe.split(split_feature,split_threshold,true);  // equal_goes_left=true.
    DataFrame left_data = dataset_splits[0];
    DataFrame right_data = dataset_splits[1];
    if ( (left_data.length()==0) or (right_data.length()==0) ) {
        return;  // Prune if best split does not actually split the dataset.
    }
    // If split produces two non-empty dataframes, recurse to (new) children:
    this->num_leaves_ += 1;  // Each split causes net addition of 1 leaf.
    TreeNode *left_child = new TreeNode(left_data);
    TreeNode *right_child = new TreeNode(right_data);
    node->setLeft(left_child);
    node->setRight(right_child);
    // Recurse to (new) children:
    this->fit_(left_child);
    this->fit_(right_child);
}

double DecisionTree::predict_(DataVector* observation) const
{
    /** Helper function to perform prediction on a single observation. */
    TreeNode* node = this->root_;
    // Starting at root node, traverse tree while going left or right according to trained splitting criteria:
    while (!node->isLeaf())
    {
        int split_feature = node->getSplitFeature();
        double split_threshold = node->getSplitThreshold();
        if ( observation->value(split_feature) <= split_threshold ){
            assert (node->hasLeft());  // A non-leaf node should have both left and right children.
            node = node->getLeft();
        } else {
            assert (node->hasRight());  // A non-leaf node should have both left and right children.
            node = node->getRight();
        }
    }
    // Make prediction based on whichever leaf is reached by the traversal:
    double prediction;
    if (this->isRegressionTree()) {
        // Regression tree: Predict mean of training data at terminal node:
        prediction = node->getDataFrame().col(-1).mean();
    } else {
        // Classification tree: Predict majority class of training data at terminal node:
        prediction = LabelCounter(node->getDataFrame().col(-1)).get_most_frequent();
    }
    return prediction;
}
DataVector DecisionTree::predict(DataFrame* testdata) const
{
    /** Perform prediction sequentially on each observation and collect a vector of predictions. */
    DataVector predictions = DataVector(false);  // is_row=false.
    // Make sure tree has been fitted before prediction:
    assert (this->isFitted());
    // Make sure dataframe has the correct number of features (or one extra column with labels).
    assert ( (testdata->width()==this->num_features_) or (testdata->width()==this->num_features_+1) );
    for (int i = 0; i < testdata->length(); i++)
    {
        DataVector* observation = testdata->row(i);
        double prediction = this->predict_(observation);
        predictions.addValue(prediction);
    }
    return predictions;
}
