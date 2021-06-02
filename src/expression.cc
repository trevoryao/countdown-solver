#include "expression.h"

using namespace std;

namespace Countdown {
Expression::Expression(unique_ptr<ExpressionNode> node) : expression_root{move(node)} { }

bool Expression::is_solution(int target) {
    return expression_root->evaluate() == target;
}

ostream &Expression::output_pretty(ostream &out) const {
    expression_root->output_pretty(out);
    return out << endl;
}

ostream &Expression::output_json(ostream &out) const {
    return expression_root->output_json(out);
}
}
