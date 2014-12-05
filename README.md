NEURONAL NETWORK SIMULATION LIBRARY FOR ARDUINO (NNSLA)

Neuronal Network Simulation Library (NNSLA) is an open source c++ library that can be used to simulate neuronal networks. It is scalable and can be easily manipulated to use sensor inputs and motor outputs and create custom neuronal networks. 

USEAGE

The arduino.ino is an example of how to implenent this code in an arduino robot. The neuronal circuits and hardware are documented under the documentation folder using xmind files. A similar program using traditional coding methods is included as traditional_algorithm.ino. To use this software on a computer or to develop neuronal circuits neuronphase.cpp and neuron.h can be used.  

CUSTOMIZATION

To customize the properties of the neurons experiment by changing any of the numbers seen. The const int in neuron.h are a good starting point. These can be used to change the number of neurons, the neuron's resting potential, the neuron's excitatory threshold, the highest hyper-polarized state allowed, the pump-rate of the sodium potassium pump, and the rate at which hyper-polarized cells leak.  


GETTING STARTED

The setup(); function is an example setup function for Arduinos, you may cut it and paste it into the setup function normally found in Arduino code before the loop(); function. The setup(); function is to prepare the Arduino's pins and to initialize the data structure and prepare the simulated neurons by calling the init_neuron_data(); function  The structure which init_neuron_data(); initiates consist of an array of a neuron structures consisting of arrays for the neuron's ID, concentration, fire status, and gate status and then calls a function to set the neurons to resting potential.  


ADDING SENSORS AND CHANGING INPUT VALUES TO NEURONS

If using sensors create a function to read info from sensors and run this function at the begining of the main endless loop. Included is a ping(); function for six ping sensors. The example included is intended for Hc-sr04 proximity sensors.  


MAKING NEURONAL CONNECTIONS

The synapses(); function is where the synapses of a neuronal circuit are defined. The library comes with an example circuit. To create your own circuit use if statements with fire as the condition and number of either NA or k gates to open of another neuron as the code to execute if fire is true.        


PROCESSING NEURONS

Within the main loop the following for loop is recommended for(int i=0;i<number_of_neurons+1;i++). The i in this loop is fed to the neuron(i); function. The i will correspond to the ID of the neuron. The neuron(); function's job is to calculate the current status of the neuron by calling three other functions: setconcentration(int& i) pump(i);, and check(i);. 

The following three functions are all handled by the neuron(i); function.

The setconcentration(i); function sets each neuron's concentration based on how many gates were opened when synapse() was called earlier. 

The pump(i); function does three things: First it simulates the sodium potassium pump by increasing the concentration if it is below resting potential, second it allows the concentration to decrease if it is above resting potential, and third it limits the maximum concentration of a neuron to -80mv.

The check(i); function checks to see if the current neuron is below threshold. If the neuron's concentration is below its threshold it flags that neuron's fire status as 1 and sets the neuron to a hyper-polarized state. If the neuron is not below its threshold it sets the neuron's fire status to 0. In addition to this, cout displays a message indicating if the neuron has fired and what its concentration currently is.

ATP is is used by each neuron, when a neuron runs out of atp, it stops working. 


FIREING NEURONS

After the i in the for loop reaches the number_of_neurons+1 the for loop ends and should be followed by the fire(); function. The fire function is located outside of the for loop so that all the neurons are processed before acting on them. The current fire function interprets the pulse rate of two neurons as different speeds, and two other neurons as toggling a forward and reverse switch. The function motorcontrol(); is then called to use the information created by the fire function and send it to the hardware. After the fire(); function your loop should end and go back to ping to get new data to interpret.  

WARENTY AND LICENCING

As the user you are free to edit this code in anyway that you like and to use it in any way that you like. I am not liable for any misuse of this code and it is not under any warranty. You may feel free to email questions to me at NNSLA@johnblood.com but are not guaranteed a reply.             









