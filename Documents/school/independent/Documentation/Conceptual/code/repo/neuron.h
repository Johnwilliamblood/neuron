/*This library is used to simulate neurons. 
It requires the use of synapses.h and action.h
*/
//libraries
#include <iostream>
#include <stdlib.h>     
#include <time.h> 
using namespace std;


//declare sensor pins
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

//store distances
long cm1, cm2, cm3, cm4, cm5, cm6;


//neuron info
const int number_of_neurons = 10;
//the neuron's resting potential -80mv is just 80 for simplicity 
const int resting_potential = 70;
//The threshold needed for an action potential 
const int threshold = 60;
const int hyperpolarized = 80;
//How many ions get through each pass the gate is open
const int pumprate = 2;
//How many ions leak through 
const int leakrate = 5;
//Neuron structure. Each neuron gets an id number, stores the ion level, if it fired, and gates open 
const int Time = 2;
//default speed, declare direction variable
long  speeda=200, speedb=200, DIRECTION;

//setup structs
typedef struct _Neuron
{
	int id;
	int concentration;
	int fire;
	int gates;
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
void synapses(int& i);
void initneurons();
//setup arduino
void setup();
//read sensors
void ping();
//control motors
void motorcontrol();
long microsecondsTocm(long microseconds);
void pump(int& i);

/*Functions
--------------------------------------------------------------------------------------*/




void setup() 
{

/*
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
--------------------------------------------------------------------------------------------*/
}


void initneurons()
{
	//Initialize program
	//set up structure 
	init_neuron_data();
	//sets all neurons to their resting potential 
	for (int i=0;i<number_of_neurons;i++)
	{
		mydata.neuron[i].concentration=resting_potential;
	}
	
	//random number time init
	srand (time(0));
	
}


//function to set each neuron id, set fire status to 0 and gate open status to 0 
void init_neuron_data()
{
	for (int i=0;i<number_of_neurons;i++)
	{ 
		mydata.neuron[i].id=i;
		mydata.neuron[i].fire=0;
		mydata.neuron[i].gates=0;
	}
}





//simulates the sodium potasium pump in the current (i) neuron
void neuron(int& i)
{
	//connections betweeen neurons
	synapses(i);
	//S-P pump
	pump(i);
	//check to see if current neuron reached action potential if so, save to mydata fire 
	check(i);


	//set new concentration based on number of open gates
	mydata.neuron[i].concentration=mydata.neuron[i].concentration-(mydata.neuron[i].gates);	
}


//manage ion gates manage dendrite's connection
void synapses(int& i)
{
		//sensor input
		//front right
		mydata.neuron[4].gates=(rand()%10)-5;
		//front left
		mydata.neuron[5].gates=(rand()%10);
		//back right
		mydata.neuron[6].gates=(rand()%10);
		//back left
		mydata.neuron[7].gates=(rand()%10);

		//front center
		mydata.neuron[8].gates=(rand()%10)-6;
		//back center
		mydata.neuron[9].gates=(rand()%10);



		/*effector neurons
-------------------------------------------------------------------------------------------		
		
		Direction Control
------------------------------------------------------------------------------------------

		Direction neuron forward, inhibits motor neurons in rear. */
		if (mydata.neuron[0].fire==1)
		{
			mydata.neuron[6].gates=mydata.neuron[6].gates-5;
			mydata.neuron[7].gates=mydata.neuron[7].gates-5;
		}		

		//Direction neuron reverse, inhibits motor neurons in front.
		if (mydata.neuron[1].fire==1)
		{
			mydata.neuron[4].gates=mydata.neuron[4].gates-5;
			mydata.neuron[5].gates=mydata.neuron[5].gates-5;
		}


		/*speed accumulators
-----------------------------------------------------------------------------------------------		
		neuron2 speeda
		neuron3 speedb
		*/



		/*sensor neurons
----------------------------------------------------------------------		

		Right and left sensors
----------------------------------------------------------------------		
	
		front right sensor*/

		if (mydata.neuron[4].fire==1)
		{
			mydata.neuron[2].gates=mydata.neuron[2].gates+20;
			mydata.neuron[3].gates=mydata.neuron[3].gates-1;
		}

		//front left sensor

		if (mydata.neuron[5].fire==1)
		{
			(mydata.neuron[2].gates=mydata.neuron[2].gates-1);
			(mydata.neuron[3].gates=mydata.neuron[3].gates+20);
		}

		//reverse right sensor

		if (mydata.neuron[6].fire==1)
		{
			(mydata.neuron[2].gates=mydata.neuron[2].gates+20);
			(mydata.neuron[3].gates=mydata.neuron[3].gates-1);
		}

		//reverse left sensor

		if (mydata.neuron[7].fire==1)
		{
			mydata.neuron[2].gates=(mydata.neuron[2].gates-1);
			mydata.neuron[3].gates=(mydata.neuron[3].gates+20);
		}
/*		Front and Reverse Sensors
------------------------------------------------------------------------------------

		

		Front Sensor*/

		if (mydata.neuron[8].fire==1)
		{
			mydata.neuron[0].gates=mydata.neuron[0].gates+10;
			mydata.neuron[1].gates=mydata.neuron[1].gates-10;
		}


		//Reverse Sensor
		//input

		if (mydata.neuron[9].fire==1)
		{
			mydata.neuron[1].gates=mydata.neuron[1].gates+10;
			mydata.neuron[0].gates=mydata.neuron[0].gates-10;
		}
}


void pump(int& i)
{
	//if the ions are lower than the resting potential pump adds number of ions defined in pumprate
	if (mydata.neuron[i].concentration<resting_potential)
	{
		mydata.neuron[i].concentration=mydata.neuron[i].concentration+pumprate;
	}
	if (mydata.neuron[i].concentration>resting_potential)
	{
		mydata.neuron[i].concentration=mydata.neuron[i].concentration-leakrate;
	}
}



void check(int& i)
{ 
	//if current neuron fired set fire status to 1 else set to 0 
	if (mydata.neuron[i].concentration<threshold)
	{
		mydata.neuron[i].fire = 1;	
		cout<<"neuron "<<i<<" fired, concentration:"<< mydata.neuron[i].concentration<<endl;
		mydata.neuron[i].concentration=hyperpolarized;
	}

	else
	{
		mydata.neuron[i].fire = 0;
		cout<<"neuron "<<i<<" concentration:"<< mydata.neuron[i].concentration<<endl;
	}

				
}











/*Functions
-----------------------------------------------------------------------------------------

ping function*/

void ping()
{
/*Arduino specific, g++ doesn't understand

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
}

//converts ping duration to cm
long microsecondsTocm(long microseconds)
{
   return microseconds / 29 / 2; 
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
		if(speeda<245) {speeda=speeda+10;}
	}
	if(mydata.neuron[2].fire==0)
	{
		if(speeda>0) {speeda=speeda-5;}
	}


	//motorb accumulator	
	//Speed pulse rate interpreter
	if(mydata.neuron[3].fire==1)
	{
		if(speedb<245) {speedb=speedb+10;}
	}
	if(mydata.neuron[3].fire==0)
	{
		if(speedb>0) {speedb=speedb-5;}
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
//reset gates and AP




	for (int j=0;j<resting_potential;j++)
	{
		mydata.neuron[j].gates=0;		
	}




}



