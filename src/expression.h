#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <utility>

#include "int-node.h"
#include "op-node.h"

namespace Countdown {
class ExpressionDivException {};
class ExpressionException {};

class Expression {
private:
    std::unique_ptr<ExpressionNode> expression_root;
public:
    template<class NumsIt, class OpsIt> // assuming bidirectional
    Expression(const NumsIt nums_begin, const NumsIt nums_end, const OpsIt ops_begin, const OpsIt ops_end);

    bool is_solution(int target);

    std::ostream &output_pretty(std::ostream &out) const;
    std::ostream &output_json(std::ostream &out) const;
};

template<class NumsIt, class OpsIt>
Expression::Expression(const NumsIt nums_begin, const NumsIt nums_end,
    const OpsIt ops_begin, const OpsIt ops_end) {
    std::list<std::unique_ptr<ExpressionNode>> nums;
    std::list<char> ops;

    for (auto nums_it = nums_begin; nums_it != nums_end; ++nums_it) {
        nums.emplace_back(std::make_unique<IntNode>(*nums_it));
    }

    std::copy(ops_begin, ops_end, std::back_inserter(ops));

    auto nums_it = nums.begin();
    auto ops_it = ops.begin();
    while (ops_it != ops.end()) {
        if (*ops_it == '*' || *ops_it == '/') {
            auto nums_right_it = nums_it;
            ++nums_right_it;
            
            if (*ops_it == '/') {
                if ((*nums_it)->evaluate() % (*nums_right_it)->evaluate()) {
                    throw ExpressionDivException{};
                }
            }

            ExpressionNode *nums_left = nums_it->release();
            ExpressionNode *nums_right = nums_right_it->release();

            ++nums_right_it;
            nums_it = nums.erase(nums_it, nums_right_it);

            nums_it = nums.insert(nums_it, std::make_unique<OpNode>(*ops_it,
                std::unique_ptr<ExpressionNode>{nums_left},
                std::unique_ptr<ExpressionNode>{nums_right}
            ));
            ops_it = ops.erase(ops_it);
        } else {
            ++ops_it;
            ++nums_it;
        }
    }

    nums_it = nums.begin();
    ops_it = ops.begin();
    while (ops_it != ops.end()) {
        auto nums_right_it = nums_it;
        ++nums_right_it;

        ExpressionNode *nums_left = nums_it->release();
        ExpressionNode *nums_right = nums_right_it->release();

        ++nums_right_it;
        nums_it = nums.erase(nums_it, nums_right_it);

        nums_it = nums.insert(nums_it, std::make_unique<OpNode>(*ops_it,
            std::unique_ptr<ExpressionNode>{nums_left},
            std::unique_ptr<ExpressionNode>{nums_right}
        ));
        ops_it = ops.erase(ops_it);
    }

    if (nums.size() == 1 && ops.empty()) {
        ExpressionNode *node_ptr = nums.begin()->release();
        nums.erase(nums.begin());
        expression_root = std::unique_ptr<ExpressionNode>{node_ptr};
    } else {
        throw ExpressionException{};
    }
}
}

#endif
