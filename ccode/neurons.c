#include <stdlib.h>
#include <stdio.h>
//#include "neurons.h"

#define for_each_synapse(linkedsynapse)\
	while(linkedsynapse !=0) 
#define synapse_step(linkedsynapse)\
		linkedsynapse = linkedsynapse->next; 
#define flow(synapse)\
	synapse->out->potential += synapse->weight * synapse->in->potential;

struct neuron{
	float potential;
};
struct synapse{
	struct neuron * in;
	struct neuron * out;
	float weight; 
};
struct linkedSynapse{
	struct linkedSynapse * next;
	struct linkedSynapse * prev;
	struct synapse * synapseInstance;
};


void calculate(struct linkedSynapse * synapses)
{
	printf("i was here 1 \n");
	for_each_synapse(synapses)
	{
		if (synapses->next != 0){
			printf("i was here 2 \n");
			
			/*
			if (synapses->synapseInstance->in != 0 \
				&& synapses->synapseInstance->out != 0){
				printf("i was here 3 \n");
				flow(synapses->synapseInstance)
			}
			printf("i was here 4 \n");
			*/
		}
		printf("i was here 5 \n");
		//printf("%f \n" , synapses->synapseInstance->weight);
		synapse_step(synapses)
	}

}
void push_synapse(struct linkedSynapse * linkedsynapse , struct synapse * item)
{	
	struct linkedSynapse * ls; 
	ls->synapseInstance = item;
	ls->prev = linkedsynapse;
	linkedsynapse->next = ls;  
	linkedsynapse = ls; 
	
}
void inputneurons(struct neuron * neurons , struct linkedSynapse * linkedsynapse)
{	
	int n , m;
	// n -> number of synapses
	scanf("%d" , &n);
	// m -> number of neurons
	scanf("%d" , &m);

	struct synapse * synapses;
	synapses = (struct synapse *) malloc (sizeof(struct synapse) * n );
	neurons =  (struct neuron *)  malloc (sizeof(struct neuron)  * m );

	float potential , weight;
	
	printf("debug-potential : \n");

	int i ,I ,J ;
	for (i = 0 ; i < m ; i++)
	{
		scanf("%f" , &potential);
		printf("	>>>%f \n" , potential);
		neurons[i].potential = potential;
	}
	printf("debug-weight : \n");
	for (i = 0 ; i < n ; i++)
	{
		scanf("%d" , &I);
		scanf("%d" , &J);
		scanf("%f" , &weight);
		printf("	>>>%d ,%d ,%f \n" , I , J , weight);

		synapses[i].in  = &neurons[I];
		synapses[i].out = &neurons[J]; 
		synapses[i].weight = weight;

		if (i == 0)
		{
			//linkedsynapse = //(struct linkedSynapse * ) malloc (sizeof(struct linkedSynapse));
			linkedsynapse->synapseInstance = &synapses[i];
		}
		else
		{
			push_synapse(linkedsynapse , &synapses[i]);
		}

		//

		//there is no need to make a forword iteration
		//because the 'push_synapse' allredy did it.  
		//[ linkedsynapse = linkedsynapse->next; ]
	}
	printf("\n");

	for (int i = 0 ; i < n ; i++)
	{
		printf("	>>>%f \n", synapses[i].in->potential);
	}

	while(linkedsynapse != 0){
		//linkedsynapse = linkedsynapse->prev;
		break;
	}

}

void Print()
{
	printf("hello world \n");
}