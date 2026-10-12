#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <cstdlib>
#include <stdexcept>

using namespace std;

double parse_a(const string& argv);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double parse_a(const string& argv){

    double a = 0.0;
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