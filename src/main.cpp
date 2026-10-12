//Reminder on usage:
// slm (-a a) k input.txt char_number

#include<iostream>
#include<fstream>
#include<random>
#include<cstdlib>
#include<stdexcept>

using namespace std;

int main(int argc, char* argv[]){
    try{
        ifstream file(argv[2]);
        if (!file)
            throw runtime_error("cannot open file '" + string(argv[2]) + "'");
    }
    catch(const exception& error){
        cerr << "slm: " << error.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}