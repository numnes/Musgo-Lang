i64 z = 3;
bool k = true;
bool l = false;
bool menor = k and l;
i32 maior = 6;

char a = 'a';
i32 vetor[4] = {10,20,40,50};
f64 f = 3.4445;

// foreach
foreach x: vetor {
	if x < maior {
		maior = x;
	}
}
x++;
maior = 3;

//classic for
i32 i;
for i = 0; i < 4; i++ {
	if vetor[i] < maior {
		maior = x;
	}
}

-> "O menor numero eh ";
-> menor;
-> "\n";
