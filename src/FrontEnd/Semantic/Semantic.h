#include "SymbolTable.h"
#include "../Types/Production.cpp"
#include <deque>

class Semantic
{
public:
  Semantic(std::deque<Production> _tokenList);
  void run();

private:
  SymbolTable symbolTable;
  std::deque<Production> tokenList;
  int proccessOperation(int i);
};