#include "AST.h"
#include <time.h>
#include <iostream>
#include <fstream>

void addChild(Node *parent, Node *child)
{
    parent->children.push_back(child);
}

AST::AST(std::string yes)
{
    this->root = new Node(yes);
    this->root->parent = nullptr;
}

void AST::dump()
{
    std::string s = "";
    std::set<int> pool;
    srand(time(NULL));

    graph_iter(this->root, s, pool);

    s = "digraph G {\n" + s + "}";

    std::ofstream file;
    file.open("dump.txt");

    if (!file.is_open())
    {
        std::cout << "Couldn't open/create dump.txt\n";
    }

    file << s;
    file.close();
    std::cout << "\033[1;32m Codigo intermediário gerado no arquivo dump.txt\033[0m\n";
}

std::string graph_iter(Node *root, std::string &s, std::set<int> pool)
{

    if (!root->children.size() and root->info == "")
        return "";

    if((root->children.size() == 1) and (root->children[0]->info == "")) {
        std::string name = graph_iter(root->children[0],s,pool);
        return name;
    }

    int rng = rand();
    while (pool.count(rng))
    {
        rng = rand();
    }
    pool.insert(rng);

    std::string name = "\"" + root->name + std::to_string(rng) + "\" ";
    s += name + " " + " [label=";

    if(root->name == "string")
        s += root->info != "" ? root->info + "]\n" : root->name + "]\n";
    else 
        s += root->info != "" ? "\"" + root->info + "\"]\n" : "\"" + root->name + "\"]\n";

    for (auto it = root->children.rbegin(); it != root->children.rend(); it++)
    {
        std::string childName = graph_iter(*it, s, pool);
        s += childName != "" ? name + "-> " + childName + "\n" : "";
    }

    return name;
}