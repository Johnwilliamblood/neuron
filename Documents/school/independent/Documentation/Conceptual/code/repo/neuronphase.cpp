//Libraries
#include "neuron.h"
using namespace std;

/*declare sensor pins for arduino
//sensor 1
int pingPin1 = 22;
int echoPin1 = 23;
//sensor2
int pingPin2 = 24;
int echoPin2 = 25;
//sensor 3
int pingPin3 = 26;
int echoPin3 = 27;
//sensor 4
int pingPin4 = 28;
int echoPin4 = 29;
//sensor 5
int pingPin5 = 30;
int echoPin5 = 31;
//sensor 6
int pingPin6 = 32;
int echoPin6 = 33;

//output pins


for arduino
void setup() 
{
-------------------------------------------------------------------------------------
Arduino specific, g++ doesn't understand

//Setup Motor A
pinMode(12, OUTPUT); //Initiates Motor Channel A pin
pinMode(9, OUTPUT); //Initiates Brake Channel A pin
//Setup Motor B
pinMode(13, OUTPUT); //Initiates Motor Channel A pin
pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
//Setup ping pins
pinMode(pingPin1, OUTPUT);
pinMode(echoPin1, INPUT); 
pinMode(pingPin2, OUTPUT);
pinMode(echoPin2, INPUT);  
pinMode(pingPin3, OUTPUT);
pinMode(echoPin3, INPUT);
pinMode(pingPin4, OUTPUT);
pinMode(echoPin4, INPUT);
pinMode(pingPin5, OUTPUT);
pinMode(echoPin5, INPUT);  
pinMode(pingPin6, OUTPUT);
pinMode(echoPin6, INPUT);
--------------------------------------------------------------------------------------------
}
*/


//begin
int main()
{
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
		death();

		//one cycle
	}
	return 0;
}














