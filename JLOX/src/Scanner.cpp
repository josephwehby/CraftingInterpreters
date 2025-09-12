#include "Scanner.hpp"

Scanner::Scanner(std::string& text_) : text(text_) {}

std::vector<Token> Scanner::scanTokens() {
  while (current < text.size()) {
    start = current;
    scanToken();
  }

  tokens.emplace_back(TokenType::END, "", "", line);
  return tokens;
}

void Scanner::scanToken() {
  char c = advance(); 
  switch (c) {
    case '(': addToken(TokenType::LEFT_PAREN); break;
    case ')': addToken(TokenType::RIGHT_PAREN); break;
    case '{': addToken(TokenType::LEFT_BRACE); break;
    case '}': addToken(TokenType::RIGHT_BRACE); break;
    case ',': addToken(TokenType::COMMA); break;
    case '.': addToken(TokenType::DOT); break;
    case '-': addToken(TokenType::MINUS); break;
    case '+': addToken(TokenType::PLUS); break;
    case ';': addToken(TokenType::SEMICOLON); break;
    case '*': addToken(TokenType::STAR); break;
    case '!': 
      addToken( (match('=')) ? TokenType::BANG_EQUAL : TokenType::BANG);
      break;
    case '=':
      addToken( (match('=')) ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
      break;
    case '<':
      addToken( (match('=')) ? TokenType::LESS_EQUAL : TokenType::LESS);
      break;
    case '>':
      addToken( (match('=')) ? TokenType::GREATER_EQUAL : TokenType::GREATER);
      break;
    case '/':
      if (match('/')) {
        while(peek() != '\n' && current < text.size()) advance();
      } else if (match('*')) {
        blockComment();
      } else {
        addToken(TokenType::SLASH);
      }
      break;
    case ' ':
    case '\r':
    case '\t':
      break;
    case '\n': line++; break;
    case '"': string(); break;
    default: 
      if (isdigit(c)) {
        number();
      } else if (isalpha(c)) {
        identifier();
      } else {
        Error::error(line, "Unexpected character.");
      }
  };
}

void Scanner::string() {
  while (peek() != '"' && current < text.size()) {
    if (peek() == '\n') line++;
    advance();
  }

  if (current >= text.size()) {
    Error::error(line, "Unterminated string.");
    return;
  }

  advance();

  std::string value = text.substr(start+1, current-start-2);
  addToken(TokenType::STRING, value);
}

void Scanner::number() {
  while (isdigit(peek())) advance();
  if (peek() == '.' && isdigit(peekNext())) {
    advance();
    while (isdigit(peek())) advance();
  }

  std::string value = text.substr(start, current-start);
  double number = std::stod(value);

  addToken(TokenType::NUMBER, number); 
}

void Scanner::identifier() {
  while (isalnum(peek())) advance();

  std::string word = text.substr(start, current-start);

  TokenType type;
  if (keywords.contains(word)) {
    type = keywords[word];
  } else {
    type = TokenType::IDENTIFIER;
  }

  addToken(type);
}

void Scanner::blockComment() {
  while (current < text.size()) {

    if (peek() == '*' && peekNext() == '/') {
      advance();
      advance();
      return; 
    }

    if (peek() == '\n') line++;
    advance();
  }

  Error::error(line, "No closing */ for block comment.");
}

char Scanner::advance() {
  char c = text[current];
  current++;
  return c;
}

void Scanner::addToken(TokenType type) {
  addToken(type, std::monostate{});
}

void Scanner::addToken(TokenType type, Object literal) {
  std::string lexeme = text.substr(start, current-start);
  tokens.emplace_back(type, lexeme, literal, line);
}

bool Scanner::match(char expected) {
  if (current >= text.size()) return false;
  if (text[current] != expected) return false;

  current++;
  return true;
}

char Scanner::peek() {
  if (current >= text.size()) return '\0';
  return text[current];
}

char Scanner::peekNext() {
  if (current+1 >= text.size()) return '\0';
  return text[current+1];
}
