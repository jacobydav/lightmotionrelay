/*
This code tests a motion and light activated sensor.
When it is bright and there is motion activated we will turn on a green led.
Otherwise the system will be inactive and a red led will be turned on.
Motion sensor is a PIR sensor that has a digital output that goes high when motion is detected.
The photosensor is connected in the following way:
5V (arduino) -> variable resistor -> photo resistor -> gnd
An analog input on the arduino is connected between the 2 resistors.
*/

byte photoSensorPin = 0;  //Analog 0
byte motionSensorPin = 8;  //Digital 8
byte greenLedPin = 7;      //output to turn on green led
byte redLedPin = 6;      //output to turn on red led

int photoThresh = 500;    //We consider it dark enough if val > photoThresh

int prevMotionVal = 0;    //Keep track of the last value

void setup() 
{
  pinMode(motionSensorPin, INPUT);      // Make digital pin an input
  pinMode(greenLedPin, OUTPUT);      // Make digital pin an output
  pinMode(redLedPin, OUTPUT);      // Make digital pin an output
  
  Serial.begin(9600);
}

void loop() 
{
  //Check if motion was detected
  int motionVal = digitalRead(motionSensorPin);
  
  //Check the light level
  int photoVal = analogRead(photoSensorPin);
  
  //print the result
  Serial.print("Motion: ");
  Serial.print(motionVal);
  Serial.print("   Photo: ");
  Serial.println(photoVal);
    
  if(photoVal>photoThresh && motionVal==HIGH)
  {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
  }
  else
  {
    //There must be 2 non-motion readings before we turn off LEDs
    //This will smooth out the readings
    if(prevMotionVal==LOW)
    {
      digitalWrite(greenLedPin, LOW);
      digitalWrite(redLedPin, HIGH);
    }
  }
  
  prevMotionVal = motionVal;
    
  delay(50);
}
