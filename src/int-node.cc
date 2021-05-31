#include "int-node.h"

#include <utility>

using namespace std;

namespace Countdown {
IntNode::IntNode(int n) : ExpressionNode{unique_ptr<ExpressionNode>{}, unique_ptr<ExpressionNode>{}}, n{n} { }

int IntNode::evaluate() { return n; }

ostream &IntNode::output_pretty(ostream &out) const {
    out << n;
    return out;
}

ostream &IntNode::output_json(ostream &out) const { return output_pretty(out); }
}
