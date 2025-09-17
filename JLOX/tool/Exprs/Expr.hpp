#pragma once

#include <memory>
#include "Token.hpp"

class VisitorExprString;
class VisitorExprObject;
class Binary;
class Grouping;
class Literal;
class Unary;

class Expr {
public:
  virtual ~Expr() = default;
  virtual std::string accept(VisitorString&) = 0;
  virtual object accept(VisitorObject&) = 0;
};

class VisitorExprString {
public:
  virtual std::string VisitBinary(Binary& expr) = 0;
  virtual std::string VisitGrouping(Grouping& expr) = 0;
  virtual std::string VisitLiteral(Literal& expr) = 0;
  virtual std::string VisitUnary(Unary& expr) = 0;
};

class VisitorExprObject {
public:
  virtual object VisitBinary(Binary& expr) = 0;
  virtual object VisitGrouping(Grouping& expr) = 0;
  virtual object VisitLiteral(Literal& expr) = 0;
  virtual object VisitUnary(Unary& expr) = 0;
};

class Binary : public Expr {
public:
  Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right) : 
      left(std::move(left)), op(std::move(op)), right(std::move(right)){}

  std::string accept(VisitorExprString& visitor) override {
    return visitor.VisitBinary(*this);
  }

  object accept(VisitorExprObject& visitor) override {
    return visitor.VisitBinary(*this);
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
    return visitor.VisitGrouping(*this);
  }

  object accept(VisitorExprObject& visitor) override {
    return visitor.VisitGrouping(*this);
  }

  std::unique_ptr<Expr> expression;
};

class Literal : public Expr {
public:
  Literal(Object value) : 
      value(std::move(value)){}

  std::string accept(VisitorExprString& visitor) override {
    return visitor.VisitLiteral(*this);
  }

  object accept(VisitorExprObject& visitor) override {
    return visitor.VisitLiteral(*this);
  }

  Object value;
};

class Unary : public Expr {
public:
  Unary(Token op, std::unique_ptr<Expr> right) : 
      op(std::move(op)), right(std::move(right)){}

  std::string accept(VisitorExprString& visitor) override {
    return visitor.VisitUnary(*this);
  }

  object accept(VisitorExprObject& visitor) override {
    return visitor.VisitUnary(*this);
  }

  Token op;
  std::unique_ptr<Expr> right;
};

