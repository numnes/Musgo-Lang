#include "SymbolTable.h"
#include "../Types/Symbol.cpp"

SymbolTable::SymbolTable()
{
  this->table = std::unordered_map<std::string, SymbolParams>();
}

/** 
 * @param str *char - Vetor de caracteres
 * @param type std::string - Novo tipo da variável
 * @return int
 * @brief Converte um vetor de caracteres em um inteiro
*/
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

/** 
 * @param name std::string - Nome da variável
 * @return bool
 * @brief Verifica se a variável existe
*/
bool SymbolTable::contains(std::string name)
{
  return this->table.find(name) != this->table.end();
}

/** 
 * @param name std::string - Nome da variável
 * @param type std::string - Novo tipo da variável
 * @return void
 * @brief Modifica o tipo da variável na tabela de simbolos
*/
void SymbolTable::update(std::string name, std::string type)
{
  if (this->contains(name))
  {
    this->table.find(name)->second.type = type;
  }
  else
  {
    std::cout << "ERRO SEMÂNTICO: Não é possivel alterar o tipo da variável " << name << ", não existe declaração prévia." << std::endl;
  }
}

/** 
 * @param name std::string - Nome da variável
 * @return SymbolParams
 * @brief Retorna os parametros da variável, se ela existe
*/
SymbolParams SymbolTable::get(std::string name)
{
  if (this->contains(name))
  {
    return this->table.find(name)->second;
  }
  else
  {
    std::cout << "ERRO SEMÂNTICO: A váriável " << name << " não foi declarada." << std::endl;
    exit(1);
  }
}

/** 
 * @return void
 * @brief Printa a tabela de simbolos
*/
void SymbolTable::print()
{
  for (auto &symbol : this->table)
  {
    std::cout << symbol.first << ": " << symbol.second.type << " " << symbol.second.value << std::endl;
  }
}
