#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef PAIR
#define PAIR
#include <utility>
#endif

#include "neurons.cpp"



int main()
{

	
	std::cout << "hello world!" << std::endl;

	int inputscount , outputscount;
	std::cin >> inputscount >> outputscount;
	struct neurons::neuron ** In  = new struct neurons::neuron * [inputscount];
	struct neurons::neuron ** Out = new struct neurons::neuron * [outputscount]; 
	neurons::create_neural_network(In , Out , inputscount , outputscount);
	
	

	
	
	/*
	while (!ret.empty()){
		std::cout << ret.front()->value << std::endl;
		ret.pop();
	}
	*/

	std::cout << "-----------" << std::endl;
	
	float sample [2]= { 0.1 , 1};
	float inputsample[2] = {0.7 , 0.7};

	optimize(In , Out , inputsample , sample);
	RestValueDeltas(In);
	In[0]->value = 0.7;
	In[1]->value = 0.7;
	neurons::calculete(In , Out);
	while(In[0] != 0){
		std::cout << In[0]->value << std::endl;
		In++; 
	}

	while(Out[0] != 0){
		std::cout << Out[0]->value << std::endl;
		Out++; 
	}
	
} 