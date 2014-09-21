//Libraries
#include <iostream>
#include "neuron.h"
using namespace std;
//declare variable
int keep_going=0;
//begin.
int main()
{
	void setup();
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

			
	
		//fire all active neurons
		fire();

		//one cycle
	}
	return 0;
}


