#include "SymbolTable.h"
#include "../Types/Symbol.cpp"

constexpr unsigned int str2int(const char *str, int h = 0)
{
  return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

void SymbolTable::add(std::string name, std::string type)
{
  if (!this->contains(name))
  {
    Symbol symbol = std::make_pair(name, SymbolParams(type, "0"));

    switch (str2int(type.c_str()))
    {
    case str2int("i32"):
      symbol = std::make_pair(name, SymbolParams(type, "0"));
      break;
    case str2int("i64"):
      symbol = std::make_pair(name, SymbolParams(type, "0"));
      break;
    case str2int("f32"):
      symbol = std::make_pair(name, SymbolParams(type, "0.0"));
      break;
    case str2int("f64"):
      symbol = std::make_pair(name, SymbolParams(type, "0.0"));
      break;
    case str2int("char"):
      symbol = std::make_pair(name, SymbolParams(type, "\0"));
      break;
    case str2int("bool"):
      symbol = std::make_pair(name, SymbolParams(type, "false"));
      break;
    }
    this->table.insert(symbol);
  }
  else
  {
    std::cout << "Error: Symbol " << name << " already exists in the table." << std::endl;
  }
}

bool SymbolTable::contains(std::string name)
{
  return this->table.find(name) != this->table.end();
}
