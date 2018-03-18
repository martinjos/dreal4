#include "dreal/smt2/driver.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include <experimental/optional>

#include "dreal/smt2/scanner.h"
#include "dreal/util/let_expander.h"

namespace dreal {

using std::cerr;
using std::cout;
using std::endl;
using std::experimental::optional;
using std::ifstream;
using std::istream;
using std::istringstream;
using std::move;
using std::string;

Smt2Driver::Smt2Driver(Context context) : context_{move(context)} {}

bool Smt2Driver::parse_stream(istream& in, const string& sname) {
  streamname_ = sname;

  Smt2Scanner scanner(&in);
  scanner.set_debug(trace_scanning_);
  this->scanner_ = &scanner;

  Smt2Parser parser(*this);
  parser.set_debug_level(trace_parsing_);
  return (parser.parse() == 0);
}

bool Smt2Driver::parse_file(const string& filename) {
  ifstream in(filename.c_str());
  if (!in.good()) {
    return false;
  }
  return parse_stream(in, filename);
}

bool Smt2Driver::parse_string(const string& input, const string& sname) {
  istringstream iss(input);
  return parse_stream(iss, sname);
}

void Smt2Driver::error(const location& l, const string& m) {
  cerr << l << " : " << m << endl;
}

void Smt2Driver::error(const string& m) { cerr << m << endl; }

void Smt2Driver::CheckSat() {
  const optional<Box> model{context_.CheckSat()};
  if (model) {
    cout << "delta-sat with delta = " << context_.config().precision() << endl;
    if (context_.config().produce_models()) {
      cout << *model << endl;
    }
  } else {
    cout << "unsat" << endl;
  }
}

Variable Smt2Driver::RegisterVariable(const std::string& name, Sort sort) {
  Variable v{ ParseVariableSort(name, sort) };
  scope_.insert(v.get_name(), v);
  return v;
}

void Smt2Driver::DeclareVariable(const std::string& name, Sort sort) {
  Variable v{ RegisterVariable(name, sort) };
  context_.DeclareVariable(v);
}

void Smt2Driver::DeclareVariable(const std::string& name, Sort sort,
                                 const Term& lb, const Term& ub) {
  Variable v{ RegisterVariable(name, sort) };
  context_.DeclareVariable(v, lb.expression(), ub.expression());
}

const Variable& Smt2Driver::lookup_variable(const string& name) {
  const auto it = scope_.find(name);
  if (it == scope_.cend()) {
    throw DREAL_RUNTIME_ERROR("{} is an undeclared variable.", name);
  }
  return it->second;
}

Variable Smt2Driver::ParseVariableSort(const std::string& name, const Sort s) {
  return Variable{name, SortToType(s)};
}

Term Smt2Driver::ExpandLet(const Term& term,
                           const std::map<std::string, Term>& bindings) {
  return LetExpander(bindings).Expand(term);
}

}  // namespace dreal
