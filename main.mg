
i32 menor = 0;
i32 vetor[10] = {10,20,40,50};
f32 var = 10.151242;
const f64 v[4] = {2.25, 3.64, 7.26, 2.69};

// teste de codigo

foreach x: vetor {
	if x < menor and x != 0{
		menor = x;
    }
	else{
		-> "Não é o menor\n";
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
