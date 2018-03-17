#include "dreal/util/let_expander.h"

#include <algorithm>
#include <set>

#include "dreal/util/exception.h"
#include "dreal/util/logging.h"

namespace dreal {

Term LetExpander::Expand(const Term& term) {
  DREAL_LOG_DEBUG("LetExpander::Expand({})", term);
  if (term.type() == Term::Type::FORMULA) {
    return Term{ Visit(term.formula()) };
  } else {
    return Term{ Visit(term.expression()) };
  }
}

Expression LetExpander::Visit(const Expression& e) {
  DREAL_LOG_TRACE("LetExpander::Visit({})", e);
  return VisitExpression<Expression>(this, e);
}

Expression LetExpander::VisitVariable(const Expression& e) {
  std::string name{ get_variable(e).get_name() };
  auto pos = bindings_.find(name);
  if (pos != bindings_.end()) {
    DREAL_LOG_TRACE("LetExpander: replacing Expression {} with {}",
                    e, pos->second.expression());
    return pos->second.expression();
  }
  return e;
}

Expression LetExpander::VisitConstant(const Expression& e) {
  return e;
}

Expression LetExpander::VisitRealConstant(const Expression& e) {
  return e;
}

Expression LetExpander::VisitAddition(const Expression& e) {
  Expression ret{ get_constant_in_addition(e) };
  for (const auto& p : get_expr_to_coeff_map_in_addition(e)) {
    const Expression& e_i{p.first};
    const double coeff{p.second};
    ret += coeff * Visit(e_i);
  }
  return ret;
}

Expression LetExpander::VisitMultiplication(const Expression& e) {
  Expression ret{ get_constant_in_multiplication(e) };
  for (const auto& p : get_base_to_exponent_map_in_multiplication(e)) {
    const Expression& base{p.first};
    const Expression& exponent{p.second};
    ret *= pow(Visit(base), Visit(exponent));
  }
  return ret;
}

Expression LetExpander::VisitDivision(const Expression& e) {
  return Visit(get_first_argument(e)) / Visit(get_second_argument(e));
}

Expression LetExpander::VisitLog(const Expression& e) {
  return log(Visit(get_argument(e)));
}

Expression LetExpander::VisitAbs(const Expression& e) {
  return abs(Visit(get_argument(e)));
}

Expression LetExpander::VisitExp(const Expression& e) {
  return exp(Visit(get_argument(e)));
}

Expression LetExpander::VisitSqrt(const Expression& e) {
  return sqrt(Visit(get_argument(e)));
}

Expression LetExpander::VisitPow(const Expression& e) {
  const Expression& base{get_first_argument(e)};
  const Expression& exponent{get_second_argument(e)};
  return pow(Visit(base), Visit(exponent));
}

Expression LetExpander::VisitSin(const Expression& e) {
  return sin(Visit(get_argument(e)));
}

Expression LetExpander::VisitCos(const Expression& e) {
  return cos(Visit(get_argument(e)));
}

Expression LetExpander::VisitTan(const Expression& e) {
  return tan(Visit(get_argument(e)));
}

Expression LetExpander::VisitAsin(const Expression& e) {
  return asin(Visit(get_argument(e)));
}

Expression LetExpander::VisitAcos(const Expression& e) {
  return acos(Visit(get_argument(e)));
}

Expression LetExpander::VisitAtan(const Expression& e) {
  return atan(Visit(get_argument(e)));
}

Expression LetExpander::VisitAtan2(const Expression& e) {
  return atan2(Visit(get_first_argument(e)),
               Visit(get_second_argument(e)));
}

Expression LetExpander::VisitSinh(const Expression& e) {
  return sinh(Visit(get_argument(e)));
}

Expression LetExpander::VisitCosh(const Expression& e) {
  return cosh(Visit(get_argument(e)));
}

Expression LetExpander::VisitTanh(const Expression& e) {
  return tanh(Visit(get_argument(e)));
}

Expression LetExpander::VisitMin(const Expression& e) {
  return min(Visit(get_first_argument(e)),
             Visit(get_second_argument(e)));
}

Expression LetExpander::VisitMax(const Expression& e) {
  return max(Visit(get_first_argument(e)),
             Visit(get_second_argument(e)));
}

Expression LetExpander::VisitIfThenElse(const Expression&) {
  throw DREAL_RUNTIME_ERROR(
      "LetExpander: If-then-else expression is not supported yet.");
}

Expression LetExpander::VisitUninterpretedFunction(const Expression&) {
  throw DREAL_RUNTIME_ERROR(
      "LetExpander: Uninterpreted function is not supported.");
}

Formula LetExpander::Visit(const Formula& f) {
  DREAL_LOG_TRACE("LetExpander::Visit({})", f);
  return VisitFormula<Formula>(this, f);
}

Formula LetExpander::VisitFalse(const Formula& f) {
  return f;
}

Formula LetExpander::VisitTrue(const Formula& f) {
  return f;
}

Formula LetExpander::VisitVariable(const Formula& f) {
  std::string name{ get_variable(f).get_name() };
  auto pos = bindings_.find(name);
  if (pos != bindings_.end()) {
    DREAL_LOG_TRACE("LetExpander: replacing Formula {} with {}",
                    f, pos->second.formula());
    return pos->second.formula();
  }
  return f;
}

Formula LetExpander::VisitEqualTo(const Formula& f) {
  Expression lhs{ Visit(get_lhs_expression(f)) };
  Expression rhs{ Visit(get_rhs_expression(f)) };
  return lhs == rhs;
}

Formula LetExpander::VisitNotEqualTo(const Formula& f) {
  Expression lhs{ Visit(get_lhs_expression(f)) };
  Expression rhs{ Visit(get_rhs_expression(f)) };
  return lhs != rhs;
}

Formula LetExpander::VisitGreaterThan(const Formula& f) {
  Expression lhs{ Visit(get_lhs_expression(f)) };
  Expression rhs{ Visit(get_rhs_expression(f)) };
  return lhs > rhs;
}

Formula LetExpander::VisitGreaterThanOrEqualTo(const Formula& f) {
  Expression lhs{ Visit(get_lhs_expression(f)) };
  Expression rhs{ Visit(get_rhs_expression(f)) };
  return lhs >= rhs;
}

Formula LetExpander::VisitLessThan(const Formula& f) {
  Expression lhs{ Visit(get_lhs_expression(f)) };
  Expression rhs{ Visit(get_rhs_expression(f)) };
  return lhs < rhs;
}

Formula LetExpander::VisitLessThanOrEqualTo(const Formula& f) {
  Expression lhs{ Visit(get_lhs_expression(f)) };
  Expression rhs{ Visit(get_rhs_expression(f)) };
  return lhs <= rhs;
}

Formula LetExpander::VisitConjunction(const Formula& f) {
  const std::set<Formula>& ops{ get_operands(f) };
  std::set<Formula> new_ops;
  for (auto& f : ops) {
    new_ops.insert(Visit(f));
  }
  return make_conjunction(new_ops);
}

Formula LetExpander::VisitDisjunction(const Formula& f) {
  const std::set<Formula>& ops{ get_operands(f) };
  std::set<Formula> new_ops;
  for (auto& f : ops) {
    new_ops.insert(Visit(f));
  }
  return make_disjunction(new_ops);
}

Formula LetExpander::VisitNegation(const Formula& f) {
  return !Visit(get_operand(f));
}

Formula LetExpander::VisitForall(const Formula&) {
  throw DREAL_RUNTIME_ERROR(
      "LetExpander: forall constraint is not supported.");
}

}  // namespace dreal
