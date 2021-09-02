#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <deque>
#include "../Utils/Utils.cpp"
#include "../Types/Production.cpp"
#include "Syntatic.h"

Syntatic::Syntatic(std::deque<Production> _productions)
{
  this->productions = _productions;
}

void Syntatic::run()
{
  std::string line;
  std::string line2;
  std::ifstream myfile("src/FrontEnd/data/Tabela_Preditiva.csv");
  std::getline(myfile, line);

  // Não terminais
  std::vector<std::string> Nterminais;

  std::vector<std::string> Terminais;
  bool exFirst = false;

  std::stringstream sline(line);
  while (std::getline(sline, line2, ','))
  {
    if (exFirst)
      Terminais.push_back(line2);
    exFirst = true;
  }

  std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> Table;

  while (std::getline(myfile, line))
  {
    std::stringstream sline(line);

    exFirst = true;

    // Não terminal chave
    std::string tableKey;

    // Derivações do não terminal
    std::unordered_map<std::string, std::vector<std::string>> derivationList;

    // Partes da derivação
    std::vector<std::vector<std::string>> derivations;

    // Derivações brutas
    std::vector<std::string> derivationsUnp;

    while (std::getline(sline, line2, ','))
    {
      if (exFirst)
      {
        tableKey = line2;
        exFirst = false;
      }
      else
        derivationsUnp.push_back(line2 + " ");
    }

    for (auto d : derivationsUnp)
    {
      std::vector<std::string> a = Utils::splitStr(d);
      derivations.push_back(a);
    }

    for (int i = 0; i < Terminais.size(); i++)
    {
      derivationList.insert(std::make_pair(Terminais[i], derivations[i]));
    }

    Nterminais.push_back(tableKey);
    Table.insert(std::make_pair(tableKey, derivationList));
  }

  std::vector<std::string> Pheap;

  Pheap.push_back("$");
  Pheap.push_back("program");

  Production p = {"$", " ", -1};
  this->productions.push_back(p);
  bool error = false;

  std::unordered_map<std::string, std::string> dictTerm = {
      {"semicolon", ";"},
      {"colon", ":"},
      {"bracket_left", "["},
      {"bracket_right", "]"},
      {"block_left", "{"},
      {"block_right", "}"},
      {"par_left", "("},
      {"par_right", ")"},
      {"comma", ","},
      {"in", "<-"},
      {"out", "->"}};

  while (!Pheap.empty())
  {
    // std::cout << "================================== heap\n";
    // for( auto a: Pheap)
    //     std::cout << "[" << a << "] ";
    // std::cout << "\n";
    // std::cout << "================================== entry\n";
    // for( auto a: productions)
    //     std::cout << "[" << a.token << "] ";
    // std::cout << "\n\n";
    std::string X = Pheap.back();
    std::string A = this->productions.front().token;

    if (std::find(Terminais.begin(), Terminais.end(), X) != Terminais.end())
    {
      if (X == A)
      {
        Pheap.pop_back();
        this->productions.pop_front();
      }
      else
      {
        std::cout << "\033[1;31mNão era esperado o token \033[0m" << dictTerm[A] << "\033[1;31m na linha \033[0m \033[1;35m" << this->productions.front().line
                  << "\033[0m\033[1;31m. Esperava-se:  \033[0m\033[1;34m" << dictTerm[X] << "\033[0m \n\n";
        error = true;
        this->productions.pop_front();
      }
    }
    else
    {
      if (!Table[X][A].empty())
      {
        Pheap.pop_back();
        for (auto rit = Table[X][A].rbegin(); rit != Table[X][A].rend(); rit++)
        {
          if (*rit != "ϵ")
            Pheap.push_back(*rit);
        }
      }
      else
      {
        std::cout << "\033[1;31mNão era esperado o token \033[0m" << dictTerm[A] << "\033[1;31m na linha \033[0m \033[1;35m" << this->productions.front().line
                  << "\033[0m\033[1;31m. Esperava-se uma das produções a seguir: \033[0m\n";

        for (auto a : Table[X])
          if (a.second.size() != 0)
            if (a.first != "$" && a.first != " " && a.first[0] != 13)
              std::cout << "  \033[1;34m" << ((dictTerm.count(a.first)) ? (dictTerm[a.first]) : (a.first)) << " \033[0m ";
        error = true;
        std::cout << "\n\n";
        this->productions.pop_front();
      }
    }
  }
  if (!error)
    std::cout << "\033[1;32m Nenhum erro encontrado!\033[0m\n";
  return;
}
