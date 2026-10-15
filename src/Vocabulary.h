#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class Vocabulary{

private:
    int k_;
    std::string file_tot_;
    std::vector<int> frequency_; //n(w)
    std::vector<std::string> k_gram_; //w
    std::vector<std::string> followers_;
    std::vector<double> probabilities; //P(c|w)

public:
    // Constructor
    Vocabulary(int k, std::string total_file);

    // Methods
    void biagram();
    double probability();
};