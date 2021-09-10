#ifndef _SEMANTIC_SYMBOLTABLE_H
#define _SEMANTIC_SYMBOLTABLE_H

#include <unordered_map>
#include <string>
#include <iostream>
#include "../Types/Symbol.cpp"

class SymbolTable
{
public:
  SymbolTable();
  void add(std::string name, std::string type, int size);
  void update(std::string name, std::string type);
  SymbolParams get(std::string name);
  bool contains(std::string name);
  void print();
  void run();

private:
  std::unordered_map<std::string, SymbolParams> table;
};

#endif