#ifndef __EXPRESSION_NODE_H__
#define __EXPRESSION_NODE_H__

#include <memory>

namespace Countdown {
class ExpressionNode {
private:
    char op;
    int n;
    std::unique_ptr<ExpressionNode> left;
    std::unique_ptr<ExpressionNode> right;
public:
    ExpressionNode(char op, int n);
    ExpressionNode(char op, int n, std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right);

    int evaluate();
};
}

#endif
