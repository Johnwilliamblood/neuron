/*This library is used to simulate neurons. 
---------------------------------------------------------------------------------------------------------

libraries*/
#include <iostream>
#include <stdlib.h>     
using namespace std;



//store sensory info
long cm1, cm2, cm3, cm4, cm5, cm6, voltagea, voltageb;


//neuron info
const int number_of_neurons = 11;
//the neuron's resting potential -80mv is just 80 for simplicity 
const int resting_potential = -700;
//The threshold needed for an action potential 
const int threshold = -600;
//hyperpolarized state
const int hyperpolarized = -800;
//How many ions get through each pass the gate is open
const int pumprate = 35;
//How many ions leak through leaky channel
const int leakrate = 10;

//Synapse strengths
const int speedexcite = 200;
const int speedinhibit = 5;
const int epiexcite = 300;
const int epiinhibit = 50;
const int directionexcite = 160;
const int directioninhibit = 25;
const int directionmodulator = 0;



//default speed, declare direction variable
long  speeda=200, speedb=200, DIRECTION;

//setup structs
typedef struct _Neuron
{
	int id;
	int concentration;
	int fire;
	int NAgates;
	int kgates;
	int epireceptor;
} NEURON;
//array of neurons 
typedef struct _mydata
{
	int data[];
	NEURON neuron[number_of_neurons];	
	}
	MYDATA;
	MYDATA mydata;


//declare functions
void fire();	
void init_neuron_data();
void neuron(int& i);
void check(int& i);
void setconcentration(int& i);
void synapses();
void initneurons();
//read sensors
void ping();
//convert sensory to neural
void sensory();
//control motors
void motorcontrol();
long microsecondsTocm(long microseconds);
void pump(int& i);

//------------------------------------------------------------------------------------

/*Functions
--------------------------------------------------------------------------------------*/

//function to set each neuron id, set fire status to 0 and gate open status to 0 
void init_neuron_data()
{
	for (int i=0;i<(number_of_neurons+1);i++)
	{ 
		mydata.neuron[i].id=i;
		mydata.neuron[i].fire=0;
		mydata.neuron[i].NAgates=0;
		mydata.neuron[i].kgates=0;
		mydata.neuron[i].epireceptor=0;
	}
	//set resting potential
	initneurons();
}

void initneurons()
{
	//Initialize program
	//set up structure 
	//sets all neurons to their resting potential 
	for (int i=0;i<(number_of_neurons+1);i++)
	{
		mydata.neuron[i].concentration=resting_potential;
	}
}

//ping function

void ping()
{
	/*
	//Arduino specific, g++ doesn't understand
	//variables 
	long duration; 
	//quick burst of electricity to the proximity sensor to activate it 
	digitalWrite(pingPin1, LOW);
	delayMicroseconds(2);
 	digitalWrite(pingPin1, HIGH);
	delayMicroseconds(5);
	digitalWrite(pingPin1, LOW);  
	//reads signal that bounces back
	duration= pulseIn(echoPin1,HIGH);
	//converts duration to cm using function below 
 	cm1 = microsecondsTocm(duration);
	digitalWrite(pingPin2, LOW);
 	delayMicroseconds(2);
	digitalWrite(pingPin2, HIGH);
 	delayMicroseconds(5);
 	digitalWrite(pingPin2, LOW);  
	//reads signal that bounces back
  	duration= pulseIn(echoPin2,HIGH);
	//converts duration to cm using function below 
 	cm2 = microsecondsTocm(duration);
  	digitalWrite(pingPin3, LOW);
  	delayMicroseconds(2);
  	digitalWrite(pingPin3, HIGH);
  	delayMicroseconds(5);
  	digitalWrite(pingPin3, LOW);   
	//reads signal that bounces back
 	duration= pulseIn(echoPin3,HIGH);
	//converts duration to cm using function below 
 	 cm3 = microsecondsTocm(duration);

 	 digitalWrite(pingPin4, LOW);
 	 delayMicroseconds(2);
 	 digitalWrite(pingPin4, HIGH);
 	 delayMicroseconds(5);
 	 digitalWrite(pingPin4, LOW);   
	//reads signal that bounces back
 	duration= pulseIn(echoPin4,HIGH);
	//converts duration to cm using function below 
 	cm4 = microsecondsTocm(duration);  
 	digitalWrite(pingPin5, LOW);
	delayMicroseconds(2);
 	digitalWrite(pingPin5, HIGH);
 	delayMicroseconds(5);
 	digitalWrite(pingPin5, LOW);  
	//reads signal that bounces back
	duration= pulseIn(echoPin5,HIGH);
	//converts duration to cm using function below 
 	cm5 = microsecondsTocm(duration); 
	digitalWrite(pingPin6, LOW);
	delayMicroseconds(2);
	digitalWrite(pingPin6, HIGH);
 	delayMicroseconds(5);
	digitalWrite(pingPin6, LOW);   
	//reads signal that bounces back
	duration= pulseIn(echoPin6,HIGH);
	//converts duration to cm using function below 
	cm6 = microsecondsTocm(duration);
	*/
	sensory();
}

