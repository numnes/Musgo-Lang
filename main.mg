i32 menor = 0;
i32 vetor[4] = {10,20,40,50};
f64 f = 3.4445;

// foreach
foreach x: vetor {
	if x < menor {
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