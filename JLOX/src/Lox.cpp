#include "Lox.hpp"

void Lox::runFile(const std::string file) {
  std::ifstream input_file(file);

  std::string text( (std::istreambuf_iterator<char>(input_file)), 
                   (std::istreambuf_iterator<char>()) );
  input_file.close();

  run(text);

  if (Error::hadError || Error::hadRuntimeError) return;
}

void Lox::runPrompt() {
  std::string line;
  std::cout << "> ";

  while (std::getline(std::cin, line)) {
    if (std::cin.eof()) break;
    run(line);
    Error::hadError = false;
    std::cout << "> ";
  }
}

void Lox::run(std::string text) {
  Scanner scanner(text);
  std::vector<Token> tokens = scanner.scanTokens();

  Parser parser(tokens);
  auto statements = parser.parse();

  if (Error::hadError) return;

  interpreter.interpret(statements);
}