void sensory()
{
	//front right
	mydata.neuron[4].NAgates=0;
	//front leftt
	mydata.neuron[5].NAgates=0;
	//back right
	mydata.neuron[6].NAgates=200;
	//back lef5
	mydata.neuron[7].NAgates=87;
	//front cent15
	mydata.neuron[8].NAgates=0;
	//back center
	mydata.neuron[9].NAgates=160;
	//if stuck while direction is 0
	mydata.neuron[10].NAgates=0;
	//if stuck while direction is 1
	mydata.neuron[11].NAgates=220;
}

//converts ping duration to cm
long microsecondsTocm(long microseconds)
{
   return microseconds / 29 / 2; 
}

//manage ion gates manage dendrite's connection
void synapses()
{
	//talk about neurotransmitters (modled effect of excite/inhib connections/synapse.
	//This simulates the effect of excititory and inhibitory neurotransmitters on ion channels in the post synaptic membrane		
	if (mydata.neuron[4].fire==1)
	{
		mydata.neuron[2].NAgates=mydata.neuron[2].NAgates+speedexcite;
		mydata.neuron[3].kgates=mydata.neuron[3].kgates+speedinhibit;
	}
	//front left sensor
	//This simulates the effect of excititory and inhibitory neurotransmitters on ion channels in the post synaptic membrane
	if (mydata.neuron[5].fire==1)
	{
		mydata.neuron[2].kgates=mydata.neuron[2].kgates+speedinhibit;
		mydata.neuron[3].NAgates=mydata.neuron[3].NAgates+speedexcite;
	}
	//reverse right sensor
	//This simulates the effect of excititory and inhibitory neurotransmitters on ion channels in the post synaptic membrane
	if (mydata.neuron[6].fire==1)
	{
		mydata.neuron[2].NAgates=mydata.neuron[2].NAgates+speedexcite;
		mydata.neuron[3].kgates=mydata.neuron[3].kgates+speedinhibit;
	}
	//reverse left sensor
	//This simulates the effect of excititory and inhibitory neurotransmitters on ion channels in the post synaptic membrane
	if (mydata.neuron[7].fire==1)
	{
		mydata.neuron[2].kgates=mydata.neuron[2].kgates+speedinhibit;
		mydata.neuron[3].NAgates=mydata.neuron[3].NAgates+speedexcite;
	}

	//Front Sensor*/
	//This simulates the effect of excititory and inhibitory neurotransmitters on ion channels in the post synaptic membrane
	if (mydata.neuron[8].fire==1)
	{
		mydata.neuron[0].NAgates=mydata.neuron[0].NAgates+directionexcite;
		mydata.neuron[1].kgates=mydata.neuron[1].kgates+directioninhibit;
	}
	//Reverse Sensor
	//This simulates the effect of excititory and inhibitory neurotransmitters on ion channels in the post synaptic membrane		
	if (mydata.neuron[9].fire==1)
	{
		mydata.neuron[1].NAgates=mydata.neuron[1].NAgates+directionexcite;
		mydata.neuron[0].kgates=mydata.neuron[0].kgates+directioninhibit;
	}
	//Neuromodulators 
	//Direction neuron forward, inhibits sensor neurons in rear. 		
	//This simulates the effect of an indirect antagonistic neuromodulator closing the NA gates on certain neurons 
	if (DIRECTION==0)
	{
		mydata.neuron[6].NAgates=directionmodulator;
		mydata.neuron[7].NAgates=directionmodulator;			
	}	
	//Direction neuron reverse, inhibits sensor neurons in front.
	//This simulates the effect of an indirect antagonistic neuromodulator closing the NA gates on certain neurons 		
	if (DIRECTION==1)
	{
		mydata.neuron[4].NAgates=directionmodulator;
		mydata.neuron[5].NAgates=directionmodulator;			
	}
	//if the wheel stops (robot is stuck) it tries to fix the situation. 
	if (mydata.neuron[10].fire==1)	
	{	
		mydata.neuron[2].NAgates=mydata.neuron[2].NAgates+epiexcite;
		mydata.neuron[3].NAgates=mydata.neuron[3].NAgates+epiexcite;
		mydata.neuron[1].NAgates=mydata.neuron[1].NAgates+epiexcite;
		mydata.neuron[0].kgates=mydata.neuron[0].kgates+epiinhibit;
	}
	if (mydata.neuron[11].fire==1)	
	{	
		mydata.neuron[2].NAgates=mydata.neuron[2].NAgates+epiexcite;
		mydata.neuron[3].NAgates=mydata.neuron[3].NAgates+epiexcite;
		mydata.neuron[0].NAgates=mydata.neuron[0].NAgates+epiexcite;
		mydata.neuron[1].kgates=mydata.neuron[1].kgates+epiinhibit;
	}
}

