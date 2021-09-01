#include <unordered_map>
#include <string>
#include <iostream>
#include "../Types/Symbol.cpp"

class SymbolTable
{
public:
  SymbolTable();
  ~SymbolTable();
  void add(std::string name, std::string type);
  void update(std::string name, std::string value);
  int get(std::string name);
  bool contains(std::string name);
  void print();

private:
  std::unordered_map<std::string, SymbolParams> table;
};
