#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

void defineType(std::ofstream& file, std::string basename, std::string classname, std::string fields) {

  file << "class " << classname << " : public Expr {\n";
  file << "  public:\n";
  file << "    " << classname << "(" << fields << ") {\n"; 

  std::stringstream ss(fields);
  std::string field;

  while (std::getline(ss, field, ',')) {
    size_t pos = field.find(' ');
    std::string name = field.substr(pos+1, field.size() - pos);
    file << "        this->" << name << " = " << name << ";\n";
  }

  file << "    }\n\n";

  ss.clear();
  ss.str("");
  ss << fields;
  while (std::getline(ss, field, ',')) {
    file << "    " << field << ";\n";
  }

  file << "};\n\n";
}

void defineAST(std::string output_dir, std::string basename, std::vector<std::string> types) {
  std::string path = output_dir + "/" + basename + ".hpp";
  std::ofstream file(path);
  file << "#pragma once\n\n#include \"Expr.hpp\"\n\n";


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

  defineAST(argv[1], "Exprs", {
    "Binary:Expr left,Token operator,Expr right",
    "Grouping:Expr expression",
    "Literal:Object value",
    "Unary:Token operator,Expr right"
  });


}
