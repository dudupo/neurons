namespace neurons 
{
	class synapse;

	static int Id = 0;

	class neuron
	{
		public:
			int id;
			double value;
			std::list<synapse *> synapses;
			neuron();
			void normate();
			double dnormate();
			// void virtual normate();
			//~neuron();	
	};
	class synapse
	{
		public:
			double weight;
			neuron *in;
			neuron *out;
			synapse(neuron *in , neuron *out);
			synapse(neuron *in , neuron *out , double weight);
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
			net(std::istream & is);
			net();
			void calculate_layer(layer * layer_ptr);
			void calculate();
			void feed();
			void feed(std::vector<double> * input);
			std::vector<double> harvest();
			std::vector<double> harvest(layer * layer_ptr);
			std::map<int, double> backpropagation(
				std::vector<layer *>::iterator iterator_layer ,
		 		std::vector<layer *>::iterator end , std::vector<double> * sample);
			void backpropagation(std::vector<double> * sample_in , std::vector<double> * sample_out);
			void clean();
			void train(std::vector<double> *sample_in , std::vector<double> * sample_out);
			net & operator<<( std::vector<double> * input);
			net & operator>>( std::vector<double> * resoult);
			double Rate;
			void print();
			//~net();
	};

	
	#define for_each_synapse_in_neuron(Neuron , iterator_synapse) \
		for (std::list<synapse *>::iterator iterator_synapse = \
		 Neuron->synapses.begin(); \
			iterator_synapse != Neuron->synapses.end(); \
			 ++iterator_synapse)

	#define for_each_neuron_in_layer(Layer , iterator_neurons) \
		for (std::list<neuron *>::iterator iterator_neurons = \
		 Layer->neurons.begin(); \
		 	iterator_neurons != Layer->neurons.end(); \
		 	 ++iterator_neurons)

	#define open_flow(Net , iterator_layers) \
		for (std::vector<layer *>::iterator iterator_layers = \
		 Net->layers.begin(); \
			iterator_layers != Net->layers.end() ; \
			 ++iterator_layers)

	void inline send_sign(synapse * synapse_ptr)
	{
		synapse_ptr->out->value +=
		 synapse_ptr->weight * synapse_ptr->in->value;
	}

	double costf(std::vector<double> * v , std::vector<double> * u);
	
	namespace net_factory
	{
		void encode(net * Net , std::iostream & os);
		net * decode(std::istream & is);
	};
	namespace net_trainer
	{
		class trainer{
			public:
				trainer();
		};
	};

};