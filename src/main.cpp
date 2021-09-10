#include <iostream>
#include <fstream>
#include "Compiler/Compiler.h"

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        std::cerr << "Error, no input file\n";
        return 0;
    }
    if (argc > 2)
    {
        Compiler compiler(argv[1], argv[2]);
        std::cout << argv[2] << std::endl;
        compiler.run();
    }
    else
    {
        char flag[5] = "null";
        Compiler compiler(argv[1], flag);
        compiler.run();
    }
}