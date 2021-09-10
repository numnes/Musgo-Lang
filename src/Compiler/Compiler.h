#include <string>

class Compiler
{
public:
  Compiler(char *_filename, char *_flag);
  void run();

private:
  char *filename;
  std::string flag;
  char *musgonizer;
  long long int length;
};