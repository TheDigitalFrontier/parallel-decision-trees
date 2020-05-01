#ifndef DECISION_TREE_HPP
#define DECISION_TREE_HPP

class DecisionTree
{
private:

    // Attributes:
    TreeNode *root_;

public:

    // Constructors:
    DecisionTree();
    DecisionTree(TreeNode *root);

    // Getters:
    int getSize() const;
    int getHeight() const;
    TreeNode * getRoot() const;

    // Setters:
    void setRoot(TreeNode *root);

    // Utilities:

};

#endif
