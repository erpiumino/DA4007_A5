# DA4007_A5
Assignment 5 for Programming Techinques II course (DA4007).
This repository contains all files and dependencies for running a small LLM based on conditional probabilities.

## Usage

To use the tool, just run ```make``` in the repository directory and then the commando ```./slm``` followed by the following options:
* The (not mandatory) option for $\alpha$: ```-a [a]```
* The option for $k$: ```[k]```
* The input text, typically ```training/<filename.txt>```
* The number of output char $c$: ```[c]```
A ```clean``` function is also included in the make file. So a complete usage would be something like
```bash
make 
./slm -a 0.001 2 moby_dick.txt 100
make clean
```

## Pipeline
The code is based on two classes:```Config``` and ```Vocabulary```:
* The ```Config``` class contains all variables given in input by the user, and its main goal is to check the validity of these variables. It does it with direct checks like this one
```C++
if (argc != 4 && argc != 6)
  throw invalid_argument("invalid number of arguments.\nExample of usage:" + string(argv[0]) + " (-a a) k input.txt char_number\nFlag -a is not mandatory");
```
or by using public functions built in the class, like the ```parse``` functions:
```C++
int Config::parse_pos(const string& argv, string type){

    int k = -1;
    size_t size = 0;

    try{
        k = stoi(argv, &size);
    }catch (const exception&) {
        throw invalid_argument("option " + type + " requires a positive integer, got '" + argv + "' instead");
    }
    if (size != argv.size() || k<=0)
        throw invalid_argument("option " + type + " requires a positive integer, got '" + argv + "' instead");

    return k;
}
```
The ```Config``` class also has a set of methods, which are just public functions made in order to return the private variables and use them in the second class. This behavior was chosen (instead of defining variables in the main) as the check on the input and error handling is extremely simpler this way.
* The ```Vocabulary``` class, which was initially meant to just hold the variables needed to run the algorithm, is the entity that actually runs the main calculation and return the output. The class has a constructor that also initiates the main variables and vectors used in the algorithm, as ```k_gram_```, ```c_```, ```frequency_``` and ```followers_``` (this latter is the only variable that is not explicitly stated in the assignment text, as it is more of a helper variable). The string vectors are built with simple loops over the ```total_file_``` variable (which is just a long string with the whole input, constructed in the ```Config``` class), like for example:
```C++
void Vocabulary::kgram(){
    vector<string> control;
    for (int i=0; i+k_ <= file_tot_.size(); i++){
        control.push_back(file_tot_.substr(i, k_));
    }
    sort(control.begin(), control.end());
    for (int i=0; i< control.size(); i++){
        if (i == 0 || control[i] != control[i - 1])
                k_gram_.push_back(control[i]);
    }
}
```
After the variables are correctly (hopefully) built, the main algorithm just follows the conditionally probability equation 

$$
P(c \mid w)=\frac{n(w, c)+\alpha}{n(w)+\alpha|\Sigma|} \text { for every } c \in \Sigma 
$$ 

And it does so until the length of the output is equal to the input given by the user. This is hence implemented through a ```while``` loop over the size of the output:

```C++

string Vocabulary::generate(int output_length, std::default_random_engine& rng) const{

    discrete_distribution<int> start(frequency_.begin(), frequency_.end());
    string w = k_gram_[start(rng)];

    string out = w;

    while (out.size() < output_length) {

        int idx = lower_bound(k_gram_.begin(), k_gram_.end(), w) - k_gram_.begin();
        bool found = (idx < k_gram_.size() && k_gram_[idx] == w);

        vector<double> weights(c_.size(), a_);
        if (found)
            for (char f : followers_[idx])
                weights[c_.find(f)] += 1;

        if (a_ == 0 && (!found || followers_[idx].empty()))
            break;

        discrete_distribution<int> next(weights.begin(), weights.end());
        char c = c_[next(rng)];

        out += c;
        w = w.substr(1) + c;
    }
    return out;

}
```

Putting all of this together, the main file looks very slim, as it only initialise the classes and print the output (this is only part of the main):

```C++
//1 Error Handling with Config class
Config config(argc, argv);

//2 Algorithm
Vocabulary vocab(config.get_k(), config.get_a(), config.get_file_tot());
random_device rd;
default_random_engine rng(rd());
cout << vocab.generate(config.get_length(), rng) << endl;
```