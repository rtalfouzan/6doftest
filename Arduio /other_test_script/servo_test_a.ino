

#include <Servo.h>
//#define echoPin 9 // attach pin D2 Arduino to pin Echo of HC-SR04
//#define trigPin 10 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
////long duration; // variable for the duration of sound wave travel
//int distance; // variable for the distance measurement

const int base=2;
const int shoulder=3;
const int elbow=4;
const int waist=5;
const int waist_roll=6;
const int gripper=7;


Servo myservoB; 
Servo myservoS;
Servo myservoE;
Servo myservoW;
Servo myservoWR;
Servo myservoG;




// twelve servo objects can be created on most boards

void setup() {
  myservoB.attach(base);
  myservoS.attach(shoulder);//makes lots of sounds
  myservoE.attach(elbow);
  myservoW.attach(waist);
  myservoWR.attach(waist_roll);
  myservoG.attach(gripper);
  Serial.begin(9600);
  myservoG.write(40);
  /*
  myservoWR.write(50);
   delay(500);
  myservoW.write(0);
     delay(500);
  myservoE.write(180);
     delay(500);
  myservoS.write(100);
   delay(500);
   */
  myservoB.write(20);
  //myservoS.write(80);
 
  
  /*
  delay(5000);
  
  myservoG.write(120);
  delay(1000);

  myservoWR.write(40);
  delay(1000);

  myservoW.write(180);
  delay(1000);

  myservoE.write(130); // almost up \/
  delay(1000);

  myservoS.write(0); // up|
  delay(1000);

  myservoB.write(100);//middle 100
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
   // // Serial Communication is starting with 9600 of baudrate speed

    myservoE.write(80); // almost up \/
  delay(1000);
  */
}

void loop() {
  /*
// Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  if (distance < 12 && distance >7){
  //  myservoG.write(30);
    Serial.print("Distance: ");
    Serial.println(distance);

  }
  if (distance < 15 ){
    myservoG.write(120);
    myservoE.write(80); // almost up \/
    Serial.print("Distance: ");
    Serial.println(distance);

  }
    if (distance < 7 ){
    
    Serial.print("Distance2: ");
    Serial.println(distance);

  }
  */
}


/*


Notes
base :
0 right
100 middle 
180 left

shoulder
0 up |
90 straigh --- 
130 almost down ( not good in use)


ELBOW:( not stronng enough)
160 up|
70 ( left 90 degree)



waist :
0 up
180 down

waist_roll:
40 upside down( servo up)
140 side ways
regualr side could not be achived


Gripper :
120 closed 
30 opened


setup values :
  myservoG.write(30);
  delay(1000);

  myservoWR.write(50);
  delay(1000);

  myservoW.write(150);
  delay(1000);

  myservoE.write(140); // almost up \/
  delay(1000);

  myservoS.write(0); // up|
  delay(1000);

  myservoB.write(100);//middle 100
  

*/