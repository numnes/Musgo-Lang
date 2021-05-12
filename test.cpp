#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <list>

std::list<std::string> splitStr(std::string str){
    std::list<std::string> retList;
    int s = str.length();
    int fSpace = str.find(" ");
    int iSpace = fSpace;
    retList.push_back(str.substr(0, fSpace));
    while((fSpace = str.find(" ", iSpace+1)) != std::string::npos){
        if(fSpace == (iSpace+1)){
            iSpace = fSpace;
            continue;
        }
        retList.push_back(str.substr(iSpace+1, (fSpace - iSpace)-1));
        iSpace = fSpace;
    }
    return retList;
}




int main()
{
    std::vector<int> a;

    for(auto i:{1,2,3,4,5,6})
        a.push_back(i);

    std::cout << *(a.end()-1) << "\n";


}