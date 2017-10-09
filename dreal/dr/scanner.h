#pragma once

// Flex expects the signature of yylex to be defined in the macro YY_DECL, and
// the C++ parser expects it to be declared. We can factor both as follows.

#ifndef YY_DECL

#define YY_DECL                                      \
  dreal::DrParser::token_type dreal::DrScanner::lex( \
      dreal::DrParser::semantic_type* yylval,        \
      dreal::DrParser::location_type* yylloc)
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer DrFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif

// The following include should come first before parser.yy.hh.
// Do not alpha-sort them.
#include "dreal/symbolic/symbolic.h"

#include "dreal/dr/parser.yy.hh"

namespace dreal {

/** DrScanner is a derived class to add some extra function to the scanner
 * class. Flex itself creates a class named yyFlexLexer, which is renamed using
 * macros to ExampleFlexLexer. However we change the context of the generated
 * yylex() function to be contained within the DrScanner class. This is
 * required because the yylex() defined in ExampleFlexLexer has no parameters.
 */
class DrScanner : public DrFlexLexer {
 public:
  /** Create a new scanner object. The streams arg_yyin and arg_yyout default
   * to cin and cout, but that assignment is only made when initializing in
   * yylex(). */
  explicit DrScanner(std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0);

  /** Required for virtual functions */
  virtual ~DrScanner();

  /** This is the main lexing function. It is generated by flex according to
   * the macro declaration YY_DECL above. The generated bison parser then
   * calls this virtual function to fetch new tokens. */
  virtual DrParser::token_type lex(DrParser::semantic_type* yylval,
                                   DrParser::location_type* yylloc);

  /** Enable debug output (via arg_yyout) if compiled into the scanner. */
  void set_debug(bool b);
};

}  // namespace dreal