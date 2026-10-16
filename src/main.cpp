//Reminder on usage:
// slm (-a a) k input.txt char_number

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <stdexcept>
#include "Config.h"
#include "Vocabulary.h"

using namespace std;

int main(int argc, char* argv[]){
    try{

        //1 Error Handling with Config class
        Config config(argc, argv);
        //1.1 Get variables from configuration
        int k = config.get_k();
        double a = config.get_a();
        string file_tot = config.get_file_tot();

        //2 Algorithm
        //2.1 Initiate vocabulary class 
        Vocabulary vocab(k, a, file_tot);
        //2.3 Run algorithm and get output

    }
    catch(const exception& error){
        cerr << "slm: " << error.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}