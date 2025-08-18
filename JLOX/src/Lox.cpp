#include "Lox.hpp"

void Lox::runFile(const std::string file) {
  std::ifstream input_file(file);

  std::string text( (std::istreambuf_iterator<char>(input_file)), 
                   (std::istreambuf_iterator<char>()) );
  input_file.close();

  run(text);

  if (has_error) return;
}

void Lox::runPrompt() {
  std::string line;
  std::cout << "> ";

  while (std::getline(std::cin, line)) {
    if (std::cin.eof()) break;
    run(line);
    has_error = false;
    std::cout << "> ";
  }
}

void Lox::run(std::string text) {
  Scanner scanner(text);
  std::vector<Token> tokens = scanner.scanTokens();

  if (scanner.hasError()) has_error = true;

  for (Token token : tokens) {
    std::cout << token.toString() << std::endl;
  }
}
