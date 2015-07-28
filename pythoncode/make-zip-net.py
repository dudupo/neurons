

if __name__ == "__main__":

	LAYERS = 1; 
	NEURONS_IN_LAYER = 15;

	_net_file = open("./data/data-zip-net/zip-net" , 'w')

	neurons  = NEURONS_IN_LAYER * LAYERS
	iner_synapses = 0
	temp = NEURONS_IN_LAYER ** 2
	
	for J in range(1 ,LAYERS ,2):
		iner_synapses += temp

	synapses = NEURONS_IN_LAYER * 2 + iner_synapses
	STR = ""
	STR +="{0} {1} {2} \n".format(LAYERS + 2,
	 NEURONS_IN_LAYER + 2 , synapses )

	STR +="0 0 \n"
	for j in range(LAYERS):
		for i in range(NEURONS_IN_LAYER):
			STR +="{0} {1} \n".format(
				   (j*NEURONS_IN_LAYER) + i + 1 , j + 1)
	STR +="{0} {1} \n".format(neurons+1 ,LAYERS+1)

	for j in range(NEURONS_IN_LAYER):
		STR +="0 {0} \n".format(j+1)

	for j in range(LAYERS-1):
		for i in range(NEURONS_IN_LAYER):
			for k in range(NEURONS_IN_LAYER):
				STR +="{0} {1} \n".format(
				 j*NEURONS_IN_LAYER + k , (j+1)*NEURONS_IN_LAYER + i)

	for j in range(NEURONS_IN_LAYER):
		STR +="{0} {1} \n".format(
			j + (NEURONS_IN_LAYER*(LAYERS-1)) +1, neurons+1)
	_net_file.write(STR)
	_net_file.close()