class Compiler
{
public:
  Compiler(char *_filename);
  void run();

private:
  char *filename;
  char *musgonizer;
  long long int length;
};