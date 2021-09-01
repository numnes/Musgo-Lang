#ifndef _LEXICAL_
#define _LEXICAL_

class Lexical
{
public:
    Lexical(const char *str, int len);
    static std::deque<Production> lex_processing(const char musgonizer[], int length);
};
#endif // _LEXICAL