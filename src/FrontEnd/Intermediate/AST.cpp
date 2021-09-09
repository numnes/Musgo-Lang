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

void AST::dump() {
    std::string s = "";
    std::set<int> pool;
    srand (time(NULL));

    graph_iter(this->root, s, pool);

    std::ofstream file;
    file.open("dump.txt");

    if(!file.is_open())
    {
        std::cout << "Couldn't open/create dump.txt\n";
    }
    
    file << s;
    file.close();

}

std::string graph_iter(Node* root, std::string &s, std::set<int> pool) {

    if(!root->children.size() and root->info == "")
        return "";

    if(root->children.size() == 1) {
        std::string name = graph_iter(root->children[0],s,pool);
        return name;
    }

    int rng = rand();
    while(pool.count(rng)) {
        rng = rand();
    }
    pool.insert(rng);

    std::string name = "\""+ root->name + std::to_string(rng) +"\" ";
    s += name + " " + " [label=\"";

    s += root->info != "" ?  root->info +"\"]\n" :  root->name +"\"]\n";

    for (auto it = root->children.rbegin(); it != root->children.rend(); it++) {
        std::string childName = graph_iter(*it,s,pool);
        s += childName != "" ? name + "-> " + childName + "\n" : "";
    }

    return name;
}