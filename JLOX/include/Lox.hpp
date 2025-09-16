#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Token.hpp"
#include "Helper.hpp"
#include "Error.hpp"
#include "Scanner.hpp"
#include "Parser.hpp"
#include "PrettyPrinter.hpp"
#include "Interpreter.hpp"

class Lox {
public:
  void runFile(const std::string);
  void runPrompt();
private:
  void run(std::string);
  Interpreter interpreter;
};
