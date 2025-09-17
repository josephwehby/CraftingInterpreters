#pragma once

#include <memory>
#include "Token.hpp"

class VisitorStmtVoid;
class VisitorStmtObject;
class Expression;
class Print;

class Stmt {
public:
  virtual ~Stmt() = default;
  virtual void accept(VisitorStmtVoid&) = 0;
  virtual Object accept(VisitorStmtObject&) = 0;
};

class VisitorStmtVoid {
public:
  virtual void VisitExpression(Expression& stmt) = 0;
  virtual void VisitPrint(Print& stmt) = 0;
};

class VisitorStmtObject {
public:
  virtual Object VisitExpression(Expression& stmt) = 0;
  virtual Object VisitPrint(Print& stmt) = 0;
};

class Expression : public Stmt {
public:
  Expression(std::unique_ptr<Expr> expression) : 
    expression(std::move(expression)){}

  void accept(VisitorStmtVoid& visitor) override {
    return visitor.VisitExpression(*this);
  }

  Object accept(VisitorStmtObject& visitor) override {
    return visitor.VisitExpression(*this);
  }

  std::unique_ptr<Expr> expression;
};

class Print : public Stmt {
public:
  Print(std::unique_ptr<Expr> expression) : 
    expression(std::move(expression)){}

  void accept(VisitorStmtVoid& visitor) override {
    return visitor.VisitPrint(*this);
  }

  Object accept(VisitorStmtObject& visitor) override {
    return visitor.VisitPrint(*this);
  }

  std::unique_ptr<Expr> expression;
};

