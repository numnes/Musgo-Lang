#ifndef SYMBOL
#define SYMBOL

#include <string>

struct SymbolParams
{
  SymbolParams(std::string _type, std::string _value, int _size) : type(_type), value(_value), size(_size) {}
  std::string type;
  std::string value;
  int size;
};

typedef struct SymbolParams SymbolParams;
typedef std::pair<std::string, SymbolParams> Symbol;

#endif // !SYMBOL