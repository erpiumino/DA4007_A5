//Reminder on usage:
// slm (-a a) k input.txt char_number

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <stdexcept>
#include "functions.h"
#include "vocabulary.h"

using namespace std;

int main(int argc, char* argv[]){
    try{
        double a;
        int k;

        //1 Error Handling
        //1.1 Check number of inputs
        if (argc != 4 && argc != 6)
            throw invalid_argument("invalid number of arguments.\nExample of usage:" + string(argv[0]) + " (-a a) k input.txt char_number\nFlag -a is not mandatory");
        
        //1.2 Check if -a flag is present and the value of a 
        if (argc == 6 && string(argv[1]) == "-a")
            a = parse_a(argv[2]);
        if (argc == 6 && string(argv[1]) != "-a")
            throw invalid_argument("unkown option. Expected -a, got '" + string(argv[1]) + "' instead");

        //1.3 Check the value of k
        k = (argc == 4) ? parse_f(argv[1]) : parse_f(argv[3]);

        //1.4 Assign file name at the right option based on the usage
        char* file_option = (argc == 4) ? argv[2] : argv[4];
        ifstream file(file_option);

        //1.5 Check if the opening goes right
        if (!file)
            throw runtime_error("cannot open file '" + string(file_option) + "'");
        
        //1.6 Check if file is long enough
        string total_file = read_all(file);

        //2 Algorithm
        //2.1 Initiate vocabulary class
        Vocabulary voc(total_file);
        voc.counting(k ,a);
    }
    catch(const exception& error){
        cerr << "slm: " << error.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}