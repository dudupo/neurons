#ifndef NEURON_H
#define NEURON_H

void calculate(struct linkedSynapse * synapses);
void push_synapse(struct linkedSynapse * linkedsynapse , struct synapse * item);
void inputneurons(struct neuron * neurons , struct linkedSynapse * linkedsynapse);
void Print();

#endif
