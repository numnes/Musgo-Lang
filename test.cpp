#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <list>

std::vector<std::string> splitStr(std::string str){
    std::vector<std::string> retList;
    int s = str.length();
    int fSpace = str.find(" ");
    int iSpace = fSpace;
    std::string firstS = str.substr(0, fSpace);
    if(firstS != "" && firstS != " ")
        retList.push_back(firstS);
    while((fSpace = str.find(" ", iSpace+1)) != std::string::npos){
        if(fSpace == (iSpace+1)){
            iSpace = fSpace;
            continue;
        }
        std::string res = str.substr(iSpace+1, (fSpace - iSpace)-1);
        if(res != "" && res != " ")
            retList.push_back(res);
        iSpace = fSpace;
    }
    std::cout <<  iSpace << " " << str[iSpace] << "\n";
    if(iSpace < str.length()-1 && str[iSpace+1] != ' '){
        firstS = str.substr(iSpace+1, str.length()-1);
        retList.push_back(firstS);
    }

    return retList;
}




int main()
{
    std::string s = "as_op    expression   semicolon";

    for( auto a : splitStr(s))
        std::cout << "[" << a << "] ";
    puts("");


}