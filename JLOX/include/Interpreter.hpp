#pragma once

#include <memory>

#include "Object.hpp"
#include "Expr.hpp"
#include "Helper.hpp"
#include "RuntimeError.hpp"
#include "Error.hpp"

class Interpreter : public VisitorObject {
public:

  void interpret(const std::unique_ptr<Expr>&);

  Object VisitBinary(Binary& expr) override;
  Object VisitGrouping(Grouping& expr) override;
  Object VisitLiteral(Literal& expr) override;
  Object VisitUnary(Unary& expr) override;

  Object evaluate(Expr&);

  bool isTruthy(const Object&);
  bool isEqual(const Object&, const Object&);
  bool endsWithZero(std::string&, size_t);

  void checkNumberOperand(Token, const Object&);
  void checkNumberOperands(Token, const Object&, const Object&);

  std::string stringify(Object&);
};
