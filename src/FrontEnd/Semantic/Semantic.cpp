#include <deque>
#include <set>
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
  result = currentToken;
  // Remove o primeiro token da lista
  operation.pop_front();

  // Operadores logicos unários
  std::set<std::string> unLogOp = {"!", "not"};

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
  else if (currentToken.lex == "++" || currentToken.lex == "--")
  {
    if (operation.front().token == "id")
    {
      if (this->symbolTable.contains(operation.front().lex))
      {
        SymbolParams varUn = this->symbolTable.get(operation.front().lex);
        if (varUn.type == "i32" || varUn.type == "i64")
        {
          operation.pop_front();
        }
        else
        {
          std::cout << "Erro semântico: A operação unária não é compativel com o tipo da variável " << operation.front().lex << ". Linha "
                    << operation.front().line << std::endl;
          exit(1);
        }
      }
      else
      {
        std::cout << "Erro semântico: Variável " << operation.front().lex << " não declarada. Linha "
                  << operation.front().line << std::endl;
        exit(1);
      }
    }
    else
    {
      if (operation.front().token == "num")
      {
        operation.pop_front();
      }
      else
      {
        std::cout << "Erro semântico: A operação unária não é compativel com o valor " << operation.front().lex << ". Linha "
                  << operation.front().line << std::endl;
        exit(1);
      }
    }
  }
  // Se o token não for uma variável então ela é um valor, assim é possível
  // Considerar apenas seu pseudo-tipo (num,float)
  else
  {
    currentType = currentToken.lex;
  }

  // Processamento da expressão
  // Itera até chegar ao fim da expressão
  while (!operation.empty() && operation.front().token != "par_left")
  {
    if (operation.front().token == "op")
    {
      // Pega o operador
      Production currentOperator = operation.front();
      // Retira o operador da expressão
      operation.pop_front();
      // Pega o próximo operando
      Production nextToken = operation.front();
      // Guarda o tipo do proximo operando
      std::string nextType;
      // Remove o próximo operando da expressão

      std::string forcedType = "";

      if (unLogOp.find(currentOperator.token) != unLogOp.end())
      {
        if (currentToken.token == "id")
        {
          if (this->symbolTable.contains(currentToken.lex))
          {
            if (this->symbolTable.get(currentToken.lex).type == "bool")
            {
              currentType = "bool";
              continue;
            }
            else
            {
              std::cout << "Erro semântico: A operação unária não é compativel com o tipo da variável " << currentToken.lex << ". Linha "
                        << currentToken.line << std::endl;
              exit(1);
            }
          }
          else
          {
            std::cout << "Erro semântico: Variável " << operation.front().lex << " não declarada. Linha "
                      << operation.front().line << std::endl;
            exit(1);
          }
        }
        else if (currentToken.token == "bool")
        {
          currentType = "bool";
          continue;
        }
        else
        {
          std::cout << "Erro semântico: A operação logica não é compativel com o valor " << currentToken.lex << ". Linha "
                    << currentToken.line << std::endl;
          exit(1);
        }
      }
      else
      {
        operation.pop_front();
      }

      if (currentOperator.token == "rel_op" || currentOperator.token == "rel_op")
      {
        forcedType = "bool";
      }

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
      if (forcedType != "")
      {
        nextType = forcedType;
      }
      currentToken = result;
      currentType = result.lex;
    }
  }

  // Remove o fechamento de parenteses da expressão
  if (!operation.empty())
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

  while (this->tokenList[curretPosition].lex != ";" && this->tokenList[curretPosition].lex != "{")
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
    // É uma declaração de variável
    if (this->tokenList[i].token == "type" && this->tokenList[i + 1].token == "id")
    {
      // Verifica se a variável já foi declarada
      if (!this->symbolTable.contains(this->tokenList[i + 1].lex))
      {
        this->symbolTable.add(this->tokenList[i + 1].lex, this->tokenList[i].lex, 0);
        // Se é apenas uma declaração, continua a execução
        if (i + 2 < this->tokenList.size() && this->tokenList[i + 2].token == ";")
        {
          i += 2;
        }
        // Se possui uma atribuição na declaração, processa a expressão atribuida
        else if (i + 2 < this->tokenList.size() && this->tokenList[i + 2].token == "as_op")
        {
          i = proccessAtribuitionExpression(i + 3);
        }
        // Sei lá, não vai chegar aqui nunca
        else
        {
          std::cout << "Não era pra ter chegado aqui";
        }
      }
      // Se foi declarada anteriormente gera um erro
      else
      {
        std::cout << "Erro semântico: A variável " << this->tokenList[i + 1].lex << " já foi declarada anteriormente. Linha "
                  << this->tokenList[i + 1].line << std::endl;
        exit(1);
      }
    }
    // É uma atribuição
    if (this->tokenList[i].token == "id")
    {
      // Verifica se a variável já foi declarada
      if (this->symbolTable.contains(this->tokenList[i].lex))
      {
        if (i + 1 < this->tokenList.size() && this->tokenList[i + 1].token == "as_op")
        {
          if (this->tokenList[i + 1].lex == "++" || this->tokenList[i + 1].lex == "--")
          {
            if (this->symbolTable.get(this->tokenList[i].lex).type == "i32" || this->symbolTable.get(this->tokenList[i].lex).type == "i64")
            {
              i += 1;
            }
            else
            {
              std::cout << "Erro semântico: O tipo da variável " << this->tokenList[i].lex << " não e compativel com operações de incremento unárias (++ ou --). Linha "
                        << this->tokenList[i].line << std::endl;
              exit(1);
            }
          }
          else
          {
            i = proccessAtribuitionExpression(i + 2);
          }
        }
        else
        {
          std::cout << "Não era pra ter chegado aqui 2";
        }
      }
      else
      {
        std::cout << "Erro semântico: A variável " << this->tokenList[i].lex << " não foi declarada. Linha "
                  << this->tokenList[i].line << std::endl;
        exit(1);
      }
    }
    // É um foreach
    else if (this->tokenList[i].lex == "foreach")
    {
      if (this->symbolTable.contains(this->tokenList[i + 3].lex))
      {
        if (this->symbolTable.get(this->tokenList[i + 3].lex).size > 0)
        {
          if (!this->symbolTable.contains(this->tokenList[i + 1].lex))
          {
            this->symbolTable.add(this->tokenList[i + 1].lex, this->symbolTable.get(this->tokenList[i + 3].lex).type, 0);
            i += 3;
          }
          else
          {
            std::cout << "Erro semântico: A variável " << this->tokenList[i + 1].lex << " já foi declarada anteriormente. Linha "
                      << this->tokenList[i + 1].line << std::endl;
            exit(1);
          }
        }
        else
        {
          std::cout << "Erro semântico: A variável " << this->tokenList[i + 3].lex << " não é um array. Linha "
                    << this->tokenList[i + 3].line << std::endl;
          exit(1);
        }
      }
      else
      {
        std::cout << "Erro semântico: A variável " << this->tokenList[i + 3].lex << " não foi declarada. Linha "
                  << this->tokenList[i + 3].line << std::endl;
        exit(1);
      }
    }
    // É um for
    else if (this->tokenList[i].lex == "for")
    {
      // Processa a primeira parte do for, atribuição
      if (this->tokenList[i + 1].token == "colon")
      {
        i += 1;
      }
      else
      {
        if (this->symbolTable.contains(this->tokenList[i + 1].lex))
        {
          i = proccessAtribuitionExpression(i + 2);
        }
        else
        {
          std::cout << "Erro semântico: A variável " << this->tokenList[i + 1].lex << " não foi declarada. Linha "
                    << this->tokenList[i + 1].line << std::endl;
          exit(1);
        }
      }
      // Processa a segunda parte do for, expressão
      if (this->tokenList[i + 1].token == "colon")
      {
        i += 1;
      }
      else
      {
        i = proccessAtribuitionExpression(i + 2);
      }
      // Processa a terceira parte do for, incremento
      if (!this->symbolTable.contains(this->tokenList[i].lex))
      {
        std::cout << "Erro semântico: A variável " << this->tokenList[i + 1].lex << " não foi declarada. Linha "
                  << this->tokenList[i + 1].line << std::endl;
        exit(1);
      }
      else
      {
        i = proccessAtribuitionExpression(i + 2);
      }
    }
    // É um if
    else if (this->tokenList[i].lex == "if")
    {
      i = proccessAtribuitionExpression(i + 1);
    }
  }
}