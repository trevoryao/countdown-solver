#include "problem.h"

#include <algorithm>
#include <exception>
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
    int solved = 0;
    
    if (!config.pretty_print) os << '[';

    // k == 1 && k == 2
    futures.emplace_back(async([this, &os, &solved] {
        stringstream ss;
        int local_solved = solve_k(ss, 1, solved) + solve_k(ss, 2, solved);
        os << ss.str();
        return local_solved;
    }));

    // k == 3
    for (int k = 3; k <= 4; ++k) {
        futures.emplace_back(async([this, &os, k, &solved] {
            stringstream ss;
            int local_solved = solve_k(ss, k, solved);
            os << ss.str();
            return local_solved;
        }));
    }

    // k == 5 && k == 6
    for (int k = 5; k <= 6; ++k) {
        for (auto &op : ops) {
            futures.emplace_back(async([this, &os, k, op, &solved] {
                stringstream ss;
                int local_solved = solve_k_large(ss, k, op, solved);
                os << ss.str();
                return local_solved;
            }));
        }
    }

    for (auto &f : futures) solved += f.get();
    if (!config.pretty_print) os << ']';
    return solved;
}

int Problem::solve_k(ostream &os, int k, const int &global_solved) {
    int solved = 0;
    vector<int> thread_numbs{numbers};

    do {
        Generator gen{ops, static_cast<size_t>(k - 1)};
        do {
            auto exp_nodes = create_expressions(thread_numbs.begin(), thread_numbs.begin() + k,
                gen.get_word().begin(), gen.get_word().end());

            for (auto &exp_node : exp_nodes) {
                Expression exp{move(exp_node)};

                try {
                    if (exp.is_solution(target)) {
                        if (config.pretty_print) exp.output_pretty(os);
                        else {
                            if (global_solved + solved) os << ',';
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

int Problem::solve_k_large(ostream &os, int k, const char op, const int &global_solved) {
    int solved = 0;
    vector<int> thread_numbs{numbers};

    if (k < 4) throw exception{};

    Generator gen{ops, static_cast<size_t>(k - 2)};

    do {
        do {
            vector<char> word{op};
            word.insert(word.end(), gen.get_word().begin(), gen.get_word().end());

            auto exp_nodes = create_expressions(thread_numbs.begin(), thread_numbs.begin() + k,
                word.begin(), word.end());

            for (auto &exp_node : exp_nodes) {
                Expression exp{move(exp_node)};

                try {
                    if (exp.is_solution(target)) {
                        if (config.pretty_print) exp.output_pretty(os);
                        else {
                            if (global_solved + solved) os << ',';
                            os << '"';
                            exp.output_json(os);
                            os << '"';
                        }
                        ++solved;
                    }
                } catch (ExpressionException) { }
            }
        } while (next_k_permutation(thread_numbs.begin(), thread_numbs.end(), k));
    } while (gen.next_word());

    return solved;
}
}
