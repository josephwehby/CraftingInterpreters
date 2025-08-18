#include <iostream>
#include <string>

#include "Lox.hpp"

int main(int argc, char* argv[]) {

  Lox lox;
  if (argc <= 1) {
    lox.runPrompt();
  } else if (argc == 2) {
    std::string file = argv[1];
    lox.runFile(file);
  } else {
    std::cout << "Usage: ./jlox [file]" << std::endl;
  }

  return 0;
}
