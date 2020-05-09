#ifndef RANDOM_FOREST_HPP
#define RANDOM_FOREST_HPP

#include "decision_tree.hpp"
#include "tree_node.hpp"
#include "datasets.hpp"
#include "losses.hpp"

class RandomForest
{
private:

    // Attributes:
    std::vector<DecisionTree> trees_;  // A list of fitted decision trees.
    int num_trees_;  // Number of treeds to fit.
    DataFrame dataframe_;  // Training data.
    bool regression_;  // Use regression==false for a classification tree.
    std::string loss_;  // String indicating loss function method.
    int mtry_;  // Hyperparameter: Number of features to use at each split (or -1 for all in deterministic order; or 0 for sqrt(n_columns) ).
    int max_height_;  // Stopping condition: max height of tree.
    int max_leaves_;  // Stopping condition: max number of leaves.
    int min_obs_;  // Stopping condition: minimum number of observations in a leaf.
    int max_prop_;  // Stopping condition: minimum proportion of majority class in a leaf.
    int num_features_;  // State variable: Number of features in dataset.
    bool fitted_;  // State variable: Flag indicated whether or not the random forest has been trained.
    int meta_seed_;  // Metaseed for random seed generator.
    SeedGenerator seed_gen;  // Random seed generator.

    // Utilities:
    void fit_();  // Perform fitting (using fit_ helper).

public:

    // Constructors:
    RandomForest(
        DataFrame dataframe, int num_trees, bool regression=false,
        std::string loss="gini_impurity", int mtry=-1, int max_height=-1,
        int max_leaves=-1, int min_obs=-1, double max_prop=-1, int seed=-1
    );

    // Getters:
    int getNumTrees() const;  // Number of trees in RandomForest.
    bool isRegressionTree() const;  // Type of tree (classification or regression).
    bool isFitted() const;  // Indicates whether the tree has been fitted on training data.
    std::vector<DecisionTree> getTrees() const;  // Get a vector of the fitted trees.
    DecisionTree getTree(int i) const;  // Get one of the fitted trees.
    DataFrame getDataFrame() const;  // Training data.

    // Setters:

    // Utilities:
    DataVector predict(DataFrame* testdata) const;  // Perform prediction sequentially on each observation.

};


#endif
