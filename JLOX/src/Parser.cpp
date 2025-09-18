#include "Parser.hpp"

Parser::Parser(std::vector<Token> tokens_) : tokens(tokens_) {}

std::vector<std::unique_ptr<Stmt>> Parser::parse() {
  std::vector<std::unique_ptr<Stmt>> statements;

  while (!isAtEnd()) {
    statements.push_back(declaration());
  }

  return statements;
}

std::unique_ptr<Stmt> Parser::statement() {
  if (match(TokenType::PRINT)) return printStatement();
  return expressionStatement();
}

std::unique_ptr<Stmt> Parser::printStatement() {
  auto value = expression();
  consume(TokenType::SEMICOLON, "Expect ';' after value");
  return std::make_unique<Print>(std::move(value));
}

std::unique_ptr<Stmt> Parser::expressionStatement() {
  auto expr = expression();
  consume(TokenType::SEMICOLON, "Expect ';' after value");
  return std::make_unique<Expression>(std::move(expr));
}

std::unique_ptr<Stmt> Parser::declaration() {
  try {
    if (match(TokenType::VAR)) return varDeclaration();
    return statement();
  } catch (const ParseError& error) {
    synchronize();
    return nullptr;
  }
}

std::unique_ptr<Stmt> Parser::varDeclaration() {
  Token name = consume(TokenType::IDENTIFIER, "Expect variable name");

  std::unique_ptr<Expr> initializer = nullptr;
  if (match(TokenType::EQUAL)) {
    initializer = expression();
  }

  consume(TokenType::SEMICOLON, "Expect ';' after variable declaration");
  return std::make_unique<Var>(name, std::move(initializer));
}
std::unique_ptr<Expr> Parser::expression() {
  return equality();
}

std::unique_ptr<Expr> Parser::equality() {
  auto expr = comparison();

  while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
    Token op = previous();
    auto right = comparison();
    expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
  }

  return expr;
}

std::unique_ptr<Expr> Parser::comparison() {
  auto expr = term();

  while (match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL)) {
    Token op = previous();
    auto right = term();
    expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
  }

  return expr;
}

std::unique_ptr<Expr> Parser::term() {
  auto expr = factor();

  while (match(TokenType::MINUS, TokenType::PLUS)) {
    Token op = previous();
    auto right = factor();
    expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
  }

  return expr;
}

std::unique_ptr<Expr> Parser::factor() {
  auto expr = unary();

  while (match(TokenType::SLASH, TokenType::STAR)) {
    Token op = previous();
    auto right = unary();
    expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
  }

  return expr;
}

std::unique_ptr<Expr> Parser::unary() {
  if (match(TokenType::BANG, TokenType::MINUS)) {
    Token op = previous();
    auto right = unary();
    return std::make_unique<Unary>(op, std::move(right));
  }

  return primary();
}

std::unique_ptr<Expr> Parser::primary() {
  if (match(TokenType::FALSE)) return std::make_unique<Literal>(false);
  if (match(TokenType::TRUE)) return std::make_unique<Literal>(true);
  if (match(TokenType::NIL)) return std::make_unique<Literal>(std::monostate{});

  if (match(TokenType::NUMBER, TokenType::STRING)) {
    return std::make_unique<Literal>(previous().literal);
  }

  if (match(TokenType::IDENTIFIER)) return std::make_unique<Variable>(previous());


  if (match(TokenType::LEFT_PAREN)) {
    auto expr = expression();
    consume(TokenType::RIGHT_PAREN, "Expect ) after expression");
    return std::make_unique<Grouping>(std::move(expr));
  }

  error(peek(), "Expect expression.");
  return nullptr;
}

void Parser::synchronize() {
  advance();

  while (!isAtEnd()) {
    if (previous().type == TokenType::SEMICOLON) return;

    switch(peek().type) {
      case TokenType::CLASS:
      case TokenType::FUN:
      case TokenType::VAR:
      case TokenType::FOR:
      case TokenType::IF:
      case TokenType::WHILE:
      case TokenType::PRINT:
      case TokenType::RETURN:
        return;
      default:
        return;
    }

    advance();
  }
}

ParseError Parser::error(Token token, std::string message) {
  Error::error(token, message);
  return ParseError{};
}

bool Parser::check(TokenType type) {
  if (isAtEnd()) return false;
  return peek().type == type;
}

bool Parser::isAtEnd() {
  return peek().type == TokenType::END;
}

Token Parser::consume(TokenType type, std::string message) {
  if (check(type)) return advance();

  Error::error(peek(), message);
  return {TokenType::END, "", "", 0};
}

Token Parser::advance() {
  if (!isAtEnd()) current++;
  return previous();
}

Token Parser::peek() {
  return tokens[current];
}

Token Parser::previous() {
  return tokens[current - 1];
}
