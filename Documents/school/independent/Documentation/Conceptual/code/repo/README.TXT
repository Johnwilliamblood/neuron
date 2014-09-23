NEURONAL NETWORK SIMULATION LIBRARY FOR ARDUINO

Neuronal Network Simulation Library (NNSL) is an open source c++ library that can be used to simulate neuronal networks. It is scalable and can be easily manipulated to use sensor inputs and motor outputs. 


USEAGE
The setup(); function is an example setup function for arduinos, you may cut it and paste it into the setup function normally found in arduino code before the loop(); function. The setup(); function is commented out to prevent accidental usage on computers rather than arduinos.   

To use NNSL include neuron.h as you would any other library. To use the NNSL library you must first call a function to initialize the data structure and prepare the simulated neurons: init_neuron_data(); This function should only be called once at the begining of the program unless you desire to reset all the data. The rest of your code should run in a loop that is either infinite or goes for a set period of time, or until it recieves some signal to end. The structure which init_neuron_data(); initiates consist of an array of a neuron structures consisting of arrays for the neuron's ID, concentration, fire status, and gate status.  

If using sensors edit the ping(); function to fit your sensors. The example included is commented out intended for Hc-sr04 proximity sensors. The section of the ping(); function that is not commented out consist of random number generators with some having additional weight by having numbers added or subtracted to the random number. This is useful for experimentation. The random number aspect is not required and can be replaced with just numbers to experiment with how the neuronal circuit behaves. 

The synapses(); function is where the synapses of a neuronal circuit are defined. The library comes with an example circuit. To create your own circuit use if statements with fire as the condition and number of gates to open of another neuron as the code to execute if fire is true.       

Within this loop the following for loop is recomended for(int i=0;i<number_of_neurons+1;i++). Within this loop i is fed to the neuron(i); function. The i will correspond to the ID of the neuron. The neuron(); function's job is to calculate the current status of the neuron by calling three other functions: setconcentration(int& i) pump(i);, and check(i);. 

The setconcentration(i); function sets each neuron's concentration based on how many gates were opened when synapse() was called earlier. Consider this the begining of the first cycle.

The pump(i); function does three things: First it simulates the sodium potasium pump by increasing the concentration if it is below resting potential, second it allows the concentration to decrease if it is above resting potential, and third it limits the maximum concentration of a neuron to 80mv.

The check(i); function checks to see if the current neuron is below threshold. If the neuron's concentration is below its threshold it flags that neuron's fire status as 1 and sets the neuron to a hyperpolarized state. If the neuron is not below its threshold it sets the neuron's fire status to 0. In addition to this, cout displays a messege indicating if the neuron fired and what its concentration currently is. 





