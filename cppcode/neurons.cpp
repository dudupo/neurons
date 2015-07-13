#include <vector>
#include <list>
#include <math.h>
#include <algorithm>
#include <map>
#include "neurons.hpp"
#include <stdio.h>
#include <cstdlib>

namespace neurons 
{
	neuron::neuron()
	{
		this->id = Id++;
		this->value = 0.5;
	}
	void neuron::normate()
	{
		this->value = 1 /( 1 + exp(- this->value));
	}
	double neuron::dnormate()
	{
		/* 
			should be called only after normate
		*/ 
		double w = this->value;
		return w* (1-w);
	}
	synapse::synapse(neuron * in , neuron * out)
	{
		this->in =  in;
		this->out = out;
		this->weight = 0.5;
	}
	synapse::synapse(neuron * in , neuron * out , double weight)
	{
		this->in =  in;
		this->out = out;
		this->weight = weight;
	}
	layer::layer()
	{

	}
	net::net() : net(std::cin)
	{
		
	}
	net::net(std::istream & is)
	{
		this->Rate = -10;

		int number_of_layers , number_of_neurons  , number_of_synapses;
		is >> number_of_layers  >> number_of_neurons >> number_of_synapses;
		std::vector<neuron *> neurons;
		
		for (int i = 0; i < number_of_layers; ++i)
			this->layers.push_back(new layer());

		for (int i = 0; i < number_of_neurons ;i++)
			neurons.push_back(new neuron());


		int I , J; // I->point on the neuron, while J point on the layer.
		for (int i = 0 ; i < number_of_neurons ; i++)
		{
			is >> I >> J;
			this->layers[J]->neurons.push_back(neurons[I]);
		}
		for (int i = 0 ; i < number_of_synapses ; i++)
		{
			is >> I >> J;
			neurons[I]->synapses.push_back( new synapse(neurons[I] , neurons[J]));
		}
	}
	void net::calculate_layer(layer * layer_ptr){
		neuron * neuron_ptr;
		synapse * synapse_ptr;
		for_each_neuron_in_layer(layer_ptr , iterator_neurons){
			neuron_ptr = *(iterator_neurons);
			neuron_ptr->normate();				
			for_each_synapse_in_neuron(neuron_ptr , iterator_synapses){
				synapse_ptr = *(iterator_synapses);
				send_sign(synapse_ptr);
			}			
		}
	}
	void net::calculate()
	{	
		open_flow(this , iterator_layer){
			this->calculate_layer(*iterator_layer);
		}
	}
	void net::feed()
	{
		for_each_neuron_in_layer(this->layers.front()
		 , iterator_neurons){
		 	/* 
		 		for some reason "cin >> (*iterator_neurons)->value;"
		 		and "scanf("%lf" , &(*iterator_neurons)->value);" dosn't
		 		work. run-time exception.
		 	*/
		 	double x; 
			scanf("%lf" , &x); 
			(*iterator_neurons)->value = x;
		}
	}
	void net::feed(std::vector<double> * input)
	{
		std::vector<double>::iterator it = input->begin();
		for_each_neuron_in_layer(this->layers.front()
		 , iterator_neurons){
			(*iterator_neurons)->value = *it;
			++it;
		}
	}
	std::vector<double> net::harvest(){
		return this->harvest(this->layers.back());
	}
	std::vector<double> net::harvest(layer * layer_ptr){
		std::vector<double> ret;
		for_each_neuron_in_layer(layer_ptr
		 , iterator_neurons){
			ret.push_back((*iterator_neurons)->value);
		}
		return ret;
	}
	std::map<int, double> net::backpropagation(
		std::vector<layer *>::iterator iterator_layer ,
		 std::vector<layer *>::iterator end , std::vector<double> * sample){
		
		std::map<int, double> map_deltas_current;

		if (iterator_layer != end && iterator_layer + 1 != end)
		{	
			
			this->calculate_layer( *iterator_layer );
			
			std::map<int, double> map_deltas =
			 this->backpropagation(iterator_layer+1 , end , sample);
			
			double temp_detla = 0 , temp; 
			for_each_neuron_in_layer((*iterator_layer) , iterator_neurons)
			{
				temp_detla = 0;
				for_each_synapse_in_neuron((*iterator_neurons) , iterator_synapses)
				{
					temp = map_deltas[(*iterator_synapses)->out->id];
					temp_detla += temp * (*iterator_synapses)->weight;
					(*iterator_synapses)->weight += (*iterator_neurons)->value * this->Rate *	temp;
				}
				temp_detla *= (*iterator_neurons)->dnormate();
				map_deltas_current[(*iterator_neurons)->id] = temp_detla;
			}
		}
		else if (iterator_layer != end){
			
			std::vector<double>::iterator iterator_sample = sample->begin();
			for_each_neuron_in_layer((*iterator_layer) , iterator_neurons)
			{
				/*
					note, that untill this point we hadn't
					normate the last layer. 
				*/
				(*iterator_neurons)->normate();

				if (iterator_sample == sample->end())
				{
					// the lengths of sample and output layer- 
					// -unequal , so the iterate should end .
					break;
				}

				map_deltas_current[(*iterator_neurons)->id ] =
				 ((*iterator_neurons)->value - (*iterator_sample)) * 
				 ((*iterator_neurons)->dnormate());

				 ++iterator_sample;	
			}	
		}
		return map_deltas_current;
	}
	void net::print()
	{
		char buffer[50];
		open_flow(this , iterator_layer){
			for_each_neuron_in_layer((*iterator_layer) , iterator_neurons){
				for_each_synapse_in_neuron((*iterator_neurons) , iterator_synapses){
					std::sprintf(buffer , "echo -e '\e[38;5;%im%i \e[39m\e[49m: \e[38;5;%im%i \e[39m\e[49m-> %f'" ,
					 18 +((*iterator_neurons)->id 		%240) ,(*iterator_neurons)->id,
					 18 +((*iterator_synapses)->out->id %240) ,(*iterator_synapses)->out->id,
					  (*iterator_synapses)->weight);
					std::system(buffer) ;
				}
			}
		}
	}
	void net::backpropagation(std::vector<double> * sample_in , std::vector<double> * sample_out){
		this->feed( sample_in );
		this->backpropagation( this->layers.begin() , this->layers.end() ,sample_out);
	}
	void net::clean(){
		open_flow(this , iterator_layer){
			for_each_neuron_in_layer((*iterator_layer) , iterator_neurons){
				(*iterator_neurons)->value = 0.0;
			}
		}
	}
	void net::train(std::vector<double> *sample_in ,
	 std::vector<double> *sample_out)
	{
		std::vector<double> resoult;
		this->clean();
		do {
			
			this->backpropagation(sample_in , sample_out);
			resoult = this->harvest();
			this->clean();
		}
		while (costf(sample_out , &resoult) > 0.01);
	}
	double costf(std::vector<double> * v , std::vector<double> * u)
	{
		double cost = 0;
		std::vector<double>::iterator j = u->begin();
		for (std::vector<double>::iterator i = v->begin(); i != v->end(); ++i){
			cost += std::pow((*i) - (*j),2);
			++j;
		}
		cost = std::sqrt(cost);
		return cost;
	}
	net & net::operator<<(std::vector<double> * input)
	{
		this->feed(input);
		return *this;
	}
	net & net::operator>>(std::vector<double> * resoult)
	{
		*resoult = this->harvest();
		return *this;
	}
	namespace net_factory
	{
		net * decode(std::istream & is)
		{
			net * Net = new net(is);
			open_flow(Net , iterator_layer){
				for_each_neuron_in_layer((*iterator_layer) , iterator_neurons){
					is >> (*iterator_neurons)->value;
					for_each_synapse_in_neuron((*iterator_neurons) , iterator_synapses){
						is >> (*iterator_synapses)->weight;
					}
				}
			}
			return Net;
		}
		void encode(net * Net , std::iostream & os)
		{
			open_flow(Net , iterator_layer){
				for_each_neuron_in_layer((*iterator_layer) , iterator_neurons){
					os << (*iterator_neurons)->value << " ";
					for_each_synapse_in_neuron((*iterator_neurons) , iterator_synapses){
						os << (*iterator_synapses)->weight << " ";
					}
				}
			}
		}
	};
	namespace net_trainer
	{


	};
};
