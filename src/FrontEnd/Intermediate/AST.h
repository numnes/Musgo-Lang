#include <string>
#include <vector>
#include <deque>
#include "../Types/Production.cpp"

struct Node {
    std::string name;
    std::vector<Node*> children;
    std::string info;
    Node(std::string _name) : name{_name}, info{""} {};
    Node(std::string _name,std::string _info) : name{_name}, info{_info} {};
};

class AST {
public:
    AST(std::deque<Production> _tokenList);
    Node* root;
    std::deque<Production> tokenList;
};