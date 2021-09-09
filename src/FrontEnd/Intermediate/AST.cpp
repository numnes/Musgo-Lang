#include "AST.h"

void addChild(Node *parent, Node *child)
{
    parent->children.push_back(child);
}

void processOp(std::deque<Production> tokenList)
{

    if (tokenList[i].token == "ar_op")
    {
    }
    if (tokenList[i].token == "log_op")
    {
    }
    if (tokenList[i].token == "rel_op")
    {
    }
}

Node *processValue(Production prod)
{
    if (prod.token == "id")
    {
        return new Node("variable", prod.lex)
    }

    return new Node(prod.token, prod.lex);
}

AST::AST(std::deque<Production> _tokenList)
{
    this->tokenList = _tokenList;

    this->root = new Node("statementList");

    for (int i = 0; i < tokenList.size(); i++)
    {

        //Assignment
        if (tokenList[i].token == "id" and tokenList[i + 1].token == "as_op")
        {
            Node *nodeAssign = new Node("assign");

            addChild(nodeAssign, new Node("variable", tokenList[i].lex));

            

            addChild(this->root, nodeAssign);
        }

        //Array
        if (tokenList[i].token == "id" and tokenList[i + 1].token == "bracket_left")
        {
        }

        //Declaration
        if (tokenList[i].token == "id" and tokenList[i + 1].token == "semicolon")
        {

            Node *nodeDeclaration = new Node("declaration");

            addChild(nodeDeclaration, new Node("variable", tokenList[i].lex));
            addChild(this->root, nodeDeclaration);
        }

        if (tokenList[i].token == "if")
        {
        }

        if (tokenList[i].token == "for")
        {
        }

        if (tokenList[i].token == "foreach")
        {
        }

        if (tokenList[i].token == "const")
        {
        }

        if (tokenList[i].token == "string")
        {
        }
        if (tokenList[i].token == "block_left")
        {
        }
        if (tokenList[i].token == "else")
        {
        }

        if (tokenList[i].token == "")
        {
        }

        if (tokenList[i].token == "")
        {
        }
    }
}