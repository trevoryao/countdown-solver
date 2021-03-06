#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include <iostream>
#include <string>
#include <vector>

#include "config.h"
#include "expression.h"

namespace Countdown {
class Problem {
private:
    std::vector<int> numbers;
    int target;
    Config config;

    static const std::vector<char> ops;
public:
    Problem(const std::vector<int> &numbers, int target, Config config);
    int solve(std::ostream &os);
private:
    int solve_k(std::ostream &os, int k, const int &global_solved); // use for k in [1, 3]
    int solve_k_large(std::ostream &os, int k,
        const char op, const int &global_solved); // use for k in [4, 6]
};
}

#endif
