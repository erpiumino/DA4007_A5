#include "Vocabulary.h"
#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor. It also creates k_gram_ and alphabet_ vectors
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vocabulary::Vocabulary(size_t k, double a, string file_tot) : k_(k), a_(a), file_tot_(file_tot){
    //k_gram constructor
    kgram();
    //c (alphabet) constructor 
    alphabet();
    //frequency constructor 
    freq_foll();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Vocabulary::kgram(){
    vector<string> control;
    for (size_t i=0; i+k_ <= file_tot_.size(); i++){
        control.push_back(file_tot_.substr(i, k_));
    }
    sort(control.begin(), control.end());
    for (size_t i=0; i< control.size(); i++){
        if (i == 0 || control[i] != control[i - 1])
                k_gram_.push_back(control[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Vocabulary::alphabet(){
    string control = file_tot_;
    sort(control.begin(), control.end());

    for (size_t i=0; i< control.size(); i++){
        if (i == 0 || control[i] != control[i - 1])
                c_.push_back(control[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Vocabulary::freq_foll(){
    frequency_.assign(k_gram_.size(), 0);
    followers_.assign(k_gram_.size(), "");

    for (size_t i = 0; i + k_ <= file_tot_.size(); i++) {
        string w = file_tot_.substr(i, k_);
        size_t idx = lower_bound(k_gram_.begin(), k_gram_.end(), w) - k_gram_.begin();

        frequency_[idx]++;
        if (i + k_ < file_tot_.size())
            followers_[idx] += file_tot_[i + k_];
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string Vocabulary::generate(size_t output_length, std::default_random_engine& rng) const{

    discrete_distribution<int> start(frequency_.begin(), frequency_.end());
    string w = k_gram_[start(rng)];

    string out = w;

    while (out.size() < output_length) {

        size_t idx = lower_bound(k_gram_.begin(), k_gram_.end(), w) - k_gram_.begin();
        bool found = (idx < k_gram_.size() && k_gram_[idx] == w);

        vector<double> weights(c_.size(), a_);
        if (found)
            for (char f : followers_[idx])
                weights[c_.find(f)] += 1;

        if (a_ == 0 && (!found || followers_[idx].empty()))
            break;

        discrete_distribution<int> next(weights.begin(), weights.end());
        char c = c_[next(rng)];

        out += c;
        w = w.substr(1) + c;
    }
    return out;

}