#ifndef __EXPRESSION_NODE_H__
#define __EXPRESSION_NODE_H__

#include <iostream>
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

    virtual std::ostream &output_pretty(std::ostream &out) const = 0;
    virtual std::ostream &output_json(std::ostream &out) const = 0;
};
}

#endif
