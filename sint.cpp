#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>    // std::find
#include <fstream>
#include <iostream>
#include <list>

// Função que separa uma string dividida em espaços em tokens
std::vector<std::string> splitStr(std::string str){
    std::vector<std::string> retList;
    int s = str.length();
    int fSpace = str.find(" ");
    int iSpace = fSpace;
    retList.push_back(str.substr(0, fSpace));
    while((fSpace = str.find(" ", iSpace+1)) != std::string::npos){
        if(fSpace == (iSpace+1)){
            iSpace = fSpace;
            continue;
        }
        retList.push_back(str.substr(iSpace+1, (fSpace - iSpace)-1));
        iSpace = fSpace;
    }
    return retList;
}

int main()
{
    std::string line;
    std::string line2;
    std::ifstream myfile("tabelaPreditiva.csv");
    std::getline(myfile, line);

    // Não terminais
    std::vector<std::string> Nterminais;

    std::vector<std::string> Terminais;
    bool exFirst = false;

    std::stringstream sline(line);
    while (std::getline(sline, line2, ',')){
        if(exFirst)
            Nterminais.push_back(line2);
        exFirst = true;
    }
    
    for(auto a: Nterminais){
        std::cout << a << std::endl;
    }
    
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string> > > Table;

    while (std::getline(myfile, line))
    {
        std::stringstream sline(line);
        exFirst = true;

        // Não terminal chave
        std::string tableKey;

        // Derivações do não terminal
        std::unordered_map<std::string, std::vector<std::string> > derivationList;

        // Partes da derivação
        std::vector< std::vector<std::string> > derivations;

        // Derivações brutas
        std::vector<std::string> derivationsUnp;

        while (std::getline(sline, line2, ',')){
            if(exFirst){
                tableKey = line2;
                exFirst = false;
            }
            else
                derivationsUnp.push_back(line2);
        }

        for(auto d : derivationsUnp)
            derivations.push_back(splitStr(d));
        
        for(int i = 0; i < Nterminais.size(); i++)
            derivationList.insert(std::make_pair(Nterminais[i], derivations[i]));
        
        Terminais.push_back(tableKey);
        Table.insert(std::make_pair(tableKey, derivationList));
    }

    std::vector<std::string> Pheap;
    std::vector<std::string> entry;

    Pheap.push_back(Nterminais[0]);

    while(!Pheap.empty()){
        if( std::find(Terminais.begin(), Terminais.end(), *(Pheap.begin())) != Terminais.end() ){
            if((*(Pheap.end()-1)) == *(entry.begin())){
                Pheap.erase((Pheap.end()-1));
                entry.erase(entry.begin());
            }
            else{
                std::cout << "Erro1";
                break;
            }
        }
        else{
            if( Table[ (*(Pheap.end()-1)) ].find((*(entry.begin()))) !=  Table[ (*(Pheap.end()-1)) ].end()){
                Pheap.erase((Pheap.end()-1));
                for(int i = Table[(*(Pheap.end()-1))][(*(entry.begin()))].size()-1; i >= 0; i--)
                    Pheap.push_back(Table[(*(Pheap.end()-1))][(*(entry.begin()))][i]);
            }
            else{
                std::cout << "Erro2";
                break;
            }
        }
    }   
    return 0;
}