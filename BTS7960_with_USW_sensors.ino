// Pin definitions

// pins for motor 1 (RIGHT)
#define RPWM_1 3 // define pin 3 for RPWM pin (output)
#define R_EN_1 4 // define pin 2 for R_EN pin (input)
#define R_IS_1 5 // define pin 5 for R_IS pin (output)

#define LPWM_1 6 // define pin 6 for LPWM pin (output)
#define L_EN_1 7 // define pin 7 for L_EN pin (input)
#define L_IS_1 8 // define pin 8 for L_IS pin (output)
// motor 1 pins end here

// pins for motor 2( LEFT)
#define RPWM_2 9 // define pin 9 for RPWM pin (output)
#define R_EN_2 10 // define pin 10 for R_EN pin (input)
#define R_IS_2 12 // define pin 12 for R_IS pin (output)

#define LPWM_2 11 // define pin 11 for LPWM pin (output)
#define L_EN_2 A0 // define pin 7 for L_EN pin (input)
#define L_IS_2 A1 // define pin 8 for L_IS pin (output)

//pins for ultra sonic wave sensor

//left
#define trigPin1 22
#define echoPin1 23

//front left
#define trigPin2 24
#define echoPin2 25

//front
#define trigPin3 26
#define echoPin3 27

//front right
#define trigPin4 28
#define echoPin4 29

//right
#define trigPin5 30
#define echoPin5 31

#define CW 1 //
#define CCW 0 //
#define debug 1 //

#include <BTS7960.h>
BTS7960 motor_RIGHT(R_EN_1,RPWM_1,R_IS_1, L_EN_1,LPWM_1,L_IS_1,debug);//define motor 1 object
BTS7960 motor_LEFT(R_EN_2,RPWM_2,R_IS_2, L_EN_2,LPWM_2,L_IS_2,debug);//define motor 2 object and the same way for other motors


// Variables for distance measurement
long duration1, distance_Left;
long duration2, distance_F_Left;
long duration3, distance_Front;
long duration4, distance_F_Right;
long duration5, distance_Right;

// Variable for direction
int direction = 0;

void setup() {

  //Set motors    
  motor_RIGHT.begin();
  motor_LEFT.begin();   
  // Set pin modes


  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);

  pinMode(trigPin5, OUTPUT);
  pinMode(echoPin5, INPUT);

  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Measure distance in all directions
  distance_Left = measureDistance(trigPin1, echoPin1);
  Serial.println("distance_Left");
  Serial.println(distance_Left);
  distance_F_Left = measureDistance(trigPin2, echoPin2);
  Serial.println("distance_Front_Left");
  Serial.println(distance_F_Left);
  distance_Front = measureDistance(trigPin3, echoPin3);
  Serial.println("distance_Front");
  Serial.println(distance_Front);
  distance_F_Right = measureDistance(trigPin4, echoPin4);
  Serial.println("distance_Front_Right");
  Serial.println(distance_F_Right);
  distance_Right = measureDistance(trigPin5, echoPin5);
  Serial.println("distance_Right");
  Serial.println(distance_Right);

// Check if there is an obstacle in front
  if (distance_Front < 20) {
    // Stop the cart
    motor_LEFT.stop();
    motor_RIGHT.stop();
    delay(2000);
     Serial.println("BACK_BACK_BACK_BACK_BACK_BACK_BACK_BACK_");
    motor_LEFT.rotate(3,CCW);// run motor at 3% speed in CCW direction
    motor_RIGHT.rotate(3,CCW);// run motor at 3% speed in CCW direction
    delay(2000);
    motor_LEFT.stop();
    motor_RIGHT.stop();
    delay(2000);
      // Decide the direction to turn
      //If the obstale is closer to front right sensor, it turns left
      if (distance_F_Left > distance_F_Right) {
        Serial.println("LEFT_LEFT_LEFT_LEFT_LEFT_LEFT_LEFT_LEFT_");
        motor_LEFT.rotate(3,CCW);// run motor at 3% speed in CCW direction
        motor_RIGHT.rotate(5,CW);// run motor at 5% speed in CW direction
        delay(500);
      }else{
        Serial.println("RIGHT_RIGHT_RIGHT_RIGHT_RIGHT_RIGHT_RIGHT_RIGHT_");
        motor_LEFT.rotate(5,CW);// run motor at 5% speed in CW direction
        motor_RIGHT.rotate(3,CCW);// run motor at 3% speed in CCW direction
        delay(500);
      } 
  }else{
    // No obstacle detected, continue moving forward
    Serial.println("FORWARD_FORWARD_FORWARD_FORWARD_FORWARD_FORWARD_FORWARD_");
    motor_LEFT.rotate(3,CW);// run motor at 3% speed in CW direction
    motor_RIGHT.rotate(3,CW);// run motor at 3% speed in CW direction
  }
}
// Measure distance using a ultrasonic sensor connected to the specified pins
long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration/2) / 29.1;
  return distance;
}
