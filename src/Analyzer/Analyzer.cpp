#include <iostream>
#include "Analyzer.h"
#include "../FrontEnd/Lexical/Lexical.h"
#include "../FrontEnd/Syntactic/Syntatic.h"
#include "../FrontEnd/Semantic/Semantic.h"

Analyzer::Analyzer(char *_musgonizer, long long int _length, std::string _flag)
{
  this->musgonizer = _musgonizer;
  this->length = _length;
  this->flag = _flag;
}

void Analyzer::run()
{
  Lexical lexical(this->musgonizer, this->length);
  std::deque<Production> tokens = lexical.run();
  // for (auto x : tokens)
  //   std::cout << x.token << "\n";
  Syntatic syntatic(tokens);
  // std::cout << "TESTETETETS" << std::endl;
  Semantic semantic(tokens);
  if (this->flag != "-sem")
  {
    std::cout << "ANÁLISE COMPLETA" << std::endl;
    AST ast = syntatic.run();
    semantic.run();
    ast.dump();
  }
  else
  {
    semantic.run();
  }
}