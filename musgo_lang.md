# Musgo_lang

Musgo_lang é uma linguagem criada para disciplina de compiladores, sendo fortemente tipada e estática, imperativa. Tem sua sintaxe inspirada em C/C++, Rust.

### Tipos

Os tipos de dados suportados pela linguagem são apresentados na tabela abaixo. Todas as coerções entre tipos devem ser feito explicitamente com o uso de _cast_: `(type)`.

| Tipo   | Descrição                                            |
| ------ | ---------------------------------------------------- |
| `i32 ` | Inteiro de 32 bits                                   |
| `i64 ` | Inteiro de 64 bits                                   |
| `f32 ` | Float com 32 bits                                    |
| `f64 ` | Float com 64 bits                                    |
| `char` | Representa um caractere, ocupa 1 byte                |
| `bool` | Tipo lógico, pode assumir true ou false, ocupa 1 bit |

### Operadores

São 23 operadores ao total, 6 operadores relacionais, 4 lógicos, 7 de atribuição e 6 aritméticos. A precedência entre os operadores relacionais, lógicos e aritméticos é definida com o uso de parênteses `()`.

| Operadores Relacionais | Descrição          |
| ---------------------- | ------------------ |
| `==`                   | Igual              |
| `!=`                   | Diferente          |
| `>`                    | Maior que          |
| `< `                   | Menor que          |
| `>=`                   | Maior ou igual que |
| `<= `                  | menor ou igual que |

| Operadores Logicos | Descrição  |
| ------------------ | ---------- |
| `and`              | And lógico |
| `or`               | Or lógico  |
| `not`              | Not lógico |
| `xor`              | Xor lógico |

| Operadores Atribuição | Descrição                                           |
| --------------------- | --------------------------------------------------- |
| `=`                   | Atribuição                                          |
| `+=`                  | Atribuição com soma do valor dos operandos          |
| `-=`                  | Atribuição com subtração do valor dos operandos     |
| `*=`                  | Atribuição com multiplicação do valor dos operandos |
| `/=`                  | Atribuição com divisão, usando a direita o divisor  |
| `++`                  | Atribuição com incremento de uma unidade            |
| `--`                  | Atribuição com decremento de uma unidade            |

| Operadores Aritméticos | Descrição         |
| ---------------------- | ----------------- |
| `+`                    | Adição            |
| `-`                    | Subtração         |
| `*`                    | Multiplicação     |
| `/`                    | Divisão           |
| `%`                    | Módulo da divisão |
| `^`                    | Potenciação       |

### Identificadores
Os identificadores são formados por conjuntos de caracteres iniciados por letras de A a Z, maiusculas ou minusculas ou pelo simbolo `_`, seguidos por qualquer caracter alfanumérico. Porém não é possível criar identificadores somente com `_`.

### Comandos de entrada e saída

 `<-`  Comando de leitura 
 `->`  Comando de escrita 

Exemplo:
```
i32 a;
<- a; // Leitura de um valor para a variável 'a'
-> a; // Print do valor da variável 'a'
```

### Palavras Reservadas
As palavras abaixo são usadas pela linguagem e não podem ser definidas como identificadores.
```
and | or | not | xor | for | foreach | true | false | if | else | i32 | i64 | f32 | f64 | bool | char | const
```

### Estruturas de decisão repetição

```    
// Exemplo de estrutura de decisão

if a < b {
    // trecho de código
}
else if  a > b {
    // trecho de código
}
else{
    // outro trecho 
}
```

```
// Exemplo estrutura de repetição

// for
for i32 i = 0 ; i < a ; i++ {
  // trecho de código
}

// foreach
foreach x: arr{
  // trecho de código
}
```

### Declaração de variáveis e constantes
A declaração de variáveis é feita no formato `type id`, enquanto constantes utilizam o termo `const` no início. Exemplo:

```
    i32 i = 0;
    const f64 j = 4.5;
```

### Vetores
A declaração de vetores é parecida com a de variáveis, mas com a indicação do tamanho do vetor. Seu tamanho deve ser sempre conhecido em tempo de compilação. É possível também inicializar um vetor com o uso `{}`, separando os elementos com `,`. _Strings_ são apenas vetores de char. Exemplo: 
```
    char string[5];
    i32 vetor[4] = {10,20,40,50};
``` 


