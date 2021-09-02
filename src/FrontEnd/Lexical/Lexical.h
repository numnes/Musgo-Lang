#include <string>
#include <vector>
#include <deque>
#include "../Types/Production.cpp"

class Lexical
{
public:
  Lexical(char *musgonizer, long long int length);
  std::deque<Production> run();
  void set_input(std::string input);
  std::deque<Production> run(const char musgonizer[], int length);

private:
  char *musgonizer;
  long long int length;
  std::string get_token(const std::string &lexema);
  void add_token(const std::string &token, const std::string &lexema, std::vector<std::string> &list, int countLines, std::deque<Production> &productions);
};