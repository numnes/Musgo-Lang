#include "AST.h"

void addChild(Node *parent, Node *child)
{
    parent->children.push_back(child);
}

AST::AST(std::string yes)
{
    this->root = new Node(yes);
    this->root->parent = nullptr;
}