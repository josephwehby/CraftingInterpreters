#include <iostream>
#include "Expr.hpp"
#include "Token.hpp"
#include "PrettyPrinter.hpp"

int main() {
  auto expression = std::make_unique<Binary>(
    std::make_unique<Unary>(
      Token(TokenType::MINUS, "-", std::monostate{}, 1),
      std::make_unique<Literal>(123.0)
    ),
    Token(TokenType::STAR, "*", std::monostate{}, 1),
    std::make_unique<Grouping>(
      std::make_unique<Literal>(45.67)
    )
  );

  PrettyPrinter printer;

  std::cout << expression->accept(printer) << std::endl;
}
