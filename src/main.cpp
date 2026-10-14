//Reminder on usage:
// slm (-a a) k input.txt char_number

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <stdexcept>
#include "functions.h"
#include "Config.h"
#include "Vocabulary.h"

using namespace std;

int main(int argc, char* argv[]){
    try{

        //1 Error Handling with Config class
        Config config(argc, argv);

        //2 Algorithm
        //2.1 Initiate vocabulary class
        //Vocabulary voc(total_file);
        //voc.counting(k ,a);
    }
    catch(const exception& error){
        cerr << "slm: " << error.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}