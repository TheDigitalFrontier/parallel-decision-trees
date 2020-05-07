#include <iostream>
#include "../src/losses.cpp"
#include "../src/datasets.cpp"

int main(){

    std::cout << "Create label and add test labels." << std::endl;
    LabelCounter label_counter1 = LabelCounter();
    label_counter1.increment(333);
    label_counter1.increment(20);
    label_counter1.increment(20);
    label_counter1.increment(21);
    label_counter1.increment(21);
    std::cout << "Number of labels: " << label_counter1.size() << std::endl;
    std::cout << "Total occurrences: " << label_counter1.total_size() << std::endl;
    std::cout << "Counts: " << label_counter1 << std::endl;
    std::cout << "Most frequent key: " << label_counter1.get_most_frequent() << std::endl;
    std::cout << std::endl;
    std::cout << "Labels: " + label_counter1.get_labels().transpose().to_string(false);
    std::cout << "Values: " + label_counter1.get_values().transpose().to_string(false);
    std::cout << "Counts: " << label_counter1 << std::endl;
    std::cout << std::endl;

    std::cout << "Reset counter." << std::endl;
    label_counter1.reset();
    std::cout << "Number of labels: " << label_counter1.size() << std::endl;
    std::cout << "Total occurrences: " << label_counter1.total_size() << std::endl;
    std::cout << "Counts: " << label_counter1 << std::endl;
    std::cout << std::endl;

    std::cout << "Loading test dataset." << std::endl;
    DataLoader test_loader = DataLoader();
    DataFrame test_data = test_loader.load();
    test_data.print();

    std::cout << "Create label counter for last column." << std::endl;
    LabelCounter label_counter2 = LabelCounter(test_data.col(-1));
    std::cout << "Number of labels: " << label_counter2.size() << std::endl;
    std::cout << "Total occurrences: " << label_counter2.total_size() << std::endl;
    std::cout << "Counts: " << label_counter2 << std::endl;
    std::cout << std::endl;
    
    std::cout << "Calculate loss (test 1)." << std::endl;
    DataVector labels = DataVector({1,0,1,0,1,1,0});
    std::cout << labels << "Counts : " << LabelCounter(labels) << std::endl;
    LossFunction loss_func_misclass = LossFunction("misclassification_error");
    double loss_misclass = loss_func_misclass.calculate(labels);
    std::cout << "Misclassification rate ( 3/7 ): " + std::to_string(loss_misclass) << std::endl;
    double loss_gini = LossFunction("gini_impurity").calculate(labels);
    std::cout << "Gini impurity ( 3/7*(1-3/7) + 4/7*(1-4/7) ): " + std::to_string(loss_gini) << std::endl;
    double loss_entropy = LossFunction("cross_entropy").calculate(labels);
    std::cout << "Binary cross-entropy ( -( 4/7*log2(4/7) + 3/7*log2(3/7) ) ): " + std::to_string(loss_entropy) << std::endl;
    double loss_mse = LossFunction("mean_squared_error").calculate(labels);
    std::cout << "Mean squared error ( ( 4 * (1-4/7)^2 + 3 * (0-4/7)^2 )/7 ): " + std::to_string(loss_mse) << std::endl;
    std::cout << std::endl;
    
    std::cout << "Calculate loss (test 2)." << std::endl;
    DataVector labels2 = DataVector({1,1,1,1,1,2,2,2,2,2,2,2,2});
    std::cout << labels2 << "Counts : " << LabelCounter(labels2) << std::endl;
    double loss_entropy2 = LossFunction("cross_entropy").calculate(labels2);  // count(1)=5, count(2)=8.
    std::cout << "Binary cross-entropy ( -( 5/13*log2(5/13) + 8/13*log2(8/13) ) ): " + std::to_string(loss_entropy2) << std::endl;
    std::cout << std::endl;

    return 0;
};
