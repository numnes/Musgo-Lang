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

    Compiler compiler(argv[1]);
    compiler.run();
}