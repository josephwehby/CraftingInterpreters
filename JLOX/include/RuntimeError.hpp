#pragma once

#include <stdexcept>
#include <string>

class RuntimeError : public std::runtime_error {
public:
  Token token;

  RuntimeError(const Token& token, const std::string& message) : 
    std::runtime_error(message), token(token) {}

};
