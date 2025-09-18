#pragma once

#include <unordered_map>
#include <string>

#include "Token.hpp"
#include "Object.hpp"
#include "RuntimeError.hpp"

class Environment {
public:
  void define(std::string, Object);
  Object get(Token);
private:
  std::unordered_map<std::string, Object> values;
};
