//Libraries
#include <iostream>
#include "neuron.h"
using namespace std;
//declare variable
int keep_going=0;
//begin
int main()
{
	//setup arduino
	void setup();
	//setup neuron array
	initneurons();
	//Loop that stays active
	while (keep_going<Time)
	{	
	//	ping();
		//calculate the state of each neuron
		for (int i=0;i<number_of_neurons;i++)
		{
			neuron(i);
		}

		for (int i=0;i<number_of_neurons;i++)
		{
			check(i);	
		}

		for (int i=0;i<number_of_neurons;i++)
		{
			setconc(i);
		}
		//check to see if current neuron reached action potential if so, save to mydata fire 


		

			
	
		//fire all active neurons
		fire();

		//one cycle
	}
	return 0;
}


