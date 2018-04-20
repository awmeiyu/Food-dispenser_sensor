/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;
int maximumRange = 3000; // Maximum range needed
int minimumRange = 0; // Minimum range needed

int maxCount=2;
int count=0;

void setup() {
  myservo.attach(8);  // attaches the servo on pin 8 to the servo object
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
    // Clears the trigPin
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
   duration = pulseIn(echoPin, HIGH);

// Calculating the distance
   distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
   Serial.print("Distance: ");
   Serial.println(distance);

//distance is measured in cm, delay in milliseconds
//delay 900000ms, 15 minutes, after triggering sensor twice
//1000ms delay, 1 second, after sensing every one time
if (distance <= 100) {
    digitalWrite(trigPin, HIGH);
    count++;
    if(count==maxCount){
    Serial.println("dispense");
     // in steps of 1 degree
    myservo.write(107);              // tell servo to go to position in variable 'pos'
    delay(500);                       // waits 500ms for the servo to reach the position
    myservo.write(90);              // 90 makes it stop, 180 makes it move clockwise, -180 makes it move anti-clockwise
    count=0;
    delay(5000);
    
    }
    delay(1000);
      }


   else {
    digitalWrite(trigPin,LOW);
    myservo.write(90);
  }
}

