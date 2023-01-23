#include <Servo.h>
//ULTRA SONIC SENSOR
#define echoPin 9 
#define trigPin 10 
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement



int led = 13;


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

  // if distance < 10 then send msg to python 
  //and start detecting
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  delay(1000);
  pinMode(led, OUTPUT); 
  digitalWrite(led, LOW);  
    //servos
  myservoB.attach(base);
  myservoS.attach(shoulder);
  myservoE.attach(elbow);
  myservoW.attach(waist);
  myservoWR.attach(waist_roll);
  myservoG.attach(gripper);

  delay(3000);
  setArm(0,90 , 180 , 0, 50 , 0);

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
  //Serial.println(distance);
  if (distance < 16 && distance >7){
     Serial.println("1");
    // Serial.println(distance);

     if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');
        //Serial.print(data);
        if (data = 1) {
          delay(3000);
          setArm(0, 45 , 180 , 30, 50 , 30);
   
          delay(3000);
          setArm(0, 75 , 110 , 180, 50 , 0);
          delay(3000);
          setArm(0,90 , 180 , 0, 50 , 0);
          delay(3000);
        }
        
        if (data = 2) {
          setArm(0,90 , 180 , 0, 50 , 0);
          delay(3000);
        }
    
     }
     }
  if (distance > 16){
    Serial.println( "0");
   // Serial.println(distance);
    
  }
   
}
