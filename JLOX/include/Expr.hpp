#pragma once

#include <memory>
#include "Token.hpp"

class VisitorExprString;
class VisitorExprObject;
class Binary;
class Grouping;
class Literal;
class Unary;
class Variable;

class Expr {
public:
  virtual ~Expr() = default;
  virtual std::string accept(VisitorExprString&) = 0;
  virtual Object accept(VisitorExprObject&) = 0;
};

class VisitorExprString {
public:
  virtual std::string VisitBinaryExpr(Binary& expr) = 0;
  virtual std::string VisitGroupingExpr(Grouping& expr) = 0;
  virtual std::string VisitLiteralExpr(Literal& expr) = 0;
  virtual std::string VisitUnaryExpr(Unary& expr) = 0;
  virtual std::string VisitVariableExpr(Variable& expr) = 0;
};

class VisitorExprObject {
public:
  virtual Object VisitBinaryExpr(Binary& expr) = 0;
  virtual Object VisitGroupingExpr(Grouping& expr) = 0;
  virtual Object VisitLiteralExpr(Literal& expr) = 0;
  virtual Object VisitUnaryExpr(Unary& expr) = 0;
  virtual Object VisitVariableExpr(Variable& expr) = 0;
};

class Binary : public Expr {
public:
  Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right) : 
    left(std::move(left)), op(std::move(op)), right(std::move(right)){}

  std::string accept(VisitorExprString& visitor) override {
    return visitor.VisitBinaryExpr(*this);
  }

  Object accept(VisitorExprObject& visitor) override {
    return visitor.VisitBinaryExpr(*this);
  }

  std::unique_ptr<Expr> left;
  Token op;
  std::unique_ptr<Expr> right;
};

class Grouping : public Expr {
public:
  Grouping(std::unique_ptr<Expr> expression) : 
    expression(std::move(expression)){}

  std::string accept(VisitorExprString& visitor) override {
    return visitor.VisitGroupingExpr(*this);
  }

  Object accept(VisitorExprObject& visitor) override {
    return visitor.VisitGroupingExpr(*this);
  }

  std::unique_ptr<Expr> expression;
};

class Literal : public Expr {
public:
  Literal(Object value) : 
    value(std::move(value)){}

  std::string accept(VisitorExprString& visitor) override {
    return visitor.VisitLiteralExpr(*this);
  }

  Object accept(VisitorExprObject& visitor) override {
    return visitor.VisitLiteralExpr(*this);
  }

  Object value;
};

class Unary : public Expr {
public:
  Unary(Token op, std::unique_ptr<Expr> right) : 
    op(std::move(op)), right(std::move(right)){}

  std::string accept(VisitorExprString& visitor) override {
    return visitor.VisitUnaryExpr(*this);
  }

  Object accept(VisitorExprObject& visitor) override {
    return visitor.VisitUnaryExpr(*this);
  }

  Token op;
  std::unique_ptr<Expr> right;
};

class Variable : public Expr {
public:
  Variable(Token name) : 
    name(std::move(name)){}

  std::string accept(VisitorExprString& visitor) override {
    return visitor.VisitVariableExpr(*this);
  }

  Object accept(VisitorExprObject& visitor) override {
    return visitor.VisitVariableExpr(*this);
  }

  Token name;
};

