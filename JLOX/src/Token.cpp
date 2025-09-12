#include "Token.hpp"

Token::Token(TokenType type_, std::string lexeme_, Object literal_, int line_) : type(type_), lexeme(lexeme_), literal(literal_), line(line_) {}

std::string Token::toString() {

  std::string token_type = std::to_string(line) + ": " + tokenTypeToString(type);

  if (holds_alternative<double>(literal)) {
    return token_type + " " + lexeme + " " + std::to_string(std::get<double>(literal));
  } else if (holds_alternative<std::string>(literal)){
    return token_type + " " + lexeme + " " + std::get<std::string>(literal);
  } else if (holds_alternative<bool>(literal)) {
    return token_type + " " + lexeme + " " + std::to_string(std::get<bool>(literal));
  } else {
    return token_type + " " + lexeme + " null" ;
  }
}

