#include <iostream>
#include "neurons.cpp"


int main(int argc, char const *argv[])
{
	neurons::net Net = neurons::net();
	std::vector<double> resoult;
	
	for (int i =0 ; i < 3;i++){
		Net.feed();
		Net.calculate();
		resoult = Net.harvest();
		for (std::vector<double>::iterator i = resoult.begin(); i != resoult.end(); ++i)
		{
			printf("%f \n", *i ); 
		}
		Net.clean();
	}
	std::vector<double> sample_in (1 ,0.1);
	std::vector<double> sample_out (1, 0.2);
	for (int j = 0 ; j < 40 ; j++){
		Net.backpropagation(&sample_in , &sample_out);
		Net.clean();
		Net.feed(&sample_in);
		Net.calculate();
		resoult = Net.harvest();

		for (std::vector<double>::iterator i = resoult.begin(); i != resoult.end(); ++i)
		{
			std::cout << *i	<< " ,";
		}

		Net.clean();
		std::cout << "\n";
	}

	/*	
	std::list<int> mylist; 

	mylist.push_back(1);

	for (std::list<int>::iterator it = mylist.begin();
	 it != mylist.end(); 
		++it ){
		std::cout << *it << std::endl;
	}
	for (std::list<int>::iterator it = mylist.begin();
	 it != mylist.end(); 
		++it ){
		std::cout << *it << std::endl;
	}
	*/
	return 0;
}