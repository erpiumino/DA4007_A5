//Reminder on usage:
// slm (-a a) k input.txt char_number

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <stdexcept>
#include "functions.h"

using namespace std;

int main(int argc, char* argv[]){
    try{
        double a;
        int k;

        //1 Check number of inputs
        if (argc != 4 && argc != 6)
            throw invalid_argument("invalid number of arguments.\nExample of usage:" + string(argv[0]) + " (-a a) k input.txt char_number");
        
        //2 Check if -a flag is present and the value of a 
        if (argc == 6 && string(argv[1]) == "-a")
            a = parse_a(argv[2]);
        if (argc == 6 && string(argv[1]) != "-a")
            throw invalid_argument("unkown option. Expected -a, got '" + string(argv[1]) + "' instead");

        //3 Check the value of k
        

        //3 Assign file name at the right option based on the usage
        char* file_option = (argc == 4) ? argv[2] : argv[4];
        ifstream file(file_option);
        if (!file)
            throw runtime_error("cannot open file '" + string(argv[2]) + "'");
    }
    catch(const exception& error){
        cerr << "slm: " << error.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}