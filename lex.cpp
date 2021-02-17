#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

void add_token(std::string &token, std::string &lexema, std::vector<std::string> &list) {
    list.push_back("[" + token + "," + lexema + "]");
    token = "";
    lexema = "";
    return;
}

std::string get_token(std::string lexema, std::unordered_set<std::string> reserved)
{
    return reserved.count(lexema) ? lexema : "id";
}

int main(int argc, char* argv[]) {

    std::vector<std::string> token_list;
    std::unordered_set<std::string> reserved = {"i32","i64","f32","f64","bool","char","const","if",
                   "else","for","foreach","xor","not","or","and"};

    std::ifstream arq("main.mg");

    if(!arq.is_open())
    {
        std::cout << "ERRO" << std::endl;
        return 0;
    }

    arq.seekg (0, arq.end);
    long long int length = arq.tellg();
    arq.seekg(0, arq.beg);
    
    char musgonizer[length]; //Armazena arquivo a ser aberto  	
    
    //Lê o arquivo todo como um bloco para o buffer musgonizer
    arq.read(musgonizer,length);

    int state = 0;
    int counter = 0;
    std::string token;
    std::string lexema;

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
                else if((c >= 'A' &&  c <= 'Z') ||  (c >= 'a' && c <= 'z')){
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
                // finais
                if(c == ']')
                {
                    token = "bracket_left";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list); 
                }
                if(c == '[')
                {
                    token = "bracket_right";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list); 
                }
                if(c == '(')
                {
                    token = "par_left";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list); 
                }
                if(c == ')')
                {
                    token = "par_right";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list); 
                }
                if(c == '{')
                {
                    token = "block_left";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list); 
                }
                if(c == '}')
                {
                    token = "block_right";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list); 
                }
                if(c == ':')
                {
                    token = "colon";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list); 
                }
                if(c == ';')
                {
                    token = "semicolon";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list); 
                }
                if(c == ',')
                {
                    token = "comma";
                    lexema = c;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
                if(c == '^')
                {
                    token = "ar_op";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list); 
                }
                if(c == '\n' || c == '\t' || c == ' ')
                {
                    continue;
                }
            break;
            case 1:
                if(c == '>')
                {
                    token = "out";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list); 
                }
                else if(c == '-' || c == '=')
                {
                    token = "as_op";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list); 
                }
                else
                {
                    token = "ar_op";
                    counter--;
                    state = 0;
                    add_token(token,lexema,token_list); 
                } 
            break;
            case 6:
                if(c == '+' || c == '=')
                {
                    token = "as_op";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list); 
                }
                else
                {
                    token = "ar_op";
                    state = 0;
                    counter--;
                    add_token(token,lexema,token_list); 
                }
            break;
            case 11:
                if(c == '=')
                {
                    token = "as_op";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list); 
                }
                else
                {
                    token = "ar_op";
                    state = 0;
                    counter--;
                    add_token(token,lexema,token_list); 
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
                else
                {
                    token = "num";
                    counter--;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
            break;
            case 15:
                if(c >='0' && c <= '9' )
                {
                    lexema += c;
                    state = 16;
                }
                else{
                    std:: cout << "erro\n";
                    state = 0;
                }
            break;
            case 16:
                if(c >='0' && c <= '9' )
                    lexema += c;
                else
                {
                    token = "float";
                    counter--;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
            break;
            case 20:
                if((c >= '0' &&  c <= '9') || (c >= 'A' &&  c <= 'Z') ||  (c >= 'a' && c <= 'z'))
                {
                    state = 21;
                    lexema += c;
                }
            break;
            case 21:
                if((c >= '0' &&  c <= '9') || (c >= 'A' &&  c <= 'Z') ||  (c >= 'a' && c <= 'z') || (c == '_'))
                {
                    lexema += c;
                }
                else
                {
                    token = get_token(lexema,reserved);
                    counter--;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
            break;
            case 23:
                if(c == '/')
                {
                    state = 24;
                    lexema += c;
                }
                else if(c == '=')
                {
                    token = "as_op";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
                else
                {
                    token = "ar_op";
                    counter--;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
            break;
            case 24:
                if(c == '\n')
                {
                    token = "comment";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
                else
                {
                    lexema += c;
                }
            break;
            case 30:
                if( c == '"')
                {
                    token = "string";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
                else 
                {
                    lexema += c;
                }
            break;
            case 34:
                 if(c == '=')
                {
                    token = "rel_op";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
                else
                {
                    token = "rel_op";
                    counter--;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
            break;
            case 37:
             if(c == '=')
                {
                    token = "rel_op";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
                else
                {
                    token = "as_op";
                    counter--;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
            break;
            case 40:
                if(c == '=')
                {
                    token = "rel_op";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list); 
                }
                else if(c == '-')
                {
                    token = "in";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
                else
                {
                    token = "rel_op";
                    counter--;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
                
            break;
            case 44:
                if(c == '=')
                {
                    token = "rel_op";
                    lexema += c;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
                else
                {
                    token = "log_op";
                    counter--;
                    state = 0;
                    add_token(token,lexema,token_list);
                }
            break;
        }
    }
    for(auto x : token_list)
        std::cout << x << "\n";
    
}