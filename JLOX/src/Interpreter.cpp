#include "Interpreter.hpp"

void Interpreter::interpret(const std::vector<std::unique_ptr<Stmt>>& statements) {
  try {
    for (auto& statement : statements) {
      execute(statement);
    }
  } catch (const RuntimeError& error) {
    Error::runtimeError(error);
  }
}

void Interpreter::execute(const std::unique_ptr<Stmt>& stmt) {
  stmt->accept(*this);
}

Object Interpreter::VisitBinaryExpr(Binary& expr) {
  Object left = evaluate(*expr.left);
  Object right = evaluate(*expr.right);

  switch (expr.op.type) {
    case TokenType::GREATER:
      checkNumberOperands(expr.op, left, right);
      return toDouble(left) > toDouble(right);
    case TokenType::GREATER_EQUAL:
      checkNumberOperands(expr.op, left, right);
      return toDouble(left) >= toDouble(right);
    case TokenType::LESS:
      checkNumberOperands(expr.op, left, right);
      return toDouble(left) < toDouble(right);
    case TokenType::LESS_EQUAL:
      checkNumberOperands(expr.op, left, right);
      return toDouble(left) <= toDouble(right);
    case TokenType::BANG_EQUAL:
      return !isEqual(left,right);
    case TokenType::EQUAL_EQUAL:
      return isEqual(left,right);
    case TokenType::MINUS:
      checkNumberOperands(expr.op, left, right);
      return toDouble(left) - toDouble(right);
    case TokenType::SLASH:
      checkNumberOperands(expr.op, left, right);
      return toDouble(left) / toDouble(right);
    case TokenType::STAR:
      checkNumberOperands(expr.op, left, right);
      return toDouble(left) * toDouble(right);
    case TokenType::PLUS:
      if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) {
        return toDouble(left) + toDouble(right);
      }

      if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right)) { 
        return toString(left) + toString(right);
      }

      throw RuntimeError(expr.op, "Operands must be two numbers or two strings.");
    default:
      return {};
  }

  return {};
}

Object Interpreter::VisitGroupingExpr(Grouping& expr) {
  return evaluate(*expr.expression);
}


Object Interpreter::VisitLiteralExpr(Literal& expr) {
  return expr.value;
}


Object Interpreter::VisitUnaryExpr(Unary& expr) {
  Object right = evaluate(*expr.right);

  switch (expr.op.type) {
    case TokenType::MINUS:
      checkNumberOperand(expr.op, right);
      if (auto num = std::get_if<double>(&right)) {
        return -(*num);
      }
    case TokenType::BANG:
      return !isTruthy(right);
    default:
      return {};
  }

  return {};
}

Object Interpreter::VisitVariableExpr(Variable& expr) {
  return env.get(expr.name);
}

void Interpreter::VisitExpressionStmt(Expression& stmt) {
  evaluate(*stmt.expression);
}

void Interpreter::VisitPrintStmt(Print& stmt) {
  Object value = evaluate(*stmt.expression);
  std::cout << stringify(value) << std::endl;
}

void Interpreter::VisitVarStmt(Var& stmt) {
  Object value = std::monostate{};
  if (stmt.initializer != nullptr) {
    value = evaluate(*stmt.initializer);
  }

  env.define(stmt.name.lexeme, value);
}

Object Interpreter::evaluate(Expr& expr) {
  return expr.accept(*this);
}

bool Interpreter::isTruthy(const Object& object) {
  if (std::holds_alternative<std::monostate>(object)) return false;
  if (auto val = std::get_if<bool>(&object)) return *val;
  return true;
}

bool Interpreter::isEqual(const Object& left, const Object& right) {
  return left == right;
}

void Interpreter::checkNumberOperand(Token op, const Object& operand) {
  if (std::holds_alternative<double>(operand)) return;
  throw RuntimeError(op, "Operand must be a number.");
}

void Interpreter::checkNumberOperands(Token op, const Object& left, const Object& right) {
  if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) 
    return;
  throw RuntimeError(op, "Operands must be a numbers.");
}

std::string Interpreter::stringify(Object& object) {
  if (std::holds_alternative<std::monostate>(object)) return "nil";

  if (auto val = std::get_if<double>(&object)) {
    std::string text = std::to_string(*val);
    size_t pos = text.find('.');
    if (endsWithZero(text, pos)) return text.substr(0, pos);
    return text;
  }

  if (auto val = std::get_if<bool>(&object)) {
    return (*val == true) ? "true" : "false";
  }

  if (auto val = std::get_if<std::string>(&object)) return *val;

  return "something wrong";
}

bool Interpreter::endsWithZero(std::string& text, size_t pos) {
  for (auto i = pos+1; i < text.size(); i++) {
    if (text[i] != '0') return false;
  }

  return true;
}
