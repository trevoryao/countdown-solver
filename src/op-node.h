#ifndef __OP_NODE_H__
#define __OP_NODE_H__

#include <memory>

#include "expression-node.h"

namespace Countdown {
class OpNode : public ExpressionNode {
private:
    char op;
public:
    OpNode(char op, std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right);

    int evaluate();
};
}

#endif
