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
    int min_obs_;  // Stopping condition: minimum number of observations in a leaf.
    int max_prop_;  // Stopping condition: minimum proportion of majority class in a leaf.
    int num_leaves_;  // State variable: Number of leaves currently in tree.
    int num_features_;  // State variable: Number of features in dataset.
    std::vector<TreeNode*> leaves_;  // State variables: List of leaves.
    bool fitted_;  // State variable: Flag indicated whether or not the tree has been trained.
    int meta_seed_;  // Metaseed for random seed generator.
    SeedGenerator seed_gen;  // Random seed generator.

    // Utilities:
    void fit_(TreeNode* node);  // Helper function to perform fitting recursively.
    double predict_(DataVector* observation) const;  // Helper function to perform prediction on a single observation.
    std::pair<int,double> findBestSplit(TreeNode *node);  // Find best split at this node.
    double calculateLoss(DataFrame* dataframe) const;  // Calculate loss before split.
    double calculateSplitLoss(DataFrame* left_dataframe, DataFrame* right_dataframe) const;  // Calculate loss on split dataset.

public:

    // Constructors:
    DecisionTree(
        DataFrame dataframe, bool regression=false, std::string loss="gini_impurity",
        int mtry=-1, int max_height=-1, int max_leaves=-1, int min_obs=-1,
        double max_prop=-1, int seed=-1
    );

    // Getters:
    int getSize() const;  // Number of nodes in tree.
    int getHeight() const;  // Height of tree.
    bool isRegressionTree() const;  // Type of tree (classification or regression).
    bool isFitted() const;  // Indicates whether the tree has been fitted on training data.
    TreeNode * getRoot() const;  // Root node in tree.
    std::vector<TreeNode*> getLeaves();  // Get leaves.
    DataFrame getDataFrame() const;  // Training data.
    std::string to_string() const;  // Return the DecisionTree as a string.
    void print() const;  // Print the DecisionTree.

    // Overloaded operators:
    friend std::ostream& operator<<(std::ostream& os, const DecisionTree& tree);

    // Setters:

    // Utilities:
    DataVector predict(DataFrame* testdata) const;  // Perform prediction sequentially on each observation.

};

#endif
