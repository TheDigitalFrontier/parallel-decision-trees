#ifndef DECISION_TREE_HPP
#define DECISION_TREE_HPP

#include "tree_node.hpp"
#include "datasets.hpp"
#include "losses.hpp"
#include <utility>  // std::pair, std::make_pair

class DecisionTree
{
private:

    // Attributes:
    TreeNode *root_;  // Root node.
    DataFrame dataframe_;  // Training data.
    bool regression_;  // Use regression==false for a classification tree.
    std::string loss_;  // String indicating loss function method.
    int mtry_;  // Hyperparameter: Number of features to use at each split (or -1 for all in deterministic order; or 0 for sqrt(n_columns) ).
    int max_height_;  // Stopping condition: max height of tree.
    int max_leaves_;  // Stopping condition: max number of leaves.
    int num_leaves_;  // State variable: Number of leaves currently in tree.
    int num_features_;  // State variable: Number of features in dataset.
    std::vector<TreeNode*> leaves_;  // State variables: List of leaves.

    // Utilities:
    void fit_(TreeNode* node);  // Helper function to perform fitting recursively.
    std::pair<int,double> findBestSplit(TreeNode *node) const;  // Find best split at this node.
    double calculateLoss(DataFrame* dataframe) const;  // Calculate loss before split.
    double calculateSplitLoss(DataFrame* left_dataframe, DataFrame* right_dataframe) const;  // Calculate loss on split dataset.

public:

    // Constructors:
    DecisionTree(DataFrame dataframe, bool regression, std::string loss, int mtry=-1, int max_height=-1, int max_leaves=-1);

    // Getters:
    int getSize() const;  // Number of nodes in tree.
    int getHeight() const;  // Height of tree.
    bool isRegressionTree() const;  // Type of tree (classification or regression).
    TreeNode * getRoot() const;  // Root node in tree.
    std::vector<TreeNode*> getLeaves();  // Get leaves.
    DataFrame getDataFrame() const;  // Training data.

    // Setters:

    // Utilities:
    void fit();  // Perform fitting recursively (using fit_ helper).

};

#endif
