#pragma once

#include <memory>
#include <vector>

#include "Object.hpp"
#include "Expr.hpp"
#include "Stmt.hpp"
#include "Helper.hpp"
#include "RuntimeError.hpp"
#include "Error.hpp"

class Interpreter : public VisitorObject, VisitorStmtVoid {
public:

  void interpret(const std::vector<std::unique_ptr<Stmt>>&);
  void execute(const std::unique_ptr<Stmt>&);

  Object VisitBinary(Binary& expr) override;
  Object VisitGrouping(Grouping& expr) override;
  Object VisitLiteral(Literal& expr) override;
  Object VisitUnary(Unary& expr) override;

  void VisitExpression(Expression&) override;
  void VisitPrint(Print&) override;

  Object evaluate(Expr&);

  bool isTruthy(const Object&);
  bool isEqual(const Object&, const Object&);
  bool endsWithZero(std::string&, size_t);

  void checkNumberOperand(Token, const Object&);
  void checkNumberOperands(Token, const Object&, const Object&);

  std::string stringify(Object&);
};
