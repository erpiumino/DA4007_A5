#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

class Config{

private:
    size_t k_;
    double a_;
    std::string file_tot_;
    size_t length_;

    double parse_a(const std::string& argv);
    int parse_pos(const std::string& argv, std::string type = "");
    std::string read_all(std::ifstream& file);

public:
    // Constructor
    Config(int argc, char* argv[]);

    // Methods (to get variables)
    int         get_k()         const { return k_; }
    double      get_a()         const { return a_; }
    std::string get_file_tot()  const { return file_tot_; }
    int         get_length()    const { return length_; }
};