#include <vector>
#include <list>
#include <math.h>
#include <algorithm>
#include "neurons.hpp"

namespace neurons 
{

	neuron::neuron()
	{
		this->value = 0.5;
	}

	synapse::synapse(neuron * in , neuron * out)
	{
		this->in = in;
		this->out = out;
		this->in->synapses.push_back(this);
		this->weight = 0.5;
	}

	layer::layer()
	{

	}

	net::net()
	{
		int number_of_layers , number_of_neurons  , number_of_synapses;
		std::cin >> number_of_layers  >> number_of_neurons >> number_of_synapses;
		
		this->layers = std::vector<layer *>(number_of_layers , new layer());
		std::vector<neuron> neurons ( number_of_neurons , neuron());

		int I , J; // I->point on the neuron, while J point on the layer.
		for (int i = 0 ; i < number_of_neurons ; i++)
		{
			std::cin >> I >> J;
			this->layers[J]->neurons.push_back(&neurons[I]);
		}
		for (int i = 0 ; i < number_of_synapses ; i++)
		{
			std::cin >> I >> J;
			synapse(&neurons[I] , &neurons[J]);
		}
	}

	void net::calculate()
	{

	}

	void net::feed()
	{

	}



};
