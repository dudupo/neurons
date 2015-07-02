namespace neurons 
{
	class synapse;

	class neuron
	{
		public:
			int id;
			float value;
			std::list<synapse *> synapses;
			neuron();
			//~neuron();	
	};

	class synapse
	{
		public:
			float weight;
			neuron *in;
			neuron *out;
			synapse(neuron *in , neuron *out);
			//~synapse();
		
	};
	class layer
	{
		public:
			std::list<neuron *> neurons;
			layer();
			//~layer();
	};

	class net
	{
		public:
			std::vector<layer *> layers;
			//std::vector<synapse *> synapses_heap;
			net();
			void calculate();
			void feed();
			//~net();
	};


	#define for_each_synapse_in_neuron(Neuron , iterator_synapse) \
		for (std::list<synapse *> iterator_synapse = \
		 Neuron->synapses::begin(); \
			iterator_synapse != Neuron->synapses::end(); \
			 ++iterator_synapse)

	#define for_each_neuron_in_layer(Layer , iterator_neurons) \
		for (std::list<neuron *> iterator_neurons = \
		 Layer->neurons::begin(); \
		 	iterator_neurons != Layer->neurons::end(); \
		 	 ++iterator_neurons)

	#define open_flow(Net , iterator_layers) \
		for (std::vector<layer *>::iterator iterator_layers = \
		 Net->layers::begin(); \
			iterator_layers != Net->layers::end() ; \
			 ++iterator_layers)



};