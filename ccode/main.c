#include "neurons.c"

void expriment()
{
	int n , m;
	scanf("%d" , &n);
	scanf("%d" , &m);

	printf("%d \n" , n);
	printf("%d \n" , m);
}

int main()
{
	struct linkedSynapse * ls;
	struct neuron  *  neurons; 
	 
	inputneurons( neurons , ls );
	

	//printf("debug.... %f " , ls->synapseInstance->weight);

	//ls = ls->prev;
	//while(ls != 0)
	//	ls = ls->prev;	

	calculate(ls);

	Print();
}