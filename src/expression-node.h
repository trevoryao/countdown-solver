#ifndef __EXPRESSION_NODE_H__
#define __EXPRESSION_NODE_H__

#include <memory>

namespace Countdown {
class ExpressionNode {
protected:
    std::unique_ptr<ExpressionNode> left;
    std::unique_ptr<ExpressionNode> right;
public:
    ExpressionNode(std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right);

    virtual ~ExpressionNode();

    virtual int evaluate() = 0;
};
}

#endif
