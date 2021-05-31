// parse through arguments
// format:
// countdown-solver [options] -t <target> -n <5 numbers>
// countdown-solver [options] -n <5 numbers> (CECIL will generate target)
// countdown-solver [options] -t <target> -b <# of big'uns> -l <# of little ones>
// countdown-solver [options] -b <# of big'uns> -l <# of little ones> (CECIL will generate)
// ^ standard countdown rules apply
// options:
// -j : json
// -s : shortest solution
// -o <file-name> : output to file
#include <algorithm>
#include <boost/program_options.hpp>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "config.h"
#include "expression.h"
#include "problem.h"
#include "utils.h"

using namespace std;

using namespace boost::program_options;
using namespace Countdown;

int generateTarget() {
    int target;
    
    cout << "CECIL is generating target....." << endl;
    for (int i = 0; i < 5; ++i)
        target = (rand() % 899) + 100;
    cout << "Your target is " << target << "." << endl;

    return target;
}

int generateNums(int b, int l, vector<int> &nums) {
    vector<int> biguns = {25, 50, 75, 100};
    vector<int> littluns = {1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9};

    default_random_engine rng;

    if (b + l == 6 && (0 <= b && b <= 4)) {
        cout << "Shuffling cards....." << endl;
        for (int i = 0; i < 5; ++i) {
            shuffle(biguns.begin(), biguns.end(), rng);
            shuffle(littluns.begin(), littluns.end(), rng);
        }
        
        for (int k = 0; k < b; ++k) {
            int i = rand() % biguns.size();
            nums.emplace_back(biguns[i]);
            biguns.erase(biguns.begin() + i);
        }
        
        for (int k = 0; k < l; ++k) {
            int i = rand() % littluns.size();
            nums.emplace_back(littluns[i]);
            littluns.erase(littluns.begin() + i);
        }

        cout << "Your numbers are: ";
        for (auto &n : nums) cout << n << " ";
        cout << endl;
        return 0;
    } else {
        cerr << "Invalid numbers request -- use --help for more information." << endl;
        return 2;
    }
}

int main(int argc, char *argv[]) {
    options_description desc{"Options"};
    desc.add_options()
        ("help,h", "Help Screen")
        ("target,t", value<int>(),  "Target")
        ("numbers,n", value<vector<int>>()->multitoken(), "5 numbers")
        ("biguns,b", value<int>(), "# of biguns (must be 5 - littluns)")
        ("littluns,l", value<int>(), "# of littluns (must be 5 - biguns)")
        ("json,j", "print in json format")
        ("out,o", value<string>(), "output to file");

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help")) {
        cout << "Welcome to the Countdown Numbers Game solver!" << endl;
        cout << "countdown-solver [options] -t <target> -n <5 numbers>" << endl;
        cout << "countdown-solver [options] -n <5 numbers> (CECIL will generate target)" << endl;
        cout << "countdown-solver [options] -t <target> -b <# of big'uns> -l <# of little ones>" << endl;
        cout << "countdown-solver [options] -b <# of big'uns> -l <# of little ones> (CECIL will generate)" << endl;
        cout << desc << endl;
        return 0;
    }
    
    // parse options
    Config config;
    
    if (vm.count("json"))
        config.pretty_print = false;
    if (vm.count("out"))
        config.filename = vm["out"].as<string>();

    // run command
    int target;
    vector<int> nums;

    srand(static_cast<unsigned>(time(0)));

    if (vm.count("target") && vm.count("numbers")) {
        target = vm["target"].as<int>();
        nums = vm["numbers"].as<vector<int>>();

        if (nums.size() != 5) {
            cerr << "Incorrect amount of numbers entered! There must be 5." << endl;
            return 2;
        } else if (!(100 <= target && target <= 999)) {
            cerr << "Target must be between 100 & 999." << endl;
            return 2;
        }
    } else if (vm.count("numbers")) {
        nums = vm["numbers"].as<vector<int>>();

        if (nums.size() != 5) {
            cerr << "Incorrect amount of numbers entered! There must be 5." << endl;
            return 2;
        }

        target = generateTarget();
    } else if (vm.count("target") && vm.count("biguns") && vm.count("littluns")) {
        target = vm["target"].as<int>();

        int b = vm["biguns"].as<int>();
        int l = vm["littluns"].as<int>();

        int ret = generateNums(b, l, nums);
        if (ret) return 2;
    } else if (vm.count("biguns") && vm.count("littluns")) {
        int b = vm["biguns"].as<int>();
        int l = vm["littluns"].as<int>();
        
        target = generateTarget();
        int ret = generateNums(b, l, nums);
        if (ret) return 2;
    } else {
        cerr << "Unknown Command Line arguments entered." << endl;
        cerr << "Use countdown-solver --help for more information." << endl;
        return 2;
    }

    Problem problem{nums, target, config};
    int solved;

    cout << "Looking for solutions....." << endl;
    
    if (config.filename.empty()) {
        solved = problem.solve(cout);
    } else {
        ofstream ofs{config.filename, ofstream::app};
        solved = problem.solve(ofs);
    }

    if (!config.pretty_print) cout << endl;
    
    if (solved) {
        cout << "Summary: Found " << solved << " solutions." << endl;
    } else {
        cout << "No solutions exist." << endl;
        return 1;
    }

    return 0;
}
