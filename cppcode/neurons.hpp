
namespace neurons{
	
	struct neuron{
		float   value;
		float	delta;
		std::list<struct synapse *> synapses;
		std::list<struct synapse *> prevSynapses;
		int  id;
	};
	struct synapse{
		float   weight;
		struct neuron * in;
		struct neuron * out;
	};
	struct layer{
		std::list<struct neuron *> neurons;
	};
	struct net{
		std::list<struct layer  *> layers;
	};
	
	struct layer * create_layer();
	struct net *
	 create_neural_network(struct neuron ** In , struct neuron ** Out );
	
	struct neuron   create_neuron();
	struct synapse * create_synapse(struct neuron * neuIn ,
	 struct neuron * neuOut );
	void syn_connect(struct neuron * neuIn , struct neuron * neuOut);
	void calculete(struct neuron **In);
	float normate(float x);
	float dlogistic(float x);
	void optimize(struct neuron ** In , struct neuron ** Out , 
	 int * is , int * os);
	void RestValueDeltas(struct neuron ** In);

};

