#include <iostream>
#include "neurons.cpp"


int main(int argc, char const *argv[])
{
	neurons::net Net = neurons::net();
	Net.calculate();
	return 0;
}