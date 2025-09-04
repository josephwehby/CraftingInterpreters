#include <iostream>
#include <fstream>
#include <vector>

void defineType(std::ofstream& file, std::string basename, std::string classname, std::string fields) {

}

void defineAST(std::string output_dir, std::string basename, std::vector<std::string> types) {
  std::string path = output_dir + "/" + basename + ".hpp";
  std::ofstream file(path);
  file << "#pragma once\n#include \"Expr.hpp\"\n";

  // we are going to inherit from Expr like 
  // : public Expr

  for (auto& type : types) {
    size_t pos = type.find(':');
    std::string classname = type.substr(0, pos);
    std::string fields = type.substr(pos+1, type.size()-pos);
    defineType(file, basename, classname, fields);
  }

  file.close();
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Usage: generate_ast <output_dir>" << std::endl;
    return 1;
  }

  defineAST(argv[1], "Expr", {
    "Binary:Expr left, Token operator, Expr right",
    "Grouping:Expr expression",
    "Literal:Object value",
    "Unary:Token operator, Expr right"
  });


}
