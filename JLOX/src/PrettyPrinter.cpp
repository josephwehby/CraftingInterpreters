#include "PrettyPrinter.hpp"

std::string PrettyPrinter::VisitBinaryExpr(Binary& expr) {
  return parenthesize(expr.op.lexeme, *expr.left, *expr.right); 
}

std::string PrettyPrinter::VisitGroupingExpr(Grouping& expr) {
  return parenthesize("grouping", *expr.expression);
}

std::string PrettyPrinter::VisitLiteralExpr(Literal& expr) {
  if (std::holds_alternative<double>(expr.value)) {
    return std::to_string(std::get<double>(expr.value));
  } else if (std::holds_alternative<std::string>(expr.value)) {
    return std::get<std::string>(expr.value);
  }

  return "nil";
}

std::string PrettyPrinter::VisitUnaryExpr(Unary& expr) {
  return parenthesize(expr.op.lexeme, *expr.right);
}
