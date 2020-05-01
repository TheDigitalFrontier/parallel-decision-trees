#include <iostream>
#include "losses.cpp"
#include "datasets.cpp"

int main(){

    std::cout << "Loading test dataset." << std::endl;
    DataLoader test_loader = DataLoader();
    DataFrame test_data = test_loader.load();
    test_data.print();
    
    std::cout << "Calculate loss (with itself)." << std::endl;
    DataVector y_true = *test_data.col(-1);
    DataVector y_pred = *test_data.col(-1);
    std::cout << y_true << std::endl;
    LossFunction loss_func = LossFunction("gini_impurity");
    double test_loss = loss_func.calculate(y_true,y_pred);
    std::cout << test_loss << std::endl;

    return 0;
};
