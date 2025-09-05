#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

std::vector<std::string> split(const std::string& fields, char delim) {
  std::stringstream ss(fields);
  std::vector<std::string> items;

  std::string item;
  while (std::getline(ss, item, delim)) {
    items.push_back(item);
  }

  return items;
}


void defineType(std::ofstream& file, std::string basename, std::string classname, std::string fields) {

  file << "class " << classname << " : public Expr {\n";
  file << "public:\n";
  file << "  " << classname << "(";

  std::vector<std::string> params = split(fields, ',');
  std::vector<std::string> names;

  std::string param_list = "";
  std::string member_variables = "  ";
  for (int i = 0; i < params.size(); i++) {
    std::stringstream ss(params[i]);
    std::string type, name;
    ss >> type >> name;

    names.push_back(name);

    if (type == "Expr") {
      param_list += "std::unique_ptr<Expr>";
      member_variables += "std::unique_ptr<Expr>";
    } else {
      param_list += type; 
      member_variables += type;
    }
    param_list += " ";
    param_list += name;
    member_variables += " ";
    member_variables += name;
    member_variables += ";\n";
    if (i+1 < params.size()) {
      param_list += ", ";
      member_variables += "  ";
    }
  }

  file << param_list;
  file << ") : \n      ";

  for (int i = 0; i < names.size(); i++) {
    std::string name = names[i];
    file << name << "(std::move(" << name << "))"; 
    if (i+1 < names.size()) file << ", ";
  }

  file << "{}\n\n";

  file << member_variables;

  file << "};\n\n";
}

void defineVisitor(std::ofstream& file, std::string basename, std::vector<std::string> types) {
  file << "class Visitor{\n";
  file << "  "
}

void defineAST(std::string output_dir, std::string basename, std::vector<std::string> types) {
  std::string path = output_dir + "/" + basename + ".hpp";
  std::ofstream file(path);
  file << "#pragma once\n\n";
  file << "#include <memory>\n";
  file << "#include \"Token.hpp\"\n\n";
  file << "class Expr {\n";
  file << "public:\n";
  file << "  virtual ~Expr() = default;\n";
  file << "  virtual void accept(Visitor&) = 0\n";
  file << "};\n\n";

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
    "Binary:Expr left,Token op,Expr right",
    "Grouping:Expr expression",
    "Literal:Object value",
    "Unary:Token op,Expr right"
  });


}
