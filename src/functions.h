#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <cstdlib>
#include <stdexcept>

using namespace std;

double parse_a(const string& argv);
int parse_f(const string& argv);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double parse_a(const string& argv){

    double a = -1; //In case something goes wrong with the stod, function shouldn't give a result anyway (I think)
    size_t size = 0;
    
    try{
        a = stod(argv, &size);
    }catch (const exception&) {
        throw invalid_argument("option -a requires a non-negative number, got '" + argv + "' instead");
    }
    if (size != argv.size() || a<0)
        throw invalid_argument("option -a requires a non-negative number, got '" + argv + "' instead");

    return a;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int parse_f(const string& argv){

    int k = -1;
    size_t size = 0;

    try{
        k = stoi(argv, &size);
    }catch (const exception&) {
        throw invalid_argument("option k requires a non-negative integer number, got '" + argv + "' instead");
    }
    if (size != argv.size() || k<0)
        throw invalid_argument("option k requires a non-negative integer number, got '" + argv + "' instead");

    return k;
}