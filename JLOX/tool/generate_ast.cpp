#include <algorithm>
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

std::string lower(std::string text) {
  std::transform(text.begin(), text.end(), text.begin(), 
                 [](unsigned char a){ return std::tolower(a); });
  return text;
}

void defineType(std::ofstream& file, std::string basename, std::string classname, std::string fields, std::vector<std::string> visitor_types) {

  file << "class " << classname << " : public " << basename << " {\n";
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

  for (const auto& visitor : visitor_types) {
    file << "  ";
    std::string return_type = lower(visitor);
    if (return_type == "string") {
      file << "std::";
    }
    file << return_type;
    file << " accept(Visitor" << basename << visitor << "& " << "visitor) override {\n";
    file << "    return visitor.Visit" << classname << "(*this);\n";
    file << "  }\n\n";
  }

  file << member_variables;

  file << "};\n\n";
}

void defineVisitor(std::ofstream& file, std::string basename, std::vector<std::string> classnames, std::string visitor_class_type) {
  file << "class Visitor" << basename << visitor_class_type << " {\n";
  file << "public:\n";

  std::string return_type = lower(visitor_class_type);

  for (auto& classname : classnames) {
    file << "  virtual ";
    if (return_type == "string") {
      file << "std::string ";
    } else {
      file << return_type << " ";
    }
    file << "Visit" << classname << "(";
    file << classname << "& " << lower(basename); 
    file << ") = 0;\n";
  }

  file << "};\n\n";
}

void defineAST(std::string output_dir, std::string basename, std::vector<std::string> types, std::vector<std::string> visitors) {
  std::string path = output_dir + "/" + basename + ".hpp";
  std::ofstream file(path);
  file << "#pragma once\n\n";
  file << "#include <memory>\n";
  file << "#include \"Token.hpp\"\n\n";

  std::vector<std::string> classnames;
  std::vector<std::string> fields;

  for (auto& type : types) {
    size_t pos = type.find(':');
    std::string name = type.substr(0, pos);
    std::string field = type.substr(pos+1, type.size()-pos);
    classnames.push_back(name);
    fields.push_back(field);
  }

  for (auto& visitor : visitors) {
    file << "class Visitor" << basename << visitor << ";\n";
  }

  for (const auto& name : classnames) {
    file << "class " << name << ";\n";
  }

  file << "\nclass " << basename << " {\n";
  file << "public:\n";
  file << "  virtual ~" << basename << "() = default;\n";
  for (const auto& visitor : visitors) {
    file << "  virtual ";
    std::string return_type = lower(visitor);
    if (return_type == "string") {
      file << "std::";
    }
    file << return_type;
    file << " accept(Visitor" << visitor << "&) = 0;\n";
  }
  file << "};\n\n";

  for (const auto& visitor : visitors) {
    defineVisitor(file, basename, classnames, visitor);
  }

  for (int i = 0; i < classnames.size(); i++) {
    defineType(file, basename, classnames[i], fields[i], visitors);
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
  }, {"String", "Object"});

  defineAST(argv[1], "Stmt", {
    "Expression:Expr expression",
    "Print:Expr expression"
  }, {"Void","Object"});
}
