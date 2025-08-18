#pragma once

#include <variant>
#include <string>

#include "TokenType.hpp"
#include "Helper.hpp"

using Object = std::variant<std::monostate, std::string, double>;

class Token {
public:
  Token(TokenType, std::string, Object, int);
  std::string toString();
private:
  TokenType type;
  std::string lexeme;
  Object literal;
  int line;
};
