//Libraries
#include "neuron.h"
//#include <stdlib.h>
using namespace std;
//begin
int main()
{
	//setup arduino
	void setup();
	//setup neuron array
	init_neuron_data();
	//Loop that stays active
	while (1)
	{	
		//gather sensory information
		ping();
		//connections betweeen neurons
		synapses();
		//calculate the state of each neuron
		for (int i=0;i<(number_of_neurons+1);i++)
		{
			neuron(i);
		}
		//fire all active neurons
		fire();

		//one cycle
	}
	return 0;
}


