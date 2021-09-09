#include <string>
#include <vector>
#include <deque>
#include "../Types/Production.cpp"

struct Node {
    std::string name;
    std::vector<Node*> children;
    Node* parent;
    std::string info;
    Node(std::string _name) : name{_name}, info{""} {};
    Node(std::string _name,std::string _info) : name{_name}, info{_info} {};
};

class AST {
public:
    AST(std::string yes);
    Node* root;
};