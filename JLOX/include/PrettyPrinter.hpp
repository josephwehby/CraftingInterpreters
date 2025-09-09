#include "Expr.hpp"

class PrettyPrinter : public VisitorString {
public:
  std::string VisitBinary(Binary& expr) override;
  std::string VisitGrouping(Grouping& expr) override;
  std::string VisitLiteral(Literal& expr) override;
  std::string VisitUnary(Unary& expr) override;
private:
  template<typename... Exprs>
  std::string parenthesize(const std::string& name, Exprs&... exprs) {
    std::string result = "(" + name;
    ((result += " " + exprs.accept(*this)), ...);
    result += ")";
    return result;
  }
}
