#include "Compiler.h"
#include <fstream>
#include <iostream>
#include "../Analyzer/Analyzer.h"

Compiler::Compiler(char *_filename, char *_flag)
{
  this->filename = _filename;
  std::ifstream arq(this->filename);
  if (!arq.is_open())
  {
    std::cerr << "Error opening file" << std::endl;
    return;
  }
  //Gets the file's size in bytes
  arq.seekg(0, arq.end);
  this->length = arq.tellg();
  this->flag = _flag;
  arq.seekg(0, arq.beg);
  this->musgonizer = new char[length];
  arq.read(this->musgonizer, length);
  arq.close();
}

void Compiler::run()
{
  Analyzer analyzer(this->musgonizer, this->length, this->flag);
  analyzer.run();
}