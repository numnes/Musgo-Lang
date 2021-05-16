i32 menor;
const char a = 'a';
char b[6] = "string";
i32 vetor[4] = {10 , 20,40,50};
f64 f = 3.4445;
<- f;

// foreach
foreach x: vetor {
    if x + 1 < menor {
        menor = x;
    }
}

//classic for
i32 i;
for  i = 0; i < 4; i++ {
    if vetor[i] < menor {
        menor = x;
    }
}

-> "O menor numero eh ";
-> menor;
-> "\n";

if not (a and b) {
    -> "sim";
}
else {
    -> " ";
}
