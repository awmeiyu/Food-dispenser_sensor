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

String mode="auto"; 
int buttonServo; 

int buttonState = 0; 

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

long cooldownStartTime=0;
bool isActive=true;

void setup() {
  myservo.attach(8);  // attaches the servo on pin 8 to the servo object
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication


//MODE
    pinMode(2,INPUT_PULLUP); //btnAuto
    pinMode(3,INPUT_PULLUP); //btnManual
    pinMode(4,INPUT_PULLUP); //btnDebug

//device buttons setup here
    pinMode(A1,INPUT_PULLUP); // servo

//LED setup here
    pinMode(5,OUTPUT); //AUTO
    pinMode(6,OUTPUT); //MANUAL
    pinMode(7,OUTPUT); //DEBUG

  digitalWrite(5,HIGH);

}
void loop() {
int button_auto=digitalRead(2);
int button_manual=digitalRead(3);
int button_debug=digitalRead(4);

int button_servo = digitalRead(A1);

if (button_auto==LOW){
  mode="auto";
  //handle led
    Serial.println("enters A");
        killAllLights();
        //setManualLight on
        digitalWrite(5,HIGH);
        isActive=true;
  }

if(button_manual==LOW){
    mode="manual";
    //led
Serial.println("enters M");
        killAllLights();
        //setManualLight on
        digitalWrite(6,HIGH);
        isActive=true;
    }

 if(button_debug==LOW){
      mode="debug";
      Serial.println("enters D");
        killAllLights();
        //setManualLight on
        digitalWrite(7 ,HIGH);
        isActive=true;
      }

//    // put your main code here, to run repeatedly:
 if(mode.equals("auto")){

  if(isActive){
        // here is where you'd put code that needs to be running all the time.
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
      
            //hits the cooldown for the functionalities
            cooldownStartTime=millis();
            isActive=false;
          }
          //delay(1000);
       }

     else {
      digitalWrite(trigPin,LOW);
      myservo.write(90);
    }

  }
    //cooldown check
    if((millis()-cooldownStartTime)>60000 && isActive==false){
      Serial.println("cooldownReset");
      isActive=true;
    }


}

//END AUTO
//
if(mode.equals("manual")){ 
    // here is where you'd put code that needs to be running all the time.
    if(button_servo==LOW){
    
      Serial.println("manual called");
    myservo.write(107);              // tell servo to go to position in variable 'pos'
    delay(500);                       // waits 500ms for the servo to reach the position
    myservo.write(90);              // 90 makes it stop, 180 makes it move clockwise, -180 makes it move anti-clockwise

    //delay(900000);
    //delay(1000);
    }
    delay(1000);
}

//
 if(mode.equals("debug")){

//

    if(button_servo==LOW){
    myservo.write(180);              // tell servo to go to position in variable 'pos'
    delay(500);                       // waits 500ms for the servo to reach the position
    myservo.write(90); 
      }
 }
}
//END LOOP

void killAllLights(){
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);

    }

