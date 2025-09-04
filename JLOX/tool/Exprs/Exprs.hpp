#pragma once

#include "Expr.hpp"

class Binary : public Expr {
public:
  Binary(Expr left,Token operator,Expr right) {
    this->left = left;
    this->operator = operator;
    this->right = right;
  }

  Expr left;
  Token operator;
  Expr right;
};

class Grouping : public Expr {
public:
  Grouping(Expr expression) {
    this->expression = expression;
  }

  Expr expression;
};

class Literal : public Expr {
public:
  Literal(Object value) {
    this->value = value;
  }

  Object value;
};

class Unary : public Expr {
public:
  Unary(Token operator,Expr right) {
    this->operator = operator;
    this->right = right;
  }

  Token operator;
  Expr right;
};

