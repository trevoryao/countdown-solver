#ifndef __INT_NODE_H__
#define __INT_NODE_H__

#include <memory>

#include "expression-node.h"

namespace Countdown {
class IntNode : public ExpressionNode {
private:
    int n;
public:
    IntNode(int n);

    int evaluate();
};
}

#endif
