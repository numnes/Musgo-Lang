#include <string>

struct SymbolParams
{
  SymbolParams(std::string _type, std::string _value) : type(_type), value(_value) {}
  std::string type;
  std::string value;
};

typedef struct SymbolParams SymbolParams;
typedef std::pair<std::string, SymbolParams> Symbol;
