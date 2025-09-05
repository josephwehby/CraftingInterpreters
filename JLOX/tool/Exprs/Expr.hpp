#pragma once

#include <memory>
#include "Token.hpp"

class Expr {
public:
  virtual ~Expr() = default;
  virtual void accept() = 0
};

class Binary : public Expr {
public:
  Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right) : 
      left(std::move(left)), op(std::move(op)), right(std::move(right)){}

  std::unique_ptr<Expr> left;
  Token op;
  std::unique_ptr<Expr> right;
};

class Grouping : public Expr {
public:
  Grouping(std::unique_ptr<Expr> expression) : 
      expression(std::move(expression)){}

  std::unique_ptr<Expr> expression;
};

class Literal : public Expr {
public:
  Literal(Object value) : 
      value(std::move(value)){}

  Object value;
};

class Unary : public Expr {
public:
  Unary(Token op, std::unique_ptr<Expr> right) : 
      op(std::move(op)), right(std::move(right)){}

  Token op;
  std::unique_ptr<Expr> right;
};

