#include "Parser.hpp"

Parser::Parser(std::vector<Token> tokens_) : tokens(tokens_) {}

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
    expr = std::make_unique<Binary>(std::move(epxr), op, std::move(right));
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

  if (match(TokenType::LEFT_PAREN)) {
    auto expr = expression();
    consume(TokenType::RIGHT_PAREN, "Expect ) after expression");
    return std::make_unique<Grouping>(std::move(expr));
  }
}

bool Parser::check(TokenType type) {
  if (isAtEnd()) return false;
  return peek().type == type;
}

bool Parser::isAtEnd() {
  return peek().type == TokenType::END;
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
