#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>
#include <map>
#include <deque>
#include "../Types/Production.cpp"
#include "Lexical.h"

Lexical::Lexical(char *_musgonizer, long long int _length)
{
    this->musgonizer = _musgonizer;
    this->length = _length;
}

void Lexical::add_token(const std::string &token, const std::string &lexema, std::vector<std::string> &list, int countLines, std::deque<Production> &productions)
{
    std::string aux = "[" + token + "," + lexema + "," + std::to_string(countLines) + "]";
    Production p = {token, lexema, countLines};
    productions.push_back(p);
    list.push_back(aux);
}

std::string Lexical::get_token(const std::string &lexema)
{
    std::unordered_set<std::string> reserved = {"const", "for", "foreach", "if", "else"};
    std::unordered_set<std::string> logic_ops = {"xor", "not", "or", "and"};
    std::unordered_set<std::string> types = {"i32", "i64", "f32", "f64", "bool", "char"};

    std::string token;

    if (reserved.count(lexema))
        token = lexema;
    else if (logic_ops.count(lexema))
        token = "log_op";
    else if (types.count(lexema))
        token = "type";
    else
        token = "id";

    return token;
}

std::deque<Production> Lexical::run()
{
    int state = 0;
    int counter = 0;
    int countLines = 1;
    std::string token;
    std::string lexema;

    std::deque<Production> productions;

    std::vector<std::string> token_list;

    while (counter < this->length)
    {
        char c = this->musgonizer[counter];
        counter++;
        switch (state)
        {
        case 0:
            token = "";
            lexema = "";
            // não finais
            if (c >= '0' && c <= '9')
            {
                state = 14;
                lexema += c;
            }
            else if (c == '_')
            {
                state = 20;
                lexema += c;
            }
            else if (c == '/')
            {
                state = 23;
                lexema += c;
            }
            else if (c == '*')
            {
                state = 11;
                lexema += c;
            }
            else if (c == '+')
            {
                state = 6;
                lexema += c;
            }
            else if (c == '-')
            {
                state = 1;
                lexema += c;
            }
            else if (c == '"')
            {
                state = 30;
                lexema += c;
            }
            else if (c == '>')
            {
                state = 34;
                lexema += c;
            }
            else if (c == '=')
            {
                state = 37;
                lexema += c;
            }
            else if (c == '<')
            {
                state = 40;
                lexema += c;
            }
            else if (c == '!')
            {
                state = 44;
                lexema += c;
            }
            else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
            {
                state = 21;
                lexema += c;
            }
            else if (c == '\'')
            {
                state = 53;
                lexema += c;
            }
            // finais
            else if (c == ']') //50
            {
                token = "bracket_right";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else if (c == '[') //49
            {
                token = "bracket_left";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else if (c == '(') //32
            {
                token = "par_left";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else if (c == ')') //33
            {
                token = "par_right";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else if (c == '{') //28
            {
                token = "block_left";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else if (c == '}') //29
            {
                token = "block_right";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else if (c == ':') //19
            {
                token = "colon";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else if (c == ';') //48
            {
                token = "semicolon";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else if (c == ',') //51
            {
                token = "comma";
                lexema = c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else if (c == '^') //10
            {
                token = "ar_op";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else if (c == '%') //10
            {
                token = "ar_op";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else if (c == '\n' || c == '\t' || c == ' ' || (int)c == 13) //47
            {
                if (c == '\n')
                    countLines++;
                continue;
            }
            else
            {
                std::cerr << "Error: Invalid character " << c << " at line " << countLines << std::endl;
            }
            break;
        case 1:
            if (c == '>') //2
            {
                token = "out";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else if (c == '-' || c == '=') //3+4
            {
                token = "as_op";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else //5
            {
                token = "ar_op";
                counter--;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            break;
        case 6:
            if (c == '+' || c == '=') //7+8
            {
                token = "as_op";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else //9
            {
                token = "ar_op";
                state = 0;
                counter--;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            break;
        case 11:
            if (c == '=') //12
            {
                token = "as_op";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else //13
            {
                token = "ar_op";
                state = 0;
                counter--;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            break;
        case 14:
            if (c >= '0' && c <= '9')
                lexema += c;
            else if (c == '.')
            {
                lexema += c;
                state = 15;
            }
            else //18
            {
                token = "num";
                counter--;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            break;
        case 15:
            if (c >= '0' && c <= '9')
            {
                lexema += c;
                state = 16;
            }
            else
            {
                std::cerr << "Error: Expected an numeric value after \".\", got \"" << c << "\" at line " << countLines << "\n";
                state = 16;
            }
            break;
        case 16:
            if (c >= '0' && c <= '9')
                lexema += c;
            else //17
            {
                token = "float";
                counter--;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            break;
        case 20:
            if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
            {
                state = 21;
                lexema += c;
            }
            else
            {
                std::cerr << "Error: Expected an alphanumeric character after \"_\", got \"" << c << "\" at line " << countLines << "\n";
                state = 21;
            }
            break;
        case 21:
            if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_'))
            {
                lexema += c;
            }
            else //22
            {
                token = this->get_token(lexema);
                counter--;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            break;
        case 23:
            if (c == '/')
            {
                state = 24;
                lexema += c;
            }
            else if (c == '=') //26
            {
                token = "as_op";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else //27
            {
                token = "ar_op";
                counter--;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            break;
        case 24:
            if (c == '\n') //25
            {
                state = 0;
                countLines++;
            }
            else
            {
                lexema += c;
            }
            break;
        case 30:
            if (c == '"') //31
            {
                token = "string";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else
            {
                lexema += c;
            }
            break;
        case 34:
            if (c == '=') //35
            {
                token = "rel_op";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else //36
            {
                token = "rel_op";
                counter--;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            break;
        case 37:
            if (c == '=') //38
            {
                token = "rel_op";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else //39
            {
                token = "as_op";
                counter--;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            break;
        case 40:
            if (c == '=') //41
            {
                token = "rel_op";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else if (c == '-') //42
            {
                token = "in";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else //43
            {
                token = "rel_op";
                counter--;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }

            break;
        case 44:
            if (c == '=') //45
            {
                token = "rel_op";
                lexema += c;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else //46
            {
                token = "log_op";
                counter--;
                state = 0;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            break;
        case 53:
            if ((c > 20 && c <= 125))
            {
                state = 54;
                lexema += c;
            }
            else
            {
                std::cerr << "Error: Expected a char character after \', got \"" << c << "\" at line " << countLines << "\n";
                state = 54;
                lexema += 'a';
            }
            break;
        case 54:
            if (c == '\'')
            {
                token = "char";
                state = 0;
                lexema += c;
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            else
            {
                std::cerr << "Error: Expected a \' character after char, got \"" << c << "\" at line " << countLines << "\n";
                token = "char";
                state = 0;
                lexema += '\'';
                this->add_token(token, lexema, token_list, countLines, productions);
            }
            break;
        }
    }

    // for(auto a: productions)
    //     std::cout << a.token << "\n";

    return productions;
}