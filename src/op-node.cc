#include "op-node.h"

#include <utility>

using namespace std;

namespace Countdown {
// OpNode::OpNode(char op) : ExpressionNode{unique_ptr<ExpressionNode>{}, unique_ptr<ExpressionNode>{}}, op{op} { }

OpNode::OpNode(char op, unique_ptr<ExpressionNode> left, unique_ptr<ExpressionNode> right) : ExpressionNode{move(left), move(right)}, op{op} { }

int OpNode::evaluate() {
    switch (op) {
        case '+': return left->evaluate() + right->evaluate();
        case '-': return left->evaluate() - right->evaluate();
        case '*': return left->evaluate() * right->evaluate();
        case '/': return left->evaluate() / right->evaluate();
    }
    return 0; // to remove the warnings
}

ostream &OpNode::output_pretty(ostream &out) const {
    out << "(";
    left->output_pretty(out);
    out << " " << op << " ";
    right->output_pretty(out);
    out << ")";
    return out;
}

ostream &OpNode::output_json(ostream &out) const {
    out << "(";
    left->output_pretty(out);
    out << op;
    right->output_pretty(out);
    out << ")";
    return out;
}
}
