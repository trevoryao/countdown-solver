#ifndef __OP_NODE_H__
#define __OP_NODE_H__

#include <iostream>
#include <memory>

#include "expression-node.h"

namespace Countdown {
class OpNode : public ExpressionNode {
private:
    char op;
public:
    OpNode(char op, std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right);

    int evaluate();

    std::ostream &output_pretty(std::ostream &out) const;
    std::ostream &output_json(std::ostream &out) const;
};
}

#endif
