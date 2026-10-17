#pragma once
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <cmath>

class Vocabulary{

private:
    size_t k_;
    double a_;
    std::string file_tot_;
    std::string c_;
    std::vector<int> frequency_; //n(w)
    std::vector<std::string> k_gram_; //w
    std::vector<std::string> followers_;
    std::vector<double> probabilities; //P(c|w)

public:
    // Constructor
    Vocabulary(size_t k, double a, std::string total_file);

    // Methods
    void kgram();
    void alphabet();
    void freq_foll();
    std::string generate(size_t output_length, std::default_random_engine& rng) const;
};