#include <deque>
#include "../Types/Production.cpp"

class Syntatic
{
public:
  Syntatic(std::deque<Production> _productions);
  void run();

private:
  std::deque<Production> productions;
};
