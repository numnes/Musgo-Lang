#include <deque>
#include "Semantic.h"
#include "SymbolTable.h"
#include "../Types/Production.cpp"

Semantic::Semantic(std::deque<Production> _tokenList)
{
  this->tokenList = _tokenList;
  this->symbolTable = SymbolTable();
}

int Semantic::proccessOperation(int pos)
{
  std::deque<Production> pila;
  Production var = this->tokenList[pos - 2];

  for (int i = pos; i < this->tokenList.size(); i++)
  {
    if (this->tokenList[i].token == "id")
    {
      pila.push_back(this->tokenList[i]);
    }
  }
  //i32 a = b + c * (i32)(2.5 + 4.3);
}

void Semantic::run()
{
  bool error = false;
  std::deque<Production> tokens;
  for (int i = 0; i < this->tokenList.size(); i++)
  {
    if (this->tokenList[i].token == "type")
    {
      if (i + 1 < this->tokenList.size() && this->tokenList[i + 1].token == "id")
      {
        this->symbolTable.add(this->tokenList[i + 1].lex, this->tokenList[i].lex);
      }
      if (i + 2 < this->tokenList.size() && this->tokenList[i + 2].token == ";")
      {
        i += 2;
      }
      else if (i + 2 < this->tokenList.size() && this->tokenList[i + 2].token == "")
    }
  }
}
