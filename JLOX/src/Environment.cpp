#include "Environment.hpp"

void Environment::define(std::string name, Object value) {
  values[name] = value;
}

Object Environment::get(Token name) {
  if (values.contains(name.lexeme)) {
    return values[name.lexeme];
  }

  throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
}
