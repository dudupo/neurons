if __name__ == "__main__":

	_file = open("../data/datainput" , 'w')

	Str = "2 2 14 30"

	for i in range (2 , 12):
		if (i % 2 == 0):
			Str += "\n" + "0 {0}".format(i);
		else:
			Str += "\n" + "1 {0}".format(i);
	for i in range (2 , 12):
		Str += "\n" + "{0} 12".format(i);
		Str += "\n" + "{0} 13".format(i);
	
	_file.write(Str)

