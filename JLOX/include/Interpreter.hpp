#pragma once

#include <memory>
#include <vector>

#include "Object.hpp"
#include "Expr.hpp"
#include "Stmt.hpp"
#include "Environment.hpp"
#include "Helper.hpp"
#include "RuntimeError.hpp"
#include "Error.hpp"

class Interpreter : public VisitorExprObject, VisitorStmtVoid {
public:

  void interpret(const std::vector<std::unique_ptr<Stmt>>&);
  void execute(const std::unique_ptr<Stmt>&);

  Object VisitBinaryExpr(Binary&) override;
  Object VisitGroupingExpr(Grouping&) override;
  Object VisitLiteralExpr(Literal&) override;
  Object VisitUnaryExpr(Unary&) override;
  Object VisitVariableExpr(Variable&) override;

  void VisitExpressionStmt(Expression&) override;
  void VisitPrintStmt(Print&) override;
  void VisitVarStmt(Var&) override;

  Object evaluate(Expr&);

  bool isTruthy(const Object&);
  bool isEqual(const Object&, const Object&);
  bool endsWithZero(std::string&, size_t);

  void checkNumberOperand(Token, const Object&);
  void checkNumberOperands(Token, const Object&, const Object&);

  std::string stringify(Object&);
private:

  Environment env;
};
