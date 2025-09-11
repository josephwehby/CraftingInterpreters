#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Exprs.hpp"

class Parser {
public:
  Parser(std::vector<Token>);
private:
  std::unique_ptr<Expr> expression();
  std::unique_ptr<Expr> equality();
  std::unique_ptr<Expr> comparison();
  std::unique_ptr<Expr> term();
  std::unique_ptr<Expr> factor();
  std::unique_ptr<Expr> unary();
  std::unique_ptr<Expr> primary();

  bool check(TokenType);
  bool isAtEnd();

  Token advance();
  Token peek();
  Token previous();

  template<typename Args...>
  bool match(Args... args) {
    for (TokenType type : {args...}) {
      if (check(type)) {
        advance();
        return true;
      }
    }

    return false;
  }

  const std::vector<Token> tokens;
  unsigned int current = 0;
};
