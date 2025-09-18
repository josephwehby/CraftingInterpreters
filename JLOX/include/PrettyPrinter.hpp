#include "Expr.hpp"

class PrettyPrinter : public VisitorExprString {
public:
  std::string VisitBinaryExpr(Binary& expr) override;
  std::string VisitGroupingExpr(Grouping& expr) override;
  std::string VisitLiteralExpr(Literal& expr) override;
  std::string VisitUnaryExpr(Unary& expr) override;
private:
  template<typename... Exprs>
  std::string parenthesize(const std::string& name, Exprs&... exprs) {
    std::string result = "(" + name;
    ((result += " " + exprs.accept(*this)), ...);
    result += ")";
    return result;
  }
};
