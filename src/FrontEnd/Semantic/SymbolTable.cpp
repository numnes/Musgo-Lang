#include "SymbolTable.h"
#include "../Types/Symbol.cpp"

SymbolTable::SymbolTable()
{
  this->table = std::unordered_map<std::string, SymbolParams>();
}

constexpr unsigned int str2int(const char *str, int h = 0)
{
  return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

/** 
 * @param name string - Nome da variável
 * @param type string - Tipo da variável
 * @param size int - Tamanho da variável
 * @return int
 * @throws SemanticError
 * @brief Verifica se a operação de atribuição aritimetica é válida
*/
void SymbolTable::add(std::string name, std::string type, int size)
{
  SymbolParams params = SymbolParams(type, "0", size);
  if (!this->contains(name))
  {
    switch (str2int(type.c_str()))
    {
    case str2int("i32"):
      params = SymbolParams(type, "0", size);
      break;
    case str2int("i64"):
      params = SymbolParams(type, "0", size);
      break;
    case str2int("f32"):
      params = SymbolParams(type, "0.0", size);
      break;
    case str2int("f64"):
      params = SymbolParams(type, "0.0", size);
      break;
    case str2int("char"):
      params = SymbolParams(type, "\0", size);
      break;
    case str2int("bool"):
      params = SymbolParams(type, "false", size);
      break;
    }
    this->table.insert(std::make_pair(name, params));
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

void SymbolTable::update(std::string name, std::string type, std::string value)
{
  if (this->contains(name))
  {
    this->table.find(name)->second.type = type;
    this->table.find(name)->second.value = value;
  }
  else
  {
    std::cout << "Error: Symbol " << name << " does not exist in the table." << std::endl;
  }
}

SymbolParams SymbolTable::get(std::string name)
{
  if (this->contains(name))
  {
    return this->table.find(name)->second;
  }
  else
  {
    std::cout << "Error: A váriável " << name << " não foi declarada." << std::endl;
    exit(1);
  }
}

void SymbolTable::print()
{
  for (auto &symbol : this->table)
  {
    std::cout << symbol.first << ": " << symbol.second.type << " " << symbol.second.value << std::endl;
  }
}
