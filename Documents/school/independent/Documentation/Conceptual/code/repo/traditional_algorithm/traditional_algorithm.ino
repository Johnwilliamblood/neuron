//SPEEDS
const int FAST = 255;
const int SLOW = 150;
//declare sensor pins
  //sensor 1
  const int pingPin1 = 22;
  const int echoPin1 = 23;
  //sensor2
  const int pingPin2 = 24;
  const int echoPin2 = 25;
  //sensor 3
  const int pingPin3 = 26;
  const int echoPin3 = 27;
  //sensor 4
  const int pingPin4 = 28;
  const int echoPin4 = 29;
  //sensor 5
  const int pingPin5 = 30;
  const int echoPin5 = 31;
  //sensor 6
  const int pingPin6 = 32;
  const int echoPin6 = 33;
//store distance read
long cm1, cm2, cm3, cm4, cm5, cm6;
//The direction of both motors and speed of each motor
long DIRECTION, speeda, speedb;
int front, back;
//initialize pins 
void setup() {
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

 

}

//runs this endlessly 
void loop()
{ 
  //read sensors
  ping();
  //interpret data from sensors
  logic();
  //use data from sensors
  motorcontrol();
}

/*
Functions:

-Ping:
The ping function activates the sensors and reads data from them. 
The data from each sensor is converted to cm and stored in a 
different variable for each sensor.  

MicrosecondsTocm:
The microsecondsTocm function takes the duration it took the 
sound waves to return and converts it to cm to make it easier
to understand the data I am working with

Motorcontrol:
The motorcontrol function sends information to the motorsheild 
pins.

Logic:
The logic function interprets the information stored in the cm1234
variables and stores meaningful information to be used int the 
Motorcontrol function. 

*/

//ping function
long ping()
{
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
  Serial.print(cm2);

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
  
  Serial.print("cm1");
  Serial.print(cm1);
  Serial.print("cm2");
  Serial.print(cm2);
  Serial.print("cm3");
  Serial.print(cm3);
  Serial.print("cm4");
  Serial.print(cm4);
  Serial.print("cm5");
  Serial.print(cm5);
  Serial.print("cm6");
  Serial.print(cm6);
}


//converts ping duration to cm
  
  long microsecondsTocm(long microseconds)
  {
     return microseconds / 29 / 2; 
  }
  
  
//motor control
  void motorcontrol()
  {
    digitalWrite(12, DIRECTION); //Establishes forward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, speeda);   //Spins the motor on Channel A at full speed

    digitalWrite(13, DIRECTION); //Establishes forward direction of Channel A
    digitalWrite(8, LOW);   //Disengage the Brake for Channel A
    analogWrite(11, speedb);   //Spins the motor on Channel A at full speed 
  }
  
  //set values to send to motorcontrol function 
void logic()
{
  /*
    Direction Shifting:
    The difference in distance between switching from forward to reverse (30) and 
    switching from reverse to forward (50) results in the robot having a tendancy 
    to go forward.
  */
  front = cm1+cm2+cm3;
  back = cm4+cm5+cm6;
  //if it is going forward and gets close to something infront of it, switch to reverse
  if (DIRECTION==LOW && cm1 > cm4 && cm4<30) 
  {
      DIRECTION=HIGH;
      
  
  }
  //if it is in reverse and something is moderatly close switch to forward 
  if (DIRECTION==HIGH && cm4 > cm1 && cm1<30)
  {
    DIRECTION=LOW;
  }
  
  /*
  Speed Control: 
  The speeds between the two wheels will always be different resulting in the robot having
  a wavy motion as it moves thus "looking around". The difference in speeds also results 
  in the robot having a tendancy to move towards whichever side has the greatest amount of distance 
  thus moving away from walls and other objects. When in reverse the wheel speed difference is also
  reversed.  
  */
  
  if (DIRECTION ==LOW)
  {
    if (cm5 > cm6)
    {
      speeda=FAST;
      speedb=SLOW;
    }
    if (cm6 > cm5)
    {
      speeda=SLOW;
      speedb=FAST;
    }

  }
  if (DIRECTION ==HIGH)
  {
    if (cm2 > cm3)
    {
      speeda=FAST;
      speedb=SLOW;
    }
    if (cm3 > cm2)
    {
      speeda=SLOW;
      speedb=FAST;  
    }
  }
}
  
  
  