### Comentários 
Há suporte para comentários, basta que  use `//` no início de cada linha.

### Exemplo geral de um programa
```
i32 menor = 0;
i32 vetor[4] = {10,20,40,50};

foreach x: vetor {
	if x < menor {
		menor = x;
    }
}

i32 i;

for  i = 0; i < 4; i++{
	if vetor[i] < menor {
		menor = x;
    }
}

-> "O menor número eh: ";
-> menor;
-> "\n";

```

## Expressões Regulares
```
num           -> [0-9]+
alfanum       -> ([a-Z] | num)+
float         -> [num]+[.] [num]+
space         -> (tab | whitespace | newline)+
rel_op        -> [>] | [<] | [>=] | [<=] | [==] | [!=]
ar_op         -> [+] | [-] | [*] | [/] | [^]
as_op         -> [=] | [+=] | [-=] | [*=] | [/=] | [++] | [--]
log_op        -> [[!] | [and] | [or] | [not] | [xor] 
id            -> ([a-Z] | [_][alfanum]+) ([alfanum] | _ )*
string        -> ["][~"]*["]
comment       -> [//][~newline]*[newline]
booleans      -> ([true] | [false])
in            -> [<-]
out           -> [->]
block_left    -> [{]
block_right   -> [}]
par_left      -> [(]
par_right     -> [)]
colon         -> [:]
semicolon     -> [;]
comma         -> [,]
bracket_left  -> [[]
bracket_right -> []]
type          -> [i32] | [i64] | [f32] | [f64] | [bool]
reserved      -> [for] | [foreach] | [if] | [else] | [char] | [const]

```

## BNF

```
    <program>           ->  <statementList>
    <statementList>     ->  <statement> | <statementList> <statement>
    <statement>         ->  <assignment> | <loop> | 
    <aplicables>        ->  <logExp> | <matExp>

    <id>                ->  <letter> <identifier> | "_" <identifier> | <letter>
    <identifier>        ->  <number> <identifier> | <leter> <identifier> |  "_" <identifier> | <letter>
    <word>              ->  <number> <word> | <leter> <word> | <word> | <letter> | <expChar>
    <expChar>           ->  "#" | "@" | "/n" | ..... 
    <scope>             ->  "{" <statementList> "}"
    // Types
    <value>             ->  <letter> | <number> | <float> | <string> | <id>
    <types>             ->  "i32" | "i64" | "f32" | "f64" | "bool" | "char" |
    <letter>            ->  "a" | "b" | "c" | .... | "z" | "A" | "B" | "C"| ... | "Z" 
    <number>            ->  0 | 1 | 2 | .... | 9 | <number>
    <string>            ->  """ <word> """
    <float>             ->  <number> | <number> . <number> 
    // Assign
    <assignment>        ->  <type> <id> "=" <expression> ";" | <id> "=" <expression> ";" | <type> <id> "[" <num> "]" <assignment>
    // Expressions
    <expression>        ->  <logExp> | <logExp> | <relExp> | <id> | <value>
    <matExp>            ->  <matExp> <matOp> <matExp> | <expression>
    <relExp>            ->  <relExp>  <relOp> <Expression>
    <logExp>            ->  <logExp> <logOp> <logExp> | <unLogExp> | <id> | "("<logExp>")"
    <unLogExp>          ->  <unLogOp> <logExp> 
    <exp>               ->  <exp> <expOperator> <termExp> | <termExp> | "("<exp>")"
    <termExp>           ->  <termExp> <termOp> <matExp> 
    // Operators
    <matOp>             ->  "^"
    <expOp>             ->  "+" | "-"
    <termOp>            ->  "*" | "/"
    <logOp>             ->  "and" | "or" | "xor"
    <unLogOp>           ->  "not"
    // Controll
    <if>                ->  "if" <logExp> <scope> | "if" <relExp> <scope> | <if> <else>
    <else>              ->  "else" <scope> | "else" <if>
    //Loop
    <loop>              ->  <for> | <forEach>
    <for>               ->  "for" <assignment> ";" <logExp> ; 
    <forEach>           ->  "foeach" <assignment> ":" <id> <scope>
    // IO
    <IO>                ->  <print> | <put>
    <print>             ->  "->" <value> ";"
    <put>               ->  "<-" <id> ";"
```