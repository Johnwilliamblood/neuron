NEURONAL NETWORK SIMULATION LIBRARY FOR ARDUINO

Neuronal Network Simulation Library (NNSL) is an open source c++ library that can be used to simulate neuronal networks. It is scalable and can be easily manipulated to use sensor inputs and motor outputs. 


USEAGE
The setup(); function is an example setup function for arduinos, you may cut it and paste it into the setup function normally found in arduino code before the loop(); function. The setup(); function is commented out to prevent accidental usage on computers rather than arduinos.   

To use NNSL include neuron.h as you would any other library. To use the NNSL library you must first call a function to initialize the data structure and prepare the simulated neurons: init_neuron_data(); This function should only be called once at the begining of the program unless you desire to reset all the data. The rest of your code should run in a loop that is either infinite or goes for a set period of time, or until it recieves some signal to end. The structure which init_neuron_data(); initiates consist of an array of a neuron structures consisting of arrays for the neuron's ID, concentration, fire status, and gate status.  

If using sensors edit the ping(); function to fit your sensors. The example included is commented out intended for Hc-sr04 proximity sensors. The section of the ping(); function that is not commented out consist of random number generators with some having additional weight by having numbers added or subtracted to the random number. This is useful for experimentation. The random number aspect is not required and can be replaced with just numbers to experiment with how the neuronal circuit behaves. 

The synapses(); function is where the synapses of a neuronal circuit are defined. The library comes with an example circuit. To create your own circuit use if statements with fire as the condition and number of gates to open of another neuron as the code to execute if fire is true.       

Within this loop the following for loop is recomended for(int i=0;i<number_of_neurons+1;i++). Within this loop i is fed to the neuron(i); function. The i will correspond to the ID of the neuron. The neuron(); function's job is to calculate the current status of the neuron by calling three other functions: pump(i);, check(i);, and setconcentration(int& i) 

