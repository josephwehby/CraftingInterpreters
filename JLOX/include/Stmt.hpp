#pragma once

#include <memory>
#include "Token.hpp"

class VisitorStmtVoid;
class VisitorStmtObject;
class Expression;
class Print;
class Var;

class Stmt {
public:
  virtual ~Stmt() = default;
  virtual void accept(VisitorStmtVoid&) = 0;
  virtual Object accept(VisitorStmtObject&) = 0;
};

class VisitorStmtVoid {
public:
  virtual void VisitExpressionStmt(Expression& stmt) = 0;
  virtual void VisitPrintStmt(Print& stmt) = 0;
  virtual void VisitVarStmt(Var& stmt) = 0;
};

class VisitorStmtObject {
public:
  virtual Object VisitExpressionStmt(Expression& stmt) = 0;
  virtual Object VisitPrintStmt(Print& stmt) = 0;
  virtual Object VisitVarStmt(Var& stmt) = 0;
};

class Expression : public Stmt {
public:
  Expression(std::unique_ptr<Expr> expression) : 
    expression(std::move(expression)){}

  void accept(VisitorStmtVoid& visitor) override {
    return visitor.VisitExpressionStmt(*this);
  }

  Object accept(VisitorStmtObject& visitor) override {
    return visitor.VisitExpressionStmt(*this);
  }

  std::unique_ptr<Expr> expression;
};

class Print : public Stmt {
public:
  Print(std::unique_ptr<Expr> expression) : 
    expression(std::move(expression)){}

  void accept(VisitorStmtVoid& visitor) override {
    return visitor.VisitPrintStmt(*this);
  }

  Object accept(VisitorStmtObject& visitor) override {
    return visitor.VisitPrintStmt(*this);
  }

  std::unique_ptr<Expr> expression;
};

class Var : public Stmt {
public:
  Var(Token name, std::unique_ptr<Expr> initializer) : 
    name(std::move(name)), initializer(std::move(initializer)){}

  void accept(VisitorStmtVoid& visitor) override {
    return visitor.VisitVarStmt(*this);
  }

  Object accept(VisitorStmtObject& visitor) override {
    return visitor.VisitVarStmt(*this);
  }

  Token name;
  std::unique_ptr<Expr> initializer;
};

