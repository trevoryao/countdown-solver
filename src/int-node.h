#ifndef __INT_NODE_H__
#define __INT_NODE_H__

#include <iostream>
#include <memory>

#include "expression-node.h"

namespace Countdown {
class IntNode : public ExpressionNode {
private:
    int n;
public:
    IntNode(int n);

    int evaluate();

    std::ostream &output_pretty(std::ostream &out) const;
    std::ostream &output_json(std::ostream &out) const;
};
}

#endif
