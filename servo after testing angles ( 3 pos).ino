#include <Servo.h>

//ULTRA SONIC SENSOR
#define echoPin 9 
#define trigPin 10 
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


//SERVOS
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

//void setArm(int b, int s, int e, int w, int wr , int g);

void setArm(int b, int s, int e, int w, int wr , int g) {
  
  myservoS.write(s);
  delay(500);
  myservoW.write(w);
  delay(500);
  myservoWR.write(wr);
  delay(500);
  myservoS.write(s);
  delay(500);
  myservoE.write(e);
  delay(500);
  myservoB.write(b);
  delay(500);
  delay(1000);

  myservoG.write(g);
  delay(500);
}

void setup() {
  Serial.begin(9600);
  //ultrasonic sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  //servos
  myservoB.attach(base);
  myservoS.attach(shoulder);
  myservoE.attach(elbow);
  myservoW.attach(waist);
  myservoWR.attach(waist_roll);
  myservoG.attach(gripper);

  Serial.begin(9600);
  Serial.println("ill start in 3 sec");
  //setArm(0 ,0 , 0 , 0, 0 , 0);

  delay(3000);
  setArm(0,90 , 180 , 0, 50 , 0);
 
 /*
  delay(3000);
  setArm(0, 45 , 180 , 30, 50 , 30);
   
  delay(3000);
  setArm(0, 75 , 110 , 180, 50 , 0);
  delay(3000);

  setArm(0,90 , 180 , 0, 50 , 0);
 
  delay(3000);
  setArm(0, 45 , 180 , 30, 50 , 30);
   
  delay(3000);
  setArm(0, 75 , 110 , 180, 50 , 0);
  delay(3000);

 setArm(0,90 , 180 , 0, 50 , 0);
 
  delay(3000);
  setArm(0, 45 , 180 , 30, 50 , 30);
   
  delay(3000);
  setArm(0, 75 , 110 , 180, 50 , 0);
  */
}

void loop() {
  //ULTRASONIC SENSOR
  // put your main code here, to run repeatedly:
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
  Serial.print("distance = ");
  Serial.println(distance );

  delay(3000);

  if (distance < 16 && distance >7){
    delay(3000);
    setArm(0, 45 , 180 , 30, 50 , 30);
   
    delay(3000);
    setArm(0, 75 , 110 , 180, 50 , 0);
    delay(3000);
    setArm(0,90 , 180 , 0, 50 , 0);
  }

    if (distance > 17){
    delay(3000);

    setArm(0,90 , 180 , 0, 50 , 0);
  }
}
  

