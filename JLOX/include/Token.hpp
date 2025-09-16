#pragma once

#include <variant>
#include <string>

#include "Object.hpp"
#include "TokenType.hpp"
#include "Helper.hpp"

using Object = std::variant<std::monostate, std::string, double, bool>;

class Token {
public:
  Token(TokenType, std::string, Object, int);
  std::string toString();

  TokenType type;
  std::string lexeme;
  Object literal;
  unsigned int line;
};
