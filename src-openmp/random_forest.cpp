#include "random_forest.hpp"
#include "decision_tree.hpp"
#include "tree_node.hpp"
#include "datasets.hpp"
#include "losses.hpp"
#include <assert.h>
#include <iostream>
#include <omp.h>

// Constructors:
RandomForest::RandomForest(
    DataFrame dataframe, int num_trees, bool regression, std::string loss, int mtry,
    int max_height, int max_leaves, int min_obs, double max_prop, int seed
)
{
    /**
     * Initialize a RandomForest with given training set and hyperparameters.
     *    dataframe  : Training data (with class labels in right-most column).
     *    num_trees  : Number of trees to fit.
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
    assert ((num_trees>0));  // Number of trees must be non-zero.
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
    // Set properties from inputs:
    this->dataframe_ = dataframe;
    this->num_features_ = dataframe.width()-1;  // Number of columns, excluding label column.
    this->num_trees_ = num_trees;
    this->regression_ = regression;
    this->loss_ = loss;
    this->mtry_ = (mtry==-1) ? int(std::floor(sqrt(this->num_features_))) : mtry;
    this->max_height_ = max_height;
    this->max_leaves_ = max_leaves;
    this->min_obs_ = min_obs;
    this->max_prop_ = max_prop;
    this->meta_seed_ = seed;  // Metaseed for random seed generator.
    // Initialize:
    this->fitted_ = false;
    this->seed_gen = SeedGenerator(this->meta_seed_);
    // Perform training:
    this->fit_();
};

// Getters:
int RandomForest::getNumTrees() const
{
    /** Number of trees in RandomForest. */
    return this->trees_.size();
}

bool RandomForest::isRegressionTree() const
{
    /** Type of tree (classification or regression). */
    return this->regression_;
}

bool RandomForest::isFitted() const
{
    /** Indicates whether the tree has been fitted on training data. */
    return this->fitted_;
}

std::vector<DecisionTree> RandomForest::getTrees() const
{
    /** Get a vector of the fitted trees. */
    assert (this->isFitted());
    return this->trees_;
}

DecisionTree RandomForest::getTree(int i) const
{
    /** Get one of the fitted trees. */
    assert (i>=0);
    assert (i<this->trees_.size());
    assert (this->isFitted());
    return this->trees_[i];
}

DataFrame RandomForest::getDataFrame() const
{
    /** Training data. */
    return this->dataframe_;
}


// Setters:

// Utilities:

void RandomForest::fit_()
{
    /** Fit RandomForest with given parameters. */
    this->trees_ = {};
    int i;
    // Initialize vectors with seed values
    std::vector<int> data_seed_vector;
    std::vector<int> tree_seed_vector;
    // Pre-fill vectors with seed values
    for(int j=0; j < this->num_trees_; j++){
        data_seed_vector.push_back(this->seed_gen.new_seed());
        tree_seed_vector.push_back(this->seed_gen.new_seed());
    }
    // Create a team of threads for parallel execution
    #pragma omp parallel shared(data_seed_vector, tree_seed_vector) private(i)
    {
        if ((int)omp_get_thread_num() == 0){
            int nthreads = (int)omp_get_num_threads();
            std::cout << "nthreads: " << nthreads << std::endl;
        }
        // Execute for loop in parallel
        #pragma omp for schedule(dynamic)
        for (i = 0; i < this->num_trees_; i++){
            int data_seed = data_seed_vector[i];
            int tree_seed = tree_seed_vector[i];
            DataFrame bootstrap = this->dataframe_.sample(-1, data_seed, true);
            DecisionTree tree = DecisionTree(
                bootstrap, this->regression_, this->loss_, this->mtry_,
                this->max_height_, this->max_leaves_, this->min_obs_, this->max_prop_, tree_seed
            );
            this->trees_.push_back(tree);
        }
    }
    this->fitted_ = true;
}

DataVector RandomForest::predict(DataFrame* testdata) const
{
    /** Perform prediction sequentially on each observation and collect a vector of predictions. */
    DataVector predictions = DataVector(false);  // is_row=false.
    // Make sure tree has been fitted before prediction:
    assert (this->isFitted());
    // Make sure dataframe has the correct number of features (or one extra column with labels).
    assert ( (testdata->width()==this->num_features_) or (testdata->width()==this->num_features_+1) );
    // Create DataFrame to store predictions (one row per observation, one column per decision tree):
    DataFrame ensemble_predicions = DataFrame();  // Will delete rows from heap once predictions have been aggregated.
    for (int i = 0; i < this->trees_.size(); i++)
    {
        DataVector tree_predictions = this->trees_[i].predict(testdata);
        ensemble_predicions.addCol(tree_predictions.vector());
    }
    // Aggregate ensemble predictiosn:
    DataVector *observation_predictions;
    double prediction;
    for (int j = 0; j < ensemble_predicions.length(); j++)
    {
        observation_predictions = ensemble_predicions.row(j);
        if (this->isRegressionTree()) {
            // Regression tree: Predict mean of ensemble predictions:
            prediction = observation_predictions->mean();
        } else {
            // Classification tree: Predict majority class of ensemble predictions:
            prediction = LabelCounter(observation_predictions).get_most_frequent();
        }
        // Add prediction made by ensemble for this observation:
        predictions.addValue(prediction);
    }
    // Remove rows from heap:
    for (int k = 0; k < ensemble_predicions.length(); k++)
    {
        delete ensemble_predicions.row(k);  // Delete rows that were added to heap by this function.
    }
    // Return result:
    return predictions;
}
