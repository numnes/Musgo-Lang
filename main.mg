
i32 menor = 0;
i32 vetor[10] = {10,20,40,50};

foreach x: vetor {
	if x < menor {
		menor = x;
    }
}

for i32  i = 0; i < 4; i++{
	if vetor[i] < menor {
		menor = x;
    }
}

-> "O menor numero eh: ";
-> menor;
-> "\n";
