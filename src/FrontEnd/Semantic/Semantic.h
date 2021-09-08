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
  int proccessAtribuitionExpression(int i);
  void solveOperation(std::deque<Production> tokenList);
};