#include <stdio.h>
#include <stdlib.h>

typedef
	struct t{
		double c;
		int e;
		struct t* prox;
	}Termo;
	typedef Termo* Poli;

Poli resetaPoli(Poli p){
	while(1){
		if(p->e == -1){
			return p;
		}else{
			p = p->prox;
		}
	}
}
void pTermo(Termo t){
	if (t.c == 0){
		return;
	}
	if(t.e < -1){
		printf("\033[91m((%.0f)/(X^(%d)))\033[97m", t.c, -t.e);
	}
	else if(t.e == -1){
		printf("\033[93m((%.4f)/X\033[97m", t.c);
	}
	else if(t.e == 0){
		printf("(%2.2f)", t.c);
	}
	else if(t.e == 1){
		printf("(%2.2f)*X", t.c);
	}
	else if(t.e > 1){
		printf("(%2.2f)*X^(%d)", t.c, t.e);
	}
}
void pPoli(Poli p){
	p = resetaPoli(p);
	if (p->prox == p && p->e == -1){
		printf("Polinomio nulo\n");
		return;
	}
	p = p->prox;
	pTermo(*p);
	p = p->prox;
	
	while(p->e != -1){
		printf(" + ");
		pTermo(*p);
		p = p->prox;
	}
	printf("\n");
}
Poli criaPoli(){
	Poli p = (Poli)malloc(sizeof(Termo));

	p->e = -1;
	p->c = 0;
	p->prox = p;

	return p;
}
void insereTermo(Poli p, int ex, double co){
	
	Termo* t = (Termo*)malloc(sizeof(Termo));

	t->e = ex;
	t->c = co;

	t->prox = p->prox;
	p->prox = t;
}
void removeTermo(Poli p, int *ex, double *co){
	Termo* t = p->prox;
	
	*ex = t->e;
	*co = t->c;

	p->prox = t->prox;
	
	free(t);
}
void destroiPoli(Poli p){
	int e_lixo;
	double c_lixo;
	p = resetaPoli(p);
	while(p->prox != p){
		removeTermo(p, &e_lixo, &c_lixo);
	}

	free(p);

	p = NULL;
}
Poli lePoli(){
	Poli p = criaPoli();
	int ex = 0;
	double co;

	printf("Insira os coeficientes e os expoentes\n");
	printf("de um polinômio em ordem decrescente:\n");
	while(ex >= 0){
		scanf("%lf %d", &co, &ex);
		if (co != 0 && ex >= 0){
			insereTermo(p,ex,co);
			p = p->prox;
		}
	}

	return p;
}
void copiaPoli(Poli a, Poli b){
	Poli bb = b = resetaPoli(b);
	Poli aa = a = resetaPoli(a);
	bb = bb->prox;
	while(bb != b){
		insereTermo(aa, bb->e, bb->c);
		bb = bb->prox;
		aa = aa->prox;
	}
}
Poli somaPoli(Poli p, Poli q){
	Poli r = criaPoli();
	Poli pp = p = resetaPoli(p);
	Poli qq = q = resetaPoli(q);
	
	pp = pp->prox;
	qq = qq->prox;

	/*Caso um deles ou os dois sejam nulos*/
	if(pp == p){
		copiaPoli(r, q);
		return r;
	}
	if(qq == q){
		copiaPoli(r, p);
		return r;
	}
	/*Caso nenhum dos dois sejam*/
	while(!((pp == p) && (qq == q))){
		if(pp->e == qq->e){
			if(pp->c + qq->c != 0){
				insereTermo(r, pp->e , pp->c + qq->c);
				r = r->prox;
			}
			pp = pp->prox;
			qq = qq->prox;

		}else if (pp->e > qq->e){
			insereTermo(r, pp->e , pp->c);
			pp = pp->prox;
			r = r->prox;
		}else{
			insereTermo(r, qq->e , qq->c);
			qq = qq->prox;
			r = r->prox;
		}
	}
	r = resetaPoli(r);
	return r;
}
Poli multiplicaPoli(Poli p, Poli q){
	Termo* pp = p = resetaPoli(p);
	Termo* qq = q = resetaPoli(q);
	Termo* rr = criaPoli();
	Poli r = rr;
	Termo* rr_aux;

	if(p->prox == p || q->prox == q){
		return r;
	}

	pp = pp->prox;
	while(pp != p){
		rr_aux = criaPoli();
		qq = qq->prox;
		while(qq != q){
			insereTermo(rr_aux, pp->e + qq->e, pp->c * qq->c);
			rr_aux = rr_aux->prox;
			qq = qq->prox;
		}
		rr = somaPoli(rr, rr_aux);
		pp = pp->prox;
		destroiPoli(rr_aux);
	}
	
	destroiPoli(pp);
	destroiPoli(qq);
	copiaPoli(r, resetaPoli(rr));
	destroiPoli(rr);
	return r;
}
int main(){
	Poli p = lePoli();
	Poli q = lePoli();
	Poli r = multiplicaPoli(p, q);
	pPoli(r);

	destroiPoli(p);
	destroiPoli(q);
	destroiPoli(r);

	return 0;
}
