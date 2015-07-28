from random import randint

def get_random(RANGE):
	return str(randint(0 ,RANGE)) + " "

if __name__ == '__main__':

	LENGTH = 10
	RANGE  = 256
	_net_file = open("./data/data-zip-net/zip-query" , 'w')

	STR = str(RANGE) + " " + str(LENGTH) + " " 
	for _ in range(LENGTH):
		STR += get_random(RANGE)

	_net_file.write(STR)
	_net_file.close()


