#include <Servo.h>

// Ultra Sonic Sensor
#define echoPin 9
#define trigPin 10
long duration;
int distance;
int prev_distance = -1; // Initialize previous distance to an impossible value

int led = 13;

// Servos
const int base = 2;
const int shoulder = 13;
const int elbow = 4;
const int waist = 5;
const int waist_roll = 6;
const int gripper = 7;

Servo myservoB;
Servo myservoS;
Servo myservoE;
Servo myservoW;
Servo myservoWR;
Servo myservoG;

unsigned long previousMillis = 0;
const long interval = 300;


void setArm(int b, int s, int e, int w, int wr, int g) {
  myservoS.write(s);
  delay(1000);
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

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(1000);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  myservoB.attach(base);
  myservoS.attach(shoulder);
  myservoE.attach(elbow);
  myservoW.attach(waist);
  myservoWR.attach(waist_roll);
  myservoG.attach(gripper);

//  /Serial.println("Initial Setup ");
  setArm(0, 90, 180, 0, 50, 0);
// / Serial.
}
void read_distance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
//Serial.println(distance);
  if (distance < 17 && distance > 7) {
      Serial.println("1"); }// Obstacle detected
  else if (distance > 17 ) {
        Serial.println("0"); // No obstacle detected
  }
}
void loop() {
    unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    read_distance();
  }
  if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');
//        Serial.println(data);/
        if (data == "1") {
          Serial.println("2");
          setArm(0, 45, 180, 30, 50, 30);
          delay(3000);
          setArm(0, 75, 110, 180, 50, 0);
          delay(3000);
          setArm(0, 90, 180, 0, 50, 0);
          delay(3000);
          Serial.println("3");
        }
      }




  }
