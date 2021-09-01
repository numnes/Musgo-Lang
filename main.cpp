#include <iostream>
#include <fstream>
#include "lex.cpp"
#include "sint.cpp"

#include "src/Lexical.h"

int main(int argc, char *argv[])
{

    if (argc <= 1)
    {
        std::cerr << "Error, no input file\n";
        return 0;
    }

    std::ifstream arq(argv[1]);

    if (!arq.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return 0;
    }

    //Gets the file's size in bytes
    arq.seekg(0, arq.end);
    long long int length = arq.tellg();
    arq.seekg(0, arq.beg);

    char musgonizer[length]; //Holds the data

    arq.read(musgonizer, length); //Read the file into musgonizer buffer

    // auto token_list = lex_processing(musgonizer, length);
    auto token_list = Lexical::lex_processing(musgonizer, length);

    sint_processing(token_list);

    //Print mode
    // if (argc > 2 and argv[2][1] == 'p')
    //     for(auto x : token_list)
    //         std::cout << x << "\n";
}