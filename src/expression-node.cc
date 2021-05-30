#include "expression-node.h"

#include <utility>

using namespace std;

namespace Countdown {
ExpressionNode::ExpressionNode(char op, int n) : op{op}, n{n} { }

ExpressionNode::ExpressionNode(char op, int n, unique_ptr<ExpressionNode> left, unique_ptr<ExpressionNode> right) : op{op}, n{n}, left{move(left)}, right{move(right)} { }

int ExpressionNode::evaluate() {
    switch (op) {
        case '+': return left->evaluate() + right->evaluate();
        case '-': return left->evaluate() - right->evaluate();
        case '*': return left->evaluate() * right->evaluate();
        case '/': return left->evaluate() / right->evaluate();
    }
}
}
