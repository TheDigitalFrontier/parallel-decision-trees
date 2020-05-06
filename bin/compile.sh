#/bin/bash

g++ -std=c++14 -g3 ../tests/test_tree_node.cpp -o test_tree_node
g++ -std=c++14 -g3 ../tests/test_datasets.cpp -o test_datasets
g++ -std=c++14 -g3 ../tests/test_decision_tree.cpp -o test_decision_tree
g++ -std=c++14 -g3 ../tests/test_losses.cpp -o test_losses
g++ -std=c++14 -g3 ../tests/test_random_forest.cpp -o test_random_forest
