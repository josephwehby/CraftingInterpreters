#pragma once

#include <variant>
#include <string>

using Object = std::variant<std::monostate, std::string, double, bool>;
