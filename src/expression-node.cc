#include "expression-node.h"

#include <utility>

using namespace std;

namespace Countdown {
ExpressionNode::ExpressionNode(unique_ptr<ExpressionNode> left, unique_ptr<ExpressionNode> right) : left{move(left)}, right{move(right)} { }

ExpressionNode::~ExpressionNode() { }
}
