#/bin/bash

# Tests
g++-9 -std=c++14 -g3 ../tests/test_tree_node.cpp -o test_tree_node
g++-9 -std=c++14 -g3 ../tests/test_datasets.cpp -o test_datasets
g++-9 -std=c++14 -g3 ../tests/test_decision_tree.cpp -o test_decision_tree
g++-9 -std=c++14 -g3 ../tests/test_losses.cpp -o test_losses
g++-9 -std=c++14 -g3 ../tests/test_random_forest.cpp -o test_random_forest

# Speedup scripts
g++-9 -std=c++14 -O0 ../speedup/rf_serial.cpp -o rf_serial
g++-9 -std=c++14 -O0 -fopenmp ../speedup/rf_openmp.cpp -o rf_openmp