#include "Config.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor and file length check
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Config::Config(int argc, char* argv[]) : k_(0), a_(0), file_tot_(""){

    //1.1 Check number of inputs
    if (argc != 4 && argc != 6)
        throw invalid_argument("invalid number of arguments.\nExample of usage:" + string(argv[0]) + " (-a a) k input.txt char_number\nFlag -a is not mandatory");
    
    //1.2 Check if -a flag is present and the value of a 
    if (argc == 6 && string(argv[1]) == "-a")
        a_ = parse_a(argv[2]);
    if (argc == 6 && string(argv[1]) != "-a")
        throw invalid_argument("unkown option. Expected -a, got '" + string(argv[1]) + "' instead");

    //1.3 Check the value of k
    k_ = (argc == 4) ? parse_pos(argv[1]) : parse_pos(argv[3]);

    //1.4 Assign file name at the right option based on the usage
    char* file_option = (argc == 4) ? argv[2] : argv[4];
    ifstream file(file_option);

    //1.5 Check if the opening goes right
    if (!file)
        throw runtime_error("cannot open file '" + string(file_option) + "'");
    
    //1.6 Check file total length
    file_tot_ = read_all(file);
    if (file_tot_.length() < k_+1)
        throw runtime_error("training text too short, must contain " + to_string(k_+1) + " chars at least, " + to_string(file_tot_.length()) + " found instead");

    //1.7 Assign length of output and check it's bigger thank k
    length_ = (argc == 4) ? parse_pos(argv[3]) : parse_pos(argv[5]);
    if (length_ < k_)
        throw invalid_argument("invalid output length number. Expected bigger than " + to_string(k_) + ", got " + to_string(length_) + " instead"); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Config::parse_a(const string& argv){

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

int Config::parse_pos(const string& argv){

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string Config::read_all(ifstream& file){
    
    string lines, tot;
    while(getline(file, lines)){
        tot+=lines;
        if (!file.eof())
            tot+='\n';
    }
    return tot;
}