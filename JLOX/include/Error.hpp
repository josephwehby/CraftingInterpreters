#pragma once

#include "Token.hpp"

#include <iostream>
#include <string>

class Error {
public:
  static void error(int, std::string);
  static void error(Token, std::string);
  static void report(int, std::string, std::string);
  static bool hadError;
};
