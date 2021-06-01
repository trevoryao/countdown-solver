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
    vector<future<int>> futures;
    if (!config.pretty_print) os << '[';

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
    if (!config.pretty_print) os << ']';
    return solved;
}

int Problem::solve_k(ostream &os, int k) {
    int solved = 0;
    vector<int> thread_numbs{numbers};

    do {
        // possible splitting : 
        // generate (k-2) ops and tag on first op for each
        Generator gen{ops, static_cast<size_t>(k - 1)};
        do {
            // os << "current numbs:";
            // for (auto it = thread_numbs.begin(); it != thread_numbs.begin() + k; ++it) os << *it << " ";
            // os << endl << "current ops:";
            // for (auto &n : gen.get_word()) os << n << " ";
            // os << endl;
            
            auto exp_nodes = create_expressions(thread_numbs.begin(), thread_numbs.begin() + k,
                gen.get_word().begin(), gen.get_word().end());

            for (auto &exp_node : exp_nodes) {
                Expression exp{move(exp_node)};

                try {
                    if (exp.is_solution(target)) {
                        if (config.pretty_print) exp.output_pretty(os);
                        else {
                            if (solved) os << ',';
                            os << '"';
                            exp.output_json(os);
                            os << '"';
                        }
                        ++solved;
                    }
                } catch (ExpressionException) { }
            }
        } while (gen.next_word());
    } while (next_k_permutation(thread_numbs.begin(), thread_numbs.end(), k));
    return solved;
}
}
