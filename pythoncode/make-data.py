def ff(A):
	ret = 1
	for a in A:
		ret *= a
	return ret


if __name__ == "__main__":

	_file = open("./data/datainput" , 'w')

	layers = [10 , 12 , 10]
	Str = "{0} {1} 240 \n".format(len(layers) , sum(layers))
	
	j , k = 0 , 0
	for layer in layers:
		for t in range(layer):
			Str += "{0} {1} \n".format(j , k)
			j+=1
		k += 1

	for x in range(10):
		for y in range(10, 22):
			Str += "{0} {1} \n".format(x , y)
	for x in range(10 , 22):
		for y in range(22 , 32):
			Str += "{0} {1} \n".format(x , y)

	
	_file.write(Str)

