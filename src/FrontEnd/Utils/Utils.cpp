#include <vector>
#include <string>

class Utils
{
public:
  // Função que separa uma string dividida em espaços em tokens
  static std::vector<std::string> splitStr(std::string str)
  {
    std::vector<std::string> retList;
    int s = str.length();
    int fSpace = str.find(" ");
    int iSpace = fSpace;
    int fSep = fSpace;
    std::string firstS = str.substr(0, fSpace);
    if (firstS != "" && firstS != " ")
      retList.push_back(firstS);
    while ((fSpace = str.find(" ", iSpace + 1)) != std::string::npos)
    {
      if (fSpace == (iSpace + 1))
      {
        iSpace = fSpace;
        continue;
      }
      std::string res = str.substr(iSpace + 1, (fSpace - iSpace) - 1);
      if (res != "" && res != " ")
        retList.push_back(res);
      iSpace = fSpace;
    }
    return retList;
  }
};