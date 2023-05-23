#include <Servo.h>
#include "DHT.h"
#define DHTPIN 6         // what pin we're connected to
#define DHTTYPE DHT11    // DHT 11 
DHT dht(DHTPIN, DHTTYPE);
#define out_FAN 13      // Pin connected to the fan

// Pins for sensors and LED
int Sensor1_gate_Pin = 2;
int Sensor2_gate_Pin = 3;
int Sensor1_off_Pin = 4;
int Sensor2_off_Pin = 5;
int LED_Pin = 7;

Servo myservo;
int gate_outside = HIGH;
int gate_inside = HIGH;
int office1_state ;
int office2_state ;
int pos = 0;            // servo position in degrees
int Sensor_count=0;
int gate_state =0;      //0 is closed, 1 is open from first sensor, 2 is open from second sensor
char message[5];        //array of characters used in sending the data to the nodemcu
char A,B,C;

void setup() {
  // Sensor pins as input
  pinMode(Sensor1_gate_Pin, INPUT);
  pinMode(Sensor2_gate_Pin, INPUT);
  pinMode(Sensor1_off_Pin, INPUT);
  pinMode(Sensor2_off_Pin, INPUT);
  // LED pin as output
  pinMode(LED_Pin, OUTPUT);
  // Pin connected to the fan
  pinMode(out_FAN,OUTPUT);
  Serial.begin(9600);
  digitalWrite(LED_Pin,HIGH);   //the led is initially off(active low)  
  myservo.attach(11);
  myservo.write(pos);           // Set servo position to 0 degrees
  digitalWrite(out_FAN,HIGH);   //the fan is initially off(active low)
  dht.begin();
}

void loop() {
  //store the sensors readings in variables 
  gate_outside = digitalRead(Sensor1_gate_Pin);
  gate_inside = digitalRead(Sensor2_gate_Pin);
  office1_state = digitalRead(Sensor1_off_Pin);
  office2_state = digitalRead(Sensor2_off_Pin);
  float cel = dht.readTemperature();
  
  if(cel>=26){                  // If temperature is equal to or above 26 degrees Celsius
   digitalWrite(out_FAN,LOW);   // Turn off the fan
  }else if(cel<=23){            // If temperature is equal to or below 23 degrees Celsius
    digitalWrite(out_FAN,HIGH); // Turn on the fan
  }

  if ((gate_outside == LOW)&&(gate_state==0)){   //If the sensor outside the room is triggered and the gate is closed
           gate_state=1;                         // Set gate state to open from first sensor
           Sensor_count++;
           // Open the gate by incrementing servo position
           for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 90 degrees
            // in steps of 1 degree
            myservo.write(pos);                 // tell servo to go to position in variable 'pos'
            delay(15);                          // waits 15 ms for the servo to reach the position
        
           } 
  }
   else if((gate_inside == LOW) && (gate_state == 0)&&(Sensor_count != 0)){ //If the sensor inside the room is triggered and the gate is closed
           gate_state = 2;                                                  // Set gate state to open from second sensor
           Sensor_count--;
           if(Sensor_count <0){
            Sensor_count = 0;
           }
           // Open the gate by incrementing servo position
           for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 90 degrees
            // in steps of 1 degree
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15 ms for the servo to reach the position
          } 
     } 

 if((gate_outside == LOW) && (gate_state == 2)){ //If the sensor outside the room is triggered and the gate is opened from second sensor
    gate_state = 0;                              // Set gate state to closed
    // Close the gate by decrementing servo position
    for (pos = 90; pos >= 0; pos -= 1) {         // goes from 90 degrees to 0 degrees
        myservo.write(pos);                      // tell servo to go to position in variable 'pos'
        delay(15);                               // waits 15 ms for the servo to reach the position
    }
  }
  if((gate_inside == LOW) && (gate_state == 1)){     //If the sensor inside the room is triggered and the gate is opened from first sensor
    gate_state=0;                                   // Set gate state to closed
    // Close the gate by decrementing servo position
    for (pos = 90; pos >= 0; pos -= 1) {              // goes from 90 degrees to 0 degrees
        myservo.write(pos);                              // tell servo to go to position in variable 'pos'
        delay(15);                                      // waits 15 ms for the servo to reach the position
    }               
  }


  if ( Sensor_count > 0){           // Turn on the LED if Sensor_count is greater than 0
    digitalWrite(LED_Pin,LOW);
  }else{
    digitalWrite(LED_Pin,HIGH);    // Turn off the LED if Sensor_count is 0
  }

  if(cel<=23)
  {
    C='Z';
  }
  if(cel==24)
  {
    C='z';
  }
  if(cel==25)
  {
    C='X';
  }
  if(cel>=26)
  {
    C='X';
  }
  if(office1_state==1)
  {
    A='A';
  }
  else if(office1_state==0)
  {
    A='a';
  }
  if(office2_state==1)
  {
    B='B';
  }
  else if(office2_state==0)
  {
    B='b';
  }
  
  String X =String(C)+String(Sensor_count)+String(A)+String(B);
  X.toCharArray(message,5);

  Serial.write(message);      // Send the message via serial communication

  delay(500);                 // Delay for 500 milliseconds
}
