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
		//this->synapses.resize(0);
	}

	void neuron::normate()
	{
		this->value = 1 /( 1 + exp(- this->value));
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
		layer * layer_ptr;
		neuron * neuron_ptr;
		synapse * synapse_ptr;
		open_flow(this , iterator_layer)
		{
			layer_ptr = *(iterator_layer);
			for_each_neuron_in_layer(layer_ptr , iterator_neurons)
			{
				neuron_ptr = *(iterator_neurons);
				neuron_ptr->normate();
				for_each_synapse_in_neuron(neuron_ptr , iterator_synapses)
				{
					std::cout << "hi?" << std::endl;
					synapse_ptr = *(iterator_synapses);
					send_sign(synapse_ptr);
				}
				//std::cout << "hi?" << std::endl;
			}
		}
	}


	void net::feed()
	{

	}

};
