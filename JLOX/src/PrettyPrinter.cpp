#include "PrettyPrinter.hpp"

std::string PrettyPrinter::VisitBinary(Binary& expr) {
  return parenthesize(expr.op.lexeme, *expr.left, *expr.right); 
}

std::string PrettyPrinter::VisitGrouping(Grouping& expr) {
  return parenthesize("grouping", *expr.expression);
}

std::string PrettyPrinter::VisitLiteral(Literal& expr) {
  if (std::holds_alternative<double>(expr.value)) {
    return std::to_string(std::get<double>(expr.value));
  } else if (std::holds_alternative<std::string>(expr.value)) {
    return std::get<std::string>(expr.value);
  }

  return "nil";
}

std::string PrettyPrinter::VisitUnary(Unary& expr) {
  return parenthesize(expr.op.lexeme, *expr.right);
}
