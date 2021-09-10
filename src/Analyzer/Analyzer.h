class Analyzer
{
public:
  Analyzer(char *musgonizer, long long int length, std::string _flag);
  void run();
  std::string flag;

private:
  char *musgonizer;
  long long int length;
};