// Pin definitions

// pins for motor 1 (Back_RIGHT)
#define Back_RPWM_1 3 // define pin 3 for RPWM pin (output)
#define Back_R_EN_1 34 // define pin 2 for R_EN pin (input)
#define Back_R_IS_1 35 // define pin 5 for R_IS pin (output)

#define Back_LPWM_1 4 // define pin 6 for LPWM pin (output)
#define Back_L_EN_1 36 // define pin 7 for L_EN pin (input)
#define Back_L_IS_1 37 // define pin 8 for L_IS pin (output)
// motor 1 pins end here

// pins for motor 2( Back_LEFT)
#define Back_RPWM_2 5 // define pin 9 for RPWM pin (output)
#define Back_R_EN_2 38 // define pin 10 for R_EN pin (input)
#define Back_R_IS_2 39 // define pin 12 for R_IS pin (output)

#define Back_LPWM_2 6 // define pin 11 for LPWM pin (output)
#define Back_L_EN_2 40 // define pin 7 for L_EN pin (input)
#define Back_L_IS_2 41 // define pin 8 for L_IS pin (output)

// pins for motor 1 (Front_RIGHT)
#define Front_RPWM_1 7 // define pin 3 for RPWM pin (output)
#define Front_R_EN_1 28 // define pin 2 for R_EN pin (input)
#define Front_R_IS_1 29 // define pin 5 for R_IS pin (output)

#define Front_LPWM_1 8 // define pin 6 for LPWM pin (output)
#define Front_L_EN_1 30 // define pin 7 for L_EN pin (input)
#define Front_L_IS_1 31 // define pin 8 for L_IS pin (output)
// motor 1 pins end here

// pins for motor 2( Front_LEFT)
#define Front_RPWM_2 9 // define pin 9 for RPWM pin (output)
#define Front_R_EN_2 50 // define pin 10 for R_EN pin (input)
#define Front_R_IS_2 51 // define pin 12 for R_IS pin (output)

#define Front_LPWM_2 10 // define pin 11 for LPWM pin (output)
#define Front_L_EN_2 52 // define pin 7 for L_EN pin (input)
#define Front_L_IS_2 53 // define pin 8 for L_IS pin (output)
//pins for ultra sonic wave sensor


//front left
#define trigPin2 22
#define echoPin2 23

//front
#define trigPin3 24
#define echoPin3 25

//front right
#define trigPin4 26
#define echoPin4 27


#define CW 1 //
#define CCW 0 //
#define debug 1 //

#include <BTS7960.h>
BTS7960 Front_motor_RIGHT(Front_R_EN_1, Front_RPWM_1, Front_R_IS_1, Front_L_EN_1, Front_LPWM_1, Front_L_IS_1, debug);//define motor 1 object
BTS7960 Front_motor_LEFT (Front_R_EN_2, Front_RPWM_2, Front_R_IS_2, Front_L_EN_2, Front_LPWM_2, Front_L_IS_2, debug);//define motor 2 object and the same way for other motors

BTS7960 Back_motor_RIGHT(Back_R_EN_1, Back_RPWM_1, Back_R_IS_1, Back_L_EN_1, Back_LPWM_1, Back_L_IS_1, debug);//define motor 1 object
BTS7960 Back_motor_LEFT (Back_R_EN_2, Back_RPWM_2, Back_R_IS_2, Back_L_EN_2, Back_LPWM_2, Back_L_IS_2, debug);//define motor 2 object and the same way for other motors

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
  Front_motor_RIGHT.begin();
  Front_motor_LEFT.begin();
  Back_motor_RIGHT.begin();
  Back_motor_LEFT.begin();      
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
  if (distance_Front < 200) {
    // Stop the cart
    Front_motor_LEFT.rotate(0,CCW);// run motor at 3% speed in CCW direction
    Front_motor_RIGHT.rotate(0,CCW);// run motor at 3% speed in CCW direction
    Back_motor_LEFT.rotate(50,CCW);// run motor at 3% speed in CCW direction
    Back_motor_RIGHT.rotate(50,CCW);// run motor at 3% speed in CCW direction
    delay(2000);
    Front_motor_LEFT.stop();
    Front_motor_RIGHT.stop();
    Back_motor_LEFT.stop();
    Back_motor_RIGHT.stop();
    // MOVING BACKWARD
    delay(2000);
    Front_motor_LEFT.rotate(50,CCW);// run motor at 3% speed in CCW direction
    Front_motor_RIGHT.rotate(50,CCW);// run motor at 3% speed in CCW direction
    Back_motor_LEFT.rotate(50,CCW);// run motor at 3% speed in CCW direction
    Back_motor_RIGHT.rotate(50,CCW);// run motor at 3% speed in CCW direction
    delay(2000);
    Front_motor_LEFT.stop();
    Front_motor_RIGHT.stop();
    Back_motor_LEFT.stop();
    Back_motor_RIGHT.stop();
    delay(2000);
   //TURN LEFT
    Front_motor_LEFT.rotate (0,CW);// run motor at 3% speed in CW direction
    Front_motor_RIGHT.rotate(100,CW);// run motor at 3% speed in CW direction
    Back_motor_LEFT.rotate  (80,CCW);// run motor at 3% speed in CW direction
    Back_motor_RIGHT.rotate (100,CW);// run motor at 3% speed in CW direction
    delay(3000);//run for 3 seconds
    
  }else{
    // No obstacle detected, continue moving forward
    Serial.println("FORWARD_FORWARD_FORWARD_FORWARD_FORWARD_FORWARD_FORWARD_");
    Front_motor_LEFT.rotate(0,CW);// run motor at 3% speed in CW direction
    Front_motor_RIGHT.rotate(0,CW);// run motor at 3% speed in CW direction
    Back_motor_LEFT.rotate(40,CW);// run motor at 3% speed in CW direction
    Back_motor_RIGHT.rotate(40,CW);// run motor at 3% speed in CW direction
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
