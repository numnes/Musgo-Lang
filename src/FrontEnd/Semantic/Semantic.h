#include "SymbolTable.h"
#include "../Types/Production.cpp"
#include <deque>
#include <string>

class Semantic
{
public:
  Semantic(std::deque<Production> _tokenList);
  void run();

private:
  SymbolTable symbolTable;
  std::deque<Production> tokenList;
  int proccessAtribuitionExpression(int pos, Production var);
  int proccessLogicExpression(int pos);
  int proccessExpression(int pos);
  std::deque<Production> solveOperation(std::deque<Production> tokenList);
};