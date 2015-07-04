

struct pair
{
	int next;
	double data;
};
struct array_pair 
{
	struct pair position[1000];
};

#define neurons_pair struct array_pair
#define synapse_pair struct array_pair
#define synapse_weight data   

#define get_next( pair_instance , j )\
	pair_instance.position[ pair_instance.position[j].next]

#define iterate_array_pair( pair_instance , j )\
	for (; j >= 0 ; j = get_next( pair_instance , j ))

#define iterate_synapses iterate_array_pair


void recursive(neurons_pair * neurons_pair_instance,
  synapse_pair * synapse_pair_instance , int neuron ){
	iterate_array_pair(synapse_pair_instance ,
	  get_next(neurons_pair_instance , neuron)){

	}
	recursive( neurons_pair_instance , synapse_pair_instance , neuron+1 );

}
