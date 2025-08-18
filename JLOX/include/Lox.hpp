#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Token.hpp"
#include "Helper.hpp"
#include "Scanner.hpp"

class Lox {
public:
  void runFile(const std::string);
  void runPrompt();
private:
  void run(std::string);
  void report(int, std::string, std::string);
  void error(int, std::string);
  bool has_error = false;
};
