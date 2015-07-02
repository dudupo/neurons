/*


	the basic lego block of learnig mechine...  

	we want that the calculate time of each layer will-
	-be constant... 
		some ideas :
			* there will be a layers which there porose will be to decrease the
			number of active neurons... like n , 2n , 1/2 n , .... 
			* the power of the neurons is the analog calculeting .. we may want 
			to think how to mix synapsesIterator wsynapsesIteratorh the digsynapsesIteratoral-recurise calculeting.. 
			* we may want to make the active function as generic argument ...
			* we should think about how to normalete data to integer, and by that
			decrease the calculating time.
*/

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef LIST
#define LIST
#include <list>
#endif 

#ifndef QUEUE
#define QUEUE
#include <queue>
#endif 

#ifndef PAIR
#define PAIR
#include <utilsynapsesIteratory>
#endif


#ifndef SET			
#define SET			
#include <set>
#endif

#ifndef MATH
#define MATH
#include <math.h>
#endif


#include "neurons.hpp"



namespace neurons{
	
	static int ID = 0;

	struct neuron create_neuron(){
		struct neuron neu;
		neu.value = 0;
		neu.id = ID++;
		return neu;
	}
	struct synapse * create_synapse(struct neuron * neuIn ,
	 struct neuron * neuOut ){
		struct synapse * syn = new struct synapse;
		syn->weight = 0.5;
		return syn; 
	}

	void syn_connect(struct neuron * neuIn , struct neuron * neuOut){
		struct synapse * syn = create_synapse(neuIn , neuOut);
		neuIn->synapses.push_back(syn);
		neuOut->prevSynapses.push_back(syn);
		neuIn->synapses.back()->in = neuIn;
		neuIn->synapses.back()->out = neuOut;
		neuOut->prevSynapses.back()->in = neuIn;
		neuOut->prevSynapses.back()->out = neuOut;
	} 
	void
	 create_neural_network(struct neuron ** In , struct neuron ** Out ,
	  int inputscount , int outputscount){
		int neuronscount , synapsescount;
		std::cin >> neuronscount >> synapsescount; 

		struct neuron * neurons = new struct neuron [neuronscount]; 
		for (int i = 0 ; i < neuronscount; i++){
			neurons[i] = create_neuron();
			if (i < inputscount){
				In[i] = &neurons[i];
			}
		}
		for (int k = 0 , i = neuronscount - outputscount ; k < outputscount ; k++){
			Out[k] = &neurons[i];
			i++;
		}
		int I , J;
		for (int i = 0 ; i < synapsescount; i++){
			std::cin >> I >> J;
			syn_connect(&neurons[I] , &neurons[J]);
		}
	}
	void calculete(struct neuron **In , struct neuron ** Out){
		std::queue<struct neuron *> neuronsQueue;
		std::list<struct synapse *>::iterator synapsesIterator;
		std::set<int> neuronsSet;
		// first insert all the input to some neuronsQueueueue.
		for (int j = 0; In[j] != 0 ; j++){
			neuronsQueue.push(In[j]);
			neuronsSet.insert(In[j]->id);
		}
		while (!neuronsQueue.empty()){
			synapsesIterator = neuronsQueue.front()->synapses.begin();
			if (synapsesIterator != neuronsQueue.front()->synapses.end()){
				/* 
				   note that the nuerons sorted.
				   therefore when neuron get to the
				   front of the stack all the connected 
				   neurons to him, all radey have pass
				   their value.
				*/
				(*synapsesIterator)->in->value = normate((*synapsesIterator)->in->value);
			}
			while(synapsesIterator != neuronsQueue.front()->synapses.end()){
				// making step forword in the net.
				(*synapsesIterator)->out->value += (*synapsesIterator)->in->value * 
					(*synapsesIterator)->weight;
				// insert new neurons into the queue.
				if (neuronsSet.find((*synapsesIterator)->out->id) == neuronsSet.end()){
					neuronsQueue.push((*synapsesIterator)->out);
					neuronsSet.insert((*synapsesIterator)->out->id);
				}
				++synapsesIterator;
			}
			neuronsQueue.pop();
		}
		/* 
		   normate the last neurons... 
		   which haven`t pass the: 
		   "synapsesIterator != neuronsQueue.front()->synapses.end()"-test.
		*/ 
		struct neuron ** position = Out;
		while(position[0] != 0){
			position[0]->value = normate(position[0]->value);
			position++;
		} 
	}
	float normate(float x){
		return 1/(1 + exp(-x));
	}
	float dlogistic(float x){
		float w = exp(-x);
		return w/((1+w)*(1+w));
	}

#define Rate -0.6
	void optimize(struct neuron ** In , struct neuron ** Out , 
	 float * is , float * os){
		struct neuron ** position = In;
		while( is[0] != 0 && position[0] != 0 ){
			position[0]->value = is[0];
			position++;
			is++;
		}
		calculete(In , Out);
		position = Out;
		std::queue<struct neuron *> neuronsQueue;
		std::list<struct synapse *>::iterator synapsesIterator;
		std::set<int> neuronsSet;
		float delta;
		for (int j = 0 ; os[j] != 0 && position[j] != 0 ; j++ ){
			delta = dlogistic(position[j]->value)*(position[j]->value - os[j]);
			position[j]->delta = delta;
			neuronsQueue.push(position[j]);
			neuronsSet.insert(position[j]->id);
		}
		while (!neuronsQueue.empty()){
			synapsesIterator = neuronsQueue.front()->prevSynapses.begin();
			neuronsQueue.front()->delta *= dlogistic(neuronsQueue.front()->value);
			for (;synapsesIterator != neuronsQueue.front()->prevSynapses.end();++synapsesIterator){
				(*synapsesIterator)->weight += (*synapsesIterator)->out->value * delta * Rate;
				(*synapsesIterator)->in->delta += (*synapsesIterator)->weight *
				 neuronsQueue.front()->delta;
				if (neuronsSet.find((*synapsesIterator)->in->id) == neuronsSet.end()){
					neuronsQueue.push((*synapsesIterator)->in);
					neuronsSet.insert((*synapsesIterator)->in->id);
				}
			}
			neuronsQueue.pop();
		}
	}
	void RestValueDeltas(struct neuron ** In){
		std::queue<struct neuron *> neuronsQueue;
		std::list<struct synapse *>::iterator synapsesIterator;
		std::set<int> neuronsSet;
		for (int j = 0; In[j] != 0 ; j++){
			neuronsQueue.push(In[j]);
			neuronsSet.insert(In[j]->id);
		}
		while (!neuronsQueue.empty()){
			synapsesIterator = neuronsQueue.front()->synapses.begin();
			neuronsQueue.front()->value = 0;
			neuronsQueue.front()->delta = 0;
			while(synapsesIterator != neuronsQueue.front()->synapses.end()){
				if (neuronsSet.find((*synapsesIterator)->out->id) == neuronsSet.end()){
					neuronsQueue.push((*synapsesIterator)->out);
					neuronsSet.insert((*synapsesIterator)->out->id);
				}
				++synapsesIterator;
			}
			neuronsQueue.pop();
		}
	}

	

};


