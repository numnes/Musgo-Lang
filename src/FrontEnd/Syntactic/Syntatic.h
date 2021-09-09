#include <deque>
#include <unordered_map>
#include <list>
#include "../Types/Production.cpp"
#include "../Intermediate/AST.h"

class Syntatic
{
public:
  Syntatic(std::deque<Production> _productions);
  AST run();

private:
  std::deque<Production> productions;
  void printError(std::string errorToken, std::unordered_map<std::string, std::list<std::string>> dictTerm);
};