//simulates the sodium potasium pump in the current (i) neuron
void neuron(int& i)
{
	setconcentration(i);

	//S-P pump
	pump(i);

	//check to see if current neuron reached action potential if so, save to mydata fire 
	check(i);

	mydata.neuron[i].NAgates=0;
	mydata.neuron[i].kgates=0;
}

void setconcentration(int& i)
{
	//set new concentration based on number of open gates
	mydata.neuron[i].concentration=mydata.neuron[i].concentration+(mydata.neuron[i].NAgates);
	mydata.neuron[i].concentration=mydata.neuron[i].concentration-(mydata.neuron[i].kgates);
}

void pump(int& i)
{
	//if the ions are lower than the resting potential pump adds number of ions defined in pumprate
	if (mydata.neuron[i].concentration>resting_potential)
	{
		mydata.neuron[i].concentration=mydata.neuron[i].concentration-pumprate;
	}

	//if the concentration is too high ions will leak out. 
	if (mydata.neuron[i].concentration<resting_potential)
	{
		mydata.neuron[i].concentration=mydata.neuron[i].concentration+leakrate;
	}

	//This is to limit the number of ions available.
	if (mydata.neuron[i].concentration<-1000)
	{
		mydata.neuron[i].concentration=hyperpolarized;
	}
}

void check(int& i)
{ 
	//if current neuron fired set fire status to 1 else set to 0 
	if (mydata.neuron[i].concentration>threshold)
	{
		mydata.neuron[i].fire = 1;	
		cout<<"neuron "<<i<<" fired! charge:"<< mydata.neuron[i].concentration/10<<endl;
		mydata.neuron[i].concentration=hyperpolarized;
	}

	else
	{
		mydata.neuron[i].fire = 0;
		cout<<"neuron "<<i<<"        charge"<< mydata.neuron[i].concentration/10<<endl;
	}
				
}

/*What happens when different neurons fire
------------------------------------------------------------------------------------------*/
void fire()
{
/*		Speed control
------------------------------------------------------------------------


	motora accumulator*/
	//Speed pulse rate interpreter 
	if(mydata.neuron[2].fire==1)
	{
		if(speeda<245) {speeda=speeda+5;}
	}
	if(mydata.neuron[2].fire==0)
	{
		if(speeda>75) {speeda--;}
	}


	//motorb accumulator	
	//Speed pulse rate interpreter
	if(mydata.neuron[3].fire==1)
	{
		if(speedb<245) {speedb=speedb+5;}
	}
	if(mydata.neuron[3].fire==0)
	{
		if(speedb>75) {speedb--;}
	}



    /*Direction Control
    ------------------------------------------------------------------------------------------*/
	if (mydata.neuron[0].fire==1)
	{
		DIRECTION=0;
	}		
	//Direction neuron reverse, inhibits motor neurons in front.
	if (mydata.neuron[1].fire==1)
	{
		DIRECTION=1;
	}
	for (int j=0;j<15;j++)
	{
		cout<<"-";
	}
	cout<<endl;

//	motorcontrol();
	cout<<"Direction:"<<DIRECTION<<" speeda:"<<speeda<<" speedb:"<<speedb<<endl;
}



//motor control
  void motorcontrol()
  {
    /*Arduino specific, g++ doesn't understand
    digitalWrite(12, DIRECTION); //Establishes forward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, speeda);   //Spins the motor on Channel A at full speed
    digitalWrite(13, DIRECTION); //Establishes forward direction of Channel A
    digitalWrite(8, LOW);   //Disengage the Brake for Channel A
    analogWrite(11, speedb);   //Spins the motor on Channel A at full speed 
    */
  }


