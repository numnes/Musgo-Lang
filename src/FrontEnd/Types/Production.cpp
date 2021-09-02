#ifndef PRODUCTION
#define PRODUCTION

#include <string>
typedef struct
{
    std::string token;
    std::string lex;
    int line;
} Production;

#endif // !PRODUCTION