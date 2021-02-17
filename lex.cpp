#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>

void add_token(std::string &token, std::string &lexema, std::vector<std::string> &list, int countLines) 
{    
    std::string aux = "[" + token + "," + lexema + "," + std::to_string(countLines) + "]";
    list.push_back(aux);
    token = "";
    lexema = "";
}

std::string get_token(std::string lexema, std::unordered_set<std::string> reserved, std::unordered_set<std::string> logic_ops)
{
    return reserved.count(lexema) ? (lexema) : (logic_ops.count(lexema) ?  "log_op" : "id");
}

int main(int argc, char* argv[]) {

    if (argc <= 1)
    {
        std::cerr << "Error, no input file\n";
        return 0;
    }

    std::ifstream arq(argv[1]);

    if(!arq.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return 0;
    }

    //Gets the file's size in bytes
    arq.seekg (0, arq.end);
    long long int length = arq.tellg();
    arq.seekg(0, arq.beg);
    
    char musgonizer[length]; //Holds the data 	
    
    arq.read(musgonizer,length);  //Read the file into musgonizer buffer

    int state = 0;
    int counter = 0;
    int countLines = 1;
    std::string token;
    std::string lexema;

    std::vector<std::string> token_list;
    std::unordered_set<std::string> reserved = {"i32", "i64", "f32", "f64", "bool", "char", 
                                                "const", "if", "else", "for", "foreach"};
    std::unordered_set<std::string> logic_ops = {"xor", "not", "or", "and"};


    while(counter < length){
        char c = musgonizer[counter];
        counter++;

        switch(state){
            case 0:
                // não finais
                if(c >= '0' &&  c <= '9'){
                    state = 14;
                    lexema += c;
                }
                else if(c == '_'){
                    state = 20;
                    lexema += c;
                }
                else if(c == '/'){
                    state = 23;
                    lexema += c;
                }
                else if(c == '*' ){
                    state = 11;
                    lexema += c;
                }
                else if(c == '+'){
                    state = 6;
                    lexema += c;
                }
                else if(c == '-'){
                    state = 1;
                    lexema += c;
                }
                else if(c == '"'){
                    state = 30;
                    lexema += c;
                }
                else if(c == '>'){
                    state = 34;
                    lexema += c;
                }
                else if(c == '='){
                    state = 37;
                    lexema += c;
                }
                else if(c == '<'){
                    state = 40;
                    lexema += c;
                }
                else if(c == '!'){
                    state = 44;
                    lexema += c;
                }
                else if((c >= 'A' &&  c <= 'Z') ||  (c >= 'a' && c <= 'z')){
                    state = 21;
                    lexema += c;
                }
                // finais
                else if(c == ']') //50
                {
                    token = "bracket_right";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines); 
                }
                else if(c == '[') //49
                {
                    token = "bracket_left";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines); 
                }
                else if(c == '(') //32
                {
                    token = "par_left";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines); 
                }
                else if(c == ')') //33
                {
                    token = "par_right";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines); 
                }
                else if(c == '{') //28
                {
                    token = "block_left";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines); 
                }
                else if(c == '}') //29
                {
                    token = "block_right";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines); 
                }
                else if(c == ':') //19
                {
                    token = "colon";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines); 
                }
                else if(c == ';') //48
                {
                    token = "semicolon";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines); 
                }
                else if(c == ',') //51
                {
                    token = "comma";
                    lexema = c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines);
                }
                else if(c == '^') //10
                {
                    token = "ar_op";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines); 
                }
                else if(c == '\n' || c == '\t' || c == ' ' || (int) c == 13) //47
                {
                    if(c == '\n')
                        countLines ++; 
                    continue;
                }
                else {
                    std::cerr << "Error: Invalid character " << c << " at line " << countLines << std::endl;
                }
            break;
            case 1:
                if(c == '>') //2
                {
                    token = "out";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines); 
                }
                else if(c == '-' || c == '=') //3+4
                {
                    token = "as_op";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines); 
                }
                else //5
                {
                    token = "ar_op";
                    counter--;
                    state = 0;
                    add_token(token, lexema, token_list, countLines); 
                } 
            break;
            case 6:
                if(c == '+' || c == '=') //7+8
                {
                    token = "as_op";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines); 
                }
                else //9
                {
                    token = "ar_op";
                    state = 0;
                    counter--;
                    add_token(token, lexema, token_list, countLines); 
                }
            break;
            case 11:
                if(c == '=') //12
                {
                    token = "as_op";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines); 
                }
                else //13
                {
                    token = "ar_op";
                    state = 0;
                    counter--;
                    add_token(token, lexema, token_list, countLines); 
                }
            break;
            case 14:
                if(c >= '0' && c <= '9' )
                    lexema += c;
                else if(c == '.')
                {
                    lexema += c;
                    state = 15;
                }
                else //18
                {
                    token = "num";
                    counter--;
                    state = 0;
                    add_token(token, lexema, token_list, countLines);
                }
            break;
            case 15:
                if(c >='0' && c <= '9' )
                {
                    lexema += c;
                    state = 16;
                }
                else{
                    std:: cerr << "Error: Expected an numeric value after \".\", got \""<< c << "\" at line " << countLines << "\n";
                    state = 0;
                }
            break;
            case 16:
                if(c >='0' && c <= '9' )
                    lexema += c;
                else //17
                {
                    token = "float";
                    counter--;
                    state = 0;
                    add_token(token, lexema ,token_list, countLines);
                }
            break;
            case 20:
                if((c >= '0' &&  c <= '9') || (c >= 'A' &&  c <= 'Z') ||  (c >= 'a' && c <= 'z'))
                {
                    state = 21;
                    lexema += c;
                }
                else{
                    std:: cerr << "Error: Expected an alphanumeric character after \"_\", got \""<< c << "\" at line " << countLines << "\n";
                    state = 0;
                }
            break;
            case 21:
                if((c >= '0' &&  c <= '9') || (c >= 'A' &&  c <= 'Z') ||  (c >= 'a' && c <= 'z') || (c == '_'))
                {
                    lexema += c;
                }
                else //22
                {
                    token = get_token(lexema, reserved, logic_ops);
                    counter--;
                    state = 0;
                    add_token(token, lexema, token_list, countLines);
                }
            break;
            case 23:
                if(c == '/')
                {
                    state = 24;
                    lexema += c;
                }
                else if(c == '=') //26
                {
                    token = "as_op";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines);
                }
                else //27
                {
                    token = "ar_op";
                    counter--;
                    state = 0;
                    add_token(token, lexema, token_list, countLines);
                }
            break;
            case 24:
                if(c == '\n') //25
                {
                    token = "comment";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines);
                    countLines++;
                }
                else
                {
                    lexema += c;
                }
            break;
            case 30:
                if( c == '"') //31
                {
                    token = "string";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines);
                }
                else 
                {
                    lexema += c;
                }
            break;
            case 34:
                 if(c == '=') //35
                {
                    token = "rel_op";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines);
                }
                else //36
                {
                    token = "rel_op";
                    counter--;
                    state = 0;
                    add_token(token, lexema, token_list, countLines);
                }
            break;
            case 37:
             if(c == '=') //38
                {
                    token = "rel_op";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list,  countLines);
                }
                else //39
                {
                    token = "as_op";
                    counter--;
                    state = 0;
                    add_token(token, lexema, token_list, countLines);
                }
            break;
            case 40:
                if(c == '=') //41
                {
                    token = "rel_op";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines); 
                }
                else if(c == '-') //42
                {
                    token = "in";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines);
                }
                else //43
                {
                    token = "rel_op";
                    counter--;
                    state = 0;
                    add_token(token, lexema, token_list, countLines);
                }
                
            break;
            case 44:
                if(c == '=') //45
                {
                    token = "rel_op";
                    lexema += c;
                    state = 0;
                    add_token(token, lexema, token_list, countLines);
                }
                else //46
                {
                    token = "log_op";
                    counter--;
                    state = 0;
                    add_token(token, lexema, token_list, countLines);
                }
            break;
        }
    }
    //Print mode
    if (argc > 2 and argv[2][1] == 'p')
        for(auto x : token_list)
            std::cout << x << "\n";
    
}