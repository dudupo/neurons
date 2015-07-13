#include <iostream>
#include "neurons.cpp"
#include <fstream>


int main(int argc, char const *argv[])
{
	//neurons::net_factory nf = neurons::net_factory();
	std::fstream is ("./data/datainput" , std::iostream::in | 
		std::iostream::out | std::iostream::app );
	neurons::net Net = *neurons::net_factory::decode(is);
	//Net.print();

	std::fstream istrain ("./data/data-train");
	std::fstream isquery ("./data/data-query"); 

	std::vector<double> resoult; 	//resoult of calculating.
	std::vector<double> input;		//values for feeding the input neurons.
	std::vector<double> output;		//the output values of the last layer.
	
	int outlength =  Net.layers.back()->neurons.size();
	int inlength  =  Net.layers.front()->neurons.size(); 
	int train_cases;
	int query_cases;
	istrain >> train_cases;
	isquery >> query_cases;
	
	double inpd;
	//@io-function, receiving training program. 
	for (int i = 0 ; i < train_cases ; i++)
	{
		for (int j = 0 ; j < inlength ; j++)
		{
			istrain >> inpd;
			input.push_back(inpd);
		}
		for (int j = 0 ; j < outlength ; j++)
		{
			istrain >> inpd;
			output.push_back(inpd);
		}
		Net.train(&input , &output);
		input.clear();
		output.clear();
	}
	//@user-interface, output formate. 
	char buffer[50];
	for (int k = 0 ; k < outlength ; k++)
	{
		std::sprintf(buffer , "echo -ne ' \e[38;5;27m%.5i\e[38;5;7m'" ,k);
		std::system(buffer);
	}
	std::system("echo ''");
	//@io-function, receiving querys. 
	for (int i =0 ; i < query_cases ; i++)
	{
		Net.clean();
		for (int j = 0; j < inlength ; j++)
		{
			isquery >> inpd;
			input.push_back(inpd); 
		}
		Net << &input;
		Net.calculate();
		Net >> &resoult;
		//@user-interface, output formate. 
		std::system("echo -n '>'");
		for (int j = 0 ; j < outlength ; j++)
		{
			std::sprintf(buffer , "echo -n '%1.3f '" ,resoult[j]);
			std::system(buffer);
		}
		std::system("echo ''");
		input.clear();
		output.clear();
		resoult.clear();
	}
	std::system("echo ''");

	/*std::vector<double> resoult;
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
	*/
	neurons::net_factory::encode(&Net , is );
	return 0;
}