#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "int-node.h"
#include "op-node.h"

namespace Countdown {
template<class NumsIt, class OpsIt> std::vector<std::unique_ptr<ExpressionNode>>
create_expressions(const NumsIt nums_begin, const NumsIt nums_end,
    const OpsIt ops_begin, const OpsIt ops_end);

class Expression {
private:
    std::unique_ptr<ExpressionNode> expression_root;
public:
    Expression(std::unique_ptr<ExpressionNode> node);

    bool is_solution(int target);

    std::ostream &output_pretty(std::ostream &out) const;
    std::ostream &output_json(std::ostream &out) const;
};

template<class NumsIt, class OpsIt> std::vector<std::unique_ptr<ExpressionNode>>
create_expressions(const NumsIt nums_begin, const NumsIt nums_end,
    const OpsIt ops_begin, const OpsIt ops_end) {
    std::vector<std::unique_ptr<ExpressionNode>> result;

    if (nums_begin + 1 == nums_end) {
        result.emplace_back(std::move(std::make_unique<IntNode>(*nums_begin)));
        return result;
    }

    auto nums_it = nums_begin + 1;
    auto ops_it = ops_begin + 1;

    while (nums_it != nums_end) {
        auto left_exps = create_expressions(nums_begin, nums_it, ops_begin, ops_it);
        auto right_exps = create_expressions(nums_it, nums_end, ops_it, ops_end);

        for (auto &left : left_exps) {
            for (auto &right : right_exps) {
                result.emplace_back(std::move(std::make_unique<OpNode>(
                    *(ops_it - 1),
                    std::move(left),
                    std::move(right)
                )));
            }
        }

        ++nums_it;
        ++ops_it;
    }

    return result;
}
}

#endif
