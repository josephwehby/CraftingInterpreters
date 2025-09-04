#pragma once

#include <cctype>
#include <string>
#include <vector>
#include <unordered_map>

#include "Token.hpp"
#include "Helper.hpp"

class Scanner {
public:
  Scanner(std::string&);
  std::vector<Token> scanTokens();
  bool hasError();
private:
  void scanToken();
  void string();
  void number();
  void identifier();
  void blockComment();
  char advance();
  void addToken(TokenType);
  void addToken(TokenType, Object);
  bool match(char);
  char peek();
  char peekNext();

  std::string text;
  std::vector<Token> tokens;

  unsigned int start = 0;
  unsigned int current = 0;
  unsigned int line = 1;

  bool has_error = false;

  std::unordered_map<std::string, TokenType> keywords = {
    {"and", TokenType::AND},
    {"class", TokenType::CLASS},
    {"else", TokenType::ELSE},
    {"false", TokenType::FALSE},
    {"for", TokenType::FOR},
    {"fun", TokenType::FUN},
    {"if", TokenType::IF},
    {"nil", TokenType::NIL},
    {"or", TokenType::OR},
    {"print", TokenType::PRINT},
    {"return", TokenType::RETURN},
    {"super", TokenType::SUPER},
    {"this", TokenType::THIS},
    {"true", TokenType::TRUE},
    {"var", TokenType::VAR},
    {"while", TokenType::WHILE},
  };

};
