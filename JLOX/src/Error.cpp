#include "Error.hpp"

bool Error::hadError = false;

void Error::error(int line, std::string message) {
  report(line, "", message);
}

void Error::error(Token token, std::string message) {
  if (token.type == TokenType::END) {
    report(token.line, " at end", message);
  } else {
    report(token.line, " at '" + token.lexeme + "'", message);
  }
}

void Error::report(int line, std::string where, std::string message) {
  std::cout << "[line " << line << "] Error" << where << ": " << message << std::endl;
  hadError = true;
}
