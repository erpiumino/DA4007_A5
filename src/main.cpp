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

        //2 Algorithm
        Vocabulary vocab(config.get_k(), config.get_a(), config.get_file_tot());
        random_device rd;
        default_random_engine rng(rd());
        cout << vocab.generate(config.get_length(), rng) << endl;

    }
    catch(const exception& error){
        cerr << "slm: " << error.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}