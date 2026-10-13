#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class Vocabulary{

private:
    int k_;
    std::string total_file_;
    std::vector<int> frequency_;
    std::vector<std::string> k_gram_;
    std::vector<std::string> followers_;

public:
    // Constructor
    Vocabulary(int k, std::string total_file);

    // Methods
    void counting();
};