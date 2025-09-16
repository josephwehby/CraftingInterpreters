#pragma once

#include <memory>

#include "Object.hpp"
#include "Token.hpp"

class VisitorString;
class VisitorObject;
class Binary;
class Grouping;
class Literal;
class Unary;

class Expr {
public:
  virtual ~Expr() = default;
  virtual std::string accept(VisitorString&) = 0;
  virtual Object accept(VisitorObject&) = 0;
};

class VisitorString {
public:
  virtual std::string VisitBinary(Binary& expr) = 0;
  virtual std::string VisitGrouping(Grouping& expr) = 0;
  virtual std::string VisitLiteral(Literal& expr) = 0;
  virtual std::string VisitUnary(Unary& expr) = 0;
};

class VisitorObject {
public:
  virtual Object VisitBinary(Binary& expr) = 0;
  virtual Object VisitGrouping(Grouping& expr) = 0;
  virtual Object VisitLiteral(Literal& expr) = 0;
  virtual Object VisitUnary(Unary& expr) = 0;
};

class Binary : public Expr {
public:
  Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right) : 
    left(std::move(left)), op(std::move(op)), right(std::move(right)){}

  std::string accept(VisitorString& visitor) override {
    return visitor.VisitBinary(*this);
  }

  Object accept(VisitorObject& visitor) override {
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

  std::string accept(VisitorString& visitor) override {
    return visitor.VisitGrouping(*this);
  }

  Object accept(VisitorObject& visitor) override {
    return visitor.VisitGrouping(*this);
  }

  std::unique_ptr<Expr> expression;
};

class Literal : public Expr {
public:
  Literal(Object value) : 
    value(std::move(value)){}

  std::string accept(VisitorString& visitor) override {
    return visitor.VisitLiteral(*this);
  }

  Object accept(VisitorObject& visitor) override {
    return visitor.VisitLiteral(*this);
  }

  Object value;
};

class Unary : public Expr {
public:
  Unary(Token op, std::unique_ptr<Expr> right) : 
    op(std::move(op)), right(std::move(right)){}

  std::string accept(VisitorString& visitor) override {
    return visitor.VisitUnary(*this);
  }

  Object accept(VisitorObject& visitor) override {
    return visitor.VisitUnary(*this);
  }

  Token op;
  std::unique_ptr<Expr> right;
};

