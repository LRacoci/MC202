int main() { 
	int N, R, *in, i;

	int aux;

	int MTFr = 0, TRr = 0, FCr = 0;
	Lista arqs;
	
	/*Se a entrada for muito estranha*/
	LeEntrada(&N, &R, &in);
	
	/*MTF*/
	cria_lista(&arqs);
	inicializaLista(&arqs, N);
	
	for (i = 0; i < R; i++){
		if (in[i] > 0) 
			aux = MTF(arqs, in[i]);
		else 
			aux = 0;
		
		MTFr += aux;

	}

	RemoveLista(&arqs);

	/*TR*/

	cria_lista(&arqs);
	inicializaLista(&arqs, N);

	for (i = 0; i < R; i++){
		if (in[i] > 0) 
			aux = TR(arqs, in[i]);
		else 
			aux = 0;
		
		TRr += aux;

	}

	RemoveLista(&arqs);

	/*FC*/

	cria_lista(&arqs);
	inicializaLista(&arqs, N);

	for (i = 0; i < R; i++){
		if (in[i] > 0) 
			aux = FC(arqs, in[i]);
		else 
			aux = 0;
		
		FCr += aux;

	}
		
	RemoveLista(&arqs);

	/*Final*/
	printf("%d %d %d\n", MTFr, TRr, FCr);

	free(in);
	return 0; 
}