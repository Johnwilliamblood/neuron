//libraries

#include <stdlib.h>  

//declare sensor pins for arduino
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

int voltageaPin = A0;
int voltagebPin = A1;

//output pins
int motoraPin = 12;
int motoraBreak = 9;

int motorbPin = 13;
int motorbBreak = 8;

int speedaPin = 3;
int speedbPin = 11;


//store sensory info
long cm1, cm2, cm3, cm4, cm5, cm6, voltagea, voltageb;

int temp=0;

//neuron info
const int number_of_neurons = 12;
//the neuron's resting potential -80mv is just 80 for simplicity 
const int resting_potential = -700;
//The threshold needed for an action potential 
const int threshold = -600;
//hyperpolarized state
const int hyperpolarized = -800;
//How many ions get through each pass the gate is open
const int pumprate = 20;
//How many ions leak through leaky channel
const int leakrate = 10;

//Synapse strengths
const int speedexcite = 300;
const int speedinhibit = 25;
const int speedthreshold = 600; //cm
const int epiexcite = 300;
const int epiinhibit = 300;
const int directionexcite = 400; 
const int directioninhibit = 300;
const int directionmodulator = 0;
const int directionthreshold = 40; //cm



//default speed, declare direction variable
long  speeda=200, speedb=200, DIRECTION;

//setup structs
typedef struct _Neuron
{
  int id;
  long long atp;
  int state;
  int concentration;
  int fire;
  int NAgates;
  int kgates;
  int epireceptor;
} 
NEURON;
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


void setup() 
{
  //Setup Motor A
  pinMode(motoraPin, OUTPUT); //Initiates Motor Channel A pin
  pinMode(motoraBreak, OUTPUT); //Initiates Brake Channel A pin
  //Setup Motor B
  pinMode(motorbPin, OUTPUT); //Initiates Motor Channel A pin
  pinMode(motorbBreak, OUTPUT);  //Initiates Brake Channel A pin
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

  //setup neuron array
  init_neuron_data();
  Serial.begin(9600);
}

//begin
void loop()
{
  //gather sensory information
  ping();
  //connections betweeen neurons
  synapses();
  //calculate the state of each neuron
  for (int i=0;i<(number_of_neurons);i++)
  {
    neuron(i);
  }
  //fire all active neurons
  fire();
}






//------------------------------------------------------------------------------------

/*Functions
 --------------------------------------------------------------------------------------*/

//function to set each neuron id, set fire status to 0 and gate open status to 0 
void init_neuron_data()
{
  for (int i=0;i<number_of_neurons;i++)
  { 
    mydata.neuron[i].id=i;
    mydata.neuron[i].atp=9999999;
    mydata.neuron[i].state=1;
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
  for (int i=0;i<number_of_neurons;i++)
  {
    mydata.neuron[i].concentration=resting_potential;
  }
}

//ping function

void ping()
{
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

  voltagea=analogRead(voltageaPin) * (5.0 / 1023);

  voltageb=analogRead(voltagebPin) * (5.0 / 1023);

  //convert sensor info to neuron info
  sensory();
}

void sensory()
{
  if (cm2<cm3)
  {
    //front right
    mydata.neuron[7].NAgates=speedexcite;
  }
  if (cm3<cm2)
  {
    //front leftt
    mydata.neuron[6].NAgates=speedexcite;
  }
  if (cm5<cm6)
  {
    //back right
    mydata.neuron[5].NAgates=speedexcite;
  }
  if (cm6<cm5)
  {
    //back left
    mydata.neuron[4].NAgates=speedexcite;
  }
  if (cm1<directionthreshold && cm1<cm4)
  {
    //front center
    mydata.neuron[8].NAgates=directionexcite;
    mydata.neuron[9].kgates=directioninhibit;
  }
  if (cm4<directionthreshold && cm4<cm3)
  {
    //back center
    mydata.neuron[9].NAgates=directionexcite;
    mydata.neuron[8].kgates=directioninhibit;
  }


  if (voltagea<1 || voltageb<1)
  {
    if (DIRECTION==HIGH)
    {
      //if stuck while direction is 0
      mydata.neuron[10].NAgates=epiexcite;
    }
    if (DIRECTION==LOW)
    {
      //if stuck while direction is 1
      mydata.neuron[11].NAgates=epiexcite;
    }
  }
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
  if (DIRECTION==LOW)
  {
    mydata.neuron[6].NAgates=directionmodulator;
    mydata.neuron[7].NAgates=directionmodulator;			
  }	
  //Direction neuron reverse, inhibits sensor neurons in front.
  //This simulates the effect of an indirect antagonistic neuromodulator closing the NA gates on certain neurons 		
  if (DIRECTION==HIGH)
  {
    mydata.neuron[4].NAgates=directionmodulator;
    mydata.neuron[5].NAgates=directionmodulator;			
  }
/*
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
  */
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
  if (mydata.neuron[i].state==1)
  {
    //set new concentration based on number of open gates
    mydata.neuron[i].concentration=mydata.neuron[i].concentration+(mydata.neuron[i].NAgates);
    mydata.neuron[i].concentration=mydata.neuron[i].concentration-(mydata.neuron[i].kgates);
  }
}

void pump(int& i)
{
  if (mydata.neuron[i].atp<1)
  {
    mydata.neuron[i].state=0;
  }
  if (mydata.neuron[i].state==1)
  {
    if (mydata.neuron[i].concentration>resting_potential)
    {	
      mydata.neuron[i].concentration=mydata.neuron[i].concentration-pumprate;
      mydata.neuron[i].atp--;
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

}

void check(int& i)
{ 
  //if current neuron fired set fire status to 1 else set to 0 
  if (mydata.neuron[i].concentration>threshold)
  {
    mydata.neuron[i].fire = 1;	
    mydata.neuron[i].concentration=hyperpolarized;
  }

  else
  {
    mydata.neuron[i].fire = 0;
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
    if(speeda<235) {
      speeda=speeda+20;
    }
  }
  if(mydata.neuron[2].fire==0)
  {
    if(speeda>50) {
      speeda=speeda-10;
    }
  }


  //motorb accumulator	
  //Speed pulse rate interpreter
  if(mydata.neuron[3].fire==1)
  {
    if(speedb<235) {
      speedb=speedb+20;
    }
  }
  if(mydata.neuron[3].fire==0)
  {
    if(speedb>50) {
      speedb=speeda-10;
    }
  }

  Serial.println("speeda:");
  Serial.println(speeda);
  Serial.println("speedb:");
  Serial.println(speedb);

  /*Direction Control
   ------------------------------------------------------------------------------------------*/
  if (mydata.neuron[0].fire==1)
  {
    DIRECTION=LOW;
  }		
  //Direction neuron reverse, inhibits motor neurons in front.
  if (mydata.neuron[1].fire==1)
  {
    DIRECTION=HIGH;
  }
  motorcontrol();
}



//motor control
void motorcontrol()
{
  //Arduino specific, g++ doesn't understand
  digitalWrite(motoraPin, DIRECTION); //Establishes forward direction of Channel A
  digitalWrite(motoraBreak, LOW);   //Disengage the Brake for Channel A
  analogWrite(speedaPin, speeda);   //Spins the motor on Channel A at full speed
  digitalWrite(motorbPin, DIRECTION); //Establishes forward direction of Channel A
  digitalWrite(motorbBreak, LOW);   //Disengage the Brake for Channel A
  analogWrite(speedbPin, speedb);   //Spins the motor on Channel A at full speed 
}















