#include "problem.h"

#include <algorithm>
#include <functional>
#include <future>
#include <sstream>
#include <thread>
#include <utility>

#include "utils.h"

using namespace std;

namespace Countdown {
const vector<char> Problem::ops = {'+', '-', '*', '/'};

Problem::Problem(const vector<int> &numbers, int target, Config config) :
    numbers{numbers}, target{target}, config{config} {
    sort(this->numbers.begin(), this->numbers.end());
}

int Problem::solve(ostream &os) {
    // vector<thread> threads;
    // vector<promise<int>> promises;
    vector<future<int>> futures;

    for (int k = 1; k <= numbers.size(); ++k) {
        futures.emplace_back(async([this, &os, k] {
            stringstream ss;
            int solved = solve_k(ss, k);
            os << ss.str();
            return solved;
        }));
    }

    int solved = 0;
    for (auto &f : futures) solved += f.get();
    return solved;
}

int Problem::solve_k(ostream &os, int k) {
    int solved = 0;

    vector<int> thread_numbs{numbers};

    do {
        // something with first k numbers
        // generate k - 1 operators
        Generator gen{ops, static_cast<size_t>(k - 1)};
        do {
            try { // current issue with k = 1
                Expression exp{thread_numbs.begin(), thread_numbs.begin() + k,
                    gen.get_word().begin(), gen.get_word().end()};

                if (exp.is_solution(target)) {
                    if (config.pretty_print) exp.output_pretty(os);
                    else exp.output_json(os);
                    ++solved;
                }
            }
            catch (ExpressionDivException) { }
        } while (gen.next_word());
    } while (next_k_permutation(thread_numbs.begin(), thread_numbs.end(), k));

    return solved;
}
}
