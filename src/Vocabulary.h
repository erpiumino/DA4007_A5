#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class Vocabulary{

private:
    int k_;
    double a_;
    std::string file_tot_;
    std::string c_;
    std::vector<int> frequency_; //n(w)
    std::vector<std::string> k_gram_; //w
    std::vector<std::string> followers_;
    std::vector<double> probabilities; //P(c|w)

public:
    // Constructor
    Vocabulary(int k, double a, std::string total_file);

    // Methods
    double probability();
};