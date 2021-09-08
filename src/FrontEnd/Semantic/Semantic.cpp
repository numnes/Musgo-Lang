#include <deque>
#include "Semantic.h"
#include "SymbolTable.h"
#include "../Types/Production.cpp"
#include "../Types/Symbol.cpp"

Semantic::Semantic(std::deque<Production> _tokenList)
{
  this->tokenList = _tokenList;
  this->symbolTable = SymbolTable();
}

/** 
 * @param operation std::deque<Production> - Pilha de tokens da operação
 * @return void
 * @throws SemanticError
 * @brief Verificar se a operação aritimetica é válida
*/
void Semantic::solveOperation(std::deque<Production> operation)
{
  // Variável que armazena o resultado da operacao
  Production result = Production();
  // Pega o primeiro token da lista
  Production currentToken = operation.front();
  // Remove o primeiro token da lista
  operation.pop_front();

  // Guarda o tipo do token na posição corrente
  std::string currentType;

  // Se o token corrente for uma variável busca seu tipo na tabela de simbolos
  if (currentToken.token == "id")
  {
    if (this->symbolTable.contains(currentToken.lex))
    {
      currentType = this->symbolTable.get(currentToken.lex).type;
    }
    // Se a variável não foi declarada anteriormente gera um erro
    else
    {
      std::cout << "Erro semântico: variável " << currentToken.lex << " não declarada. Linha "
                << currentToken.line << std::endl;
      exit(1);
    }
  }
  // Se o token não for uma variável então ela é um valor, assim é possível
  // Considerar apenas seu pseudo-tipo (num,float)
  else
  {
    currentType = currentToken.lex;
  }

  // Itera até chegar ao fim da expressão
  while (!operation.empty() && operation.front().token != "par_left")
  {
    if (operation.front().token == "op")
    {
      // Se o token for um operador retira ele da expressão
      operation.pop_front();
      // Pega o próximo operando
      Production nextToken = operation.front();
      // Guarda o tipo do proximo operando
      std::string nextType;
      // Remove o próximo operando da expressão
      operation.pop_front();

      // Se o próximo operando for uma variável busca seu tipo na tabela de simbolos
      if (nextToken.token == "id")
      {
        // Faz a mesma checagem usada no primeiro token
        if (this->symbolTable.contains(nextToken.lex))
        {
          nextType = this->symbolTable.get(nextToken.lex).type;
        }
        else
        {
          std::cout << "Erro semântico: variável " << nextToken.lex << " não declarada. Linha "
                    << nextToken.line << std::endl;
          exit(1);
        }
      }
      else
      {
        nextType = nextToken.lex;
      }

      // Guarda o resultado da operação
      result.line = currentToken.line;
      result.token = "result";
      // Trata a iteração entre os operandos
      if (nextType == currentType)
        result = currentToken;
      else
      {
        if ((currentType == "i32" && nextType == "num") || (currentType == "num" && nextType == "i32"))
          result.lex = "i32";
        else if ((currentType == "i64" && nextType == "num") || (currentType == "num" && nextType == "i64"))
          result.lex = "i64";
        else if ((currentType == "f32" && nextType == "float") || (currentType == "float" && nextType == "f32"))
          result.lex = "f32";
        else if ((currentType == "f64" && nextType == "float") || (currentType == "float" && nextType == "f64"))
          result.lex = "f64";
        else
        {
          std::cout << "Erro semântico: Operação entre tipos incompativeis. Linha "
                    << nextToken.line << std::endl;
          exit(1);
        }
      }
      currentToken = result;
      currentType = result.lex;
    }
  }
  // Remove o fechamento de parenteses da expressão
  operation.pop_front();

  // Empilha o resultado da expressão
  operation.push_front(result);
}

/** 
 * @param pos int -  Posição do inicio da atribuição
 * @return int
 * @throws SemanticError
 * @brief Verifica se a operação de atribuição aritimetica é válida
*/
int Semantic::proccessAtribuitionExpression(int pos)
{
  std::deque<Production> operation;
  Production var = this->tokenList[pos - 2];
  int curretPosition = pos;

  while (this->tokenList[curretPosition].lex != ";")
  {
    // TODO: Verificar se o fechamento de parenteses não pertence a um cast
    if (this->tokenList[curretPosition].token == "par_right")
    {
      solveOperation(operation);
    }
    else
    {
      operation.push_back(this->tokenList[curretPosition]);
    }
    curretPosition++;
  }
  solveOperation(operation);
  if (var.lex == operation.front().lex)
  {
    return curretPosition;
  }
  else
  {
    std::cout << "Erro semântico: Operação resulta em tipo incompativel com a variável. Linha "
              << var.line << std::endl;
    exit(1);
  }
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
      {
        // PLACEHOLDER
        i += 2;
      }
    }
  }
}
