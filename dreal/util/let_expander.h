#pragma once

#include <map>
#include <string>

#include "dreal/symbolic/symbolic.h"
#include "dreal/smt2/term.h"

namespace dreal {
/// Visitor class that expands references to local variables.
class LetExpander {
 public:
  /// Delete the default constructor.
  LetExpander() = delete;

  /// Constructs an expander from @p bindings.
  explicit LetExpander(const std::map<std::string, Term>& bindings)
    : bindings_(bindings) {}

  /// Expand @p term by performing the substitutions specified by the bindings.
  Term Expand(const Term& term);

 private:
  Expression Visit(const Expression& e);
  Expression VisitVariable(const Expression& e);
  Expression VisitConstant(const Expression& e);
  Expression VisitRealConstant(const Expression& e);
  Expression VisitAddition(const Expression& e);
  Expression VisitMultiplication(const Expression& e);
  Expression VisitDivision(const Expression& e);
  Expression VisitLog(const Expression& e);
  Expression VisitAbs(const Expression& e);
  Expression VisitExp(const Expression& e);
  Expression VisitSqrt(const Expression& e);
  Expression VisitPow(const Expression& e);
  Expression VisitSin(const Expression& e);
  Expression VisitCos(const Expression& e);
  Expression VisitTan(const Expression& e);
  Expression VisitAsin(const Expression& e);
  Expression VisitAcos(const Expression& e);
  Expression VisitAtan(const Expression& e);
  Expression VisitAtan2(const Expression& e);
  Expression VisitSinh(const Expression& e);
  Expression VisitCosh(const Expression& e);
  Expression VisitTanh(const Expression& e);
  Expression VisitMin(const Expression& e);
  Expression VisitMax(const Expression& e);
  Expression VisitIfThenElse(const Expression& e);
  Expression VisitUninterpretedFunction(const Expression& e);

  Formula Visit(const Formula& f);
  Formula VisitFalse(const Formula& f);
  Formula VisitTrue(const Formula& f);
  Formula VisitVariable(const Formula& f);
  Formula VisitEqualTo(const Formula& f);
  Formula VisitNotEqualTo(const Formula& f);
  Formula VisitGreaterThan(const Formula& f);
  Formula VisitGreaterThanOrEqualTo(const Formula& f);
  Formula VisitLessThan(const Formula& f);
  Formula VisitLessThanOrEqualTo(const Formula& f);
  Formula VisitConjunction(const Formula& f);
  Formula VisitDisjunction(const Formula& f);
  Formula VisitNegation(const Formula& f);
  Formula VisitForall(const Formula& f);

  // Makes VisitFormula a friend of this class so that it can use private
  // operator()s.
  friend Formula
  drake::symbolic::VisitFormula<Formula>(LetExpander*, const Formula&);

  // Makes VisitExpression a friend of this class so that it can use private
  // operator()s.
  friend Expression
  drake::symbolic::VisitExpression<Expression>(LetExpander*, const Expression&);

 private:
  const std::map<std::string, Term>& bindings_;
};

}  // namespace dreal
