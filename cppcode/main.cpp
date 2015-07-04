#include <iostream>
#include "neurons.cpp"


int main(int argc, char const *argv[])
{
	neurons::net Net = neurons::net();
	std::vector<double> resoult;
	
	std::vector<double> sample_in {0.1 , 0.2 , 0.1 , 0.5 , 0.6 ,
									0.7 , 0.1 , 0.4 , 0.3 , 0.1};
	std::vector<double> sample_out {0.1 , 0.6 , 0.1 , 0.5 , 0.6 ,
									0.7 , 0.1 , 0.4 , 0.3 , 0.1};

	Net << &sample_in;
	Net.calculate();
	resoult = Net.harvest();
	
	for (std::vector<double>::iterator i = resoult.begin(); i != resoult.end(); ++i)
	{
		printf("%f \n", *i ); 
	}
	
	printf("\n\n");

	Net.train(&sample_in , &sample_out);

	Net << &sample_in;
	Net.calculate();
	resoult = Net.harvest();
	

	for (std::vector<double>::iterator i = resoult.begin(); i != resoult.end(); ++i)
	{
		printf("%f \n", *i );
	}
	Net.clean();
	return 0;
}