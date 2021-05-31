#include "expression.h"

using namespace std;

namespace Countdown {
bool Expression::is_solution(int target) {
    return expression_root->evaluate() == target;
}

ostream &Expression::output_pretty(ostream &out) const {
    expression_root->output_pretty(out);
    return out << endl;
}

ostream &Expression::output_json(ostream &out) const {
    expression_root->output_json(out);
    return out << endl;
}
}
