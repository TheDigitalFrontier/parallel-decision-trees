Mac apparently aliases g++ with gclang++, so when you call g++ you are in fact calling gclang++.

To run OpenMP on Mac:
1. brew install gcc
2. g++-9 -std=c++14 -O0 -fopenmp ../speedup/rf_openmp.cpp -o rf_openmp
3. time ./rf_openmp
