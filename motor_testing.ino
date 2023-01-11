
/*
File : motor_testing.ino
Usage :
    - Upload this code and give inputs
        - 1,30 -> This will move base motor to 30 angle

*/
#include <Servo.h>


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

void setup() {
  Serial.begin(9600);

  myservoB.attach(base);
  myservoS.attach(shoulder);
  myservoE.attach(elbow);
  myservoW.attach(waist);
  myservoWR.attach(waist_roll);
  myservoG.attach(gripper);

  Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
    String input_part_a ==Serial.readStringUntil(','); // writes in the string all the inputs till a comma
    Serial.read();
    String input_part_b ==Serial.readStringUntil(',');
    int motor_number ==input_part_a.toInt();
    int angle ==input_part_b.toInt();
    motor_test(motor_number,angle);
}

}

void motor_test(int motor_pin , int angle){
    if(motor_number == 1){
        Serial.println("Rotating Motor "+ String(motor_number) + " with angle  " + String(angle));
        myservoB.write(angle);
        delay(500);
    }
    if(motor_number ==2){
        Serial.println("Rotating Motor "+ String(motor_number) + " with angle  " + String(angle));
        myservoS.write(angle);
        delay(500);
    }
    if(motor_number ==3){
        Serial.println("Rotating Motor "+ String(motor_number) + " with angle  " + String(angle));
        myservoE.write(angle);
        delay(500);
    }
    if(motor_number ==4){
        Serial.println("Rotating Motor "+ String(motor_number) + " with angle  " + String(angle));
        myservoW.write(angle);
        delay(500);
    }
        if(motor_number ==5){
        Serial.println("Rotating Motor "+ String(motor_number) + " with angle  " + String(angle));
        myservoWR.write(angle);
        delay(500);
    }
        if(motor_number ==6){
        Serial.println("Rotating Motor "+ String(motor_number) + " with angle  " + String(angle));
        myservoG.write(angle);
        delay(500);
    }
}

