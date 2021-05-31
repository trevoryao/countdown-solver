#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include <future>
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
    void solve_k(std::ostream *os, int k, std::promise<int> &&p);
};
}

#endif
