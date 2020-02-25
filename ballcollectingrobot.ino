#include <AFMotor.h>
#include <Servo.h> 
// Check the motor driver datasheet for motor pin connections
AF_DCMotor rm(1, MOTOR12_64KHZ);  // Right motor
AF_DCMotor lm(4, MOTOR34_64KHZ);  // Left motor
Servo grServo; // Servo motor for gripper
byte incomingByte ;

void setup() 
{ 
   Serial.begin(9600);
  // Set motors speed
   rm.setSpeed(200);  
   lm.setSpeed(200);
   rm.run(RELEASE);
   lm.run(RELEASE);
	grServo.attach(10); // Attach gripper
} 
void loop()
{
   if (Serial.available() > 0) {
    incomingByte = Serial.read(); // Read the input character from bluetooth serial input buffer
  
    if (incomingByte == 'A') 
    {
         grServo.write(120);      // Gripper Open Position
    }
    else if (incomingByte =='B') 
    {
        grServo.write(180);      // Gripper Close Position
    }
    else if (incomingByte == 'C') 
    {
        rm.run(FORWARD);        // Run both motors in forward direction
        lm.run(FORWARD);
    }
    else if (incomingByte == 'D') 
    {
        rm.run(BACKWARD);       // Run both motors in backward direction
        lm.run(BACKWARD);
    }
    else if (incomingByte == 'E') 
    {
        rm.run(BACKWARD);       // Turning Left. Run right motor in backward direction and left motor in forward direction
        lm.run(FORWARD);
    }
    else if (incomingByte == 'G') 
    {
        rm.run(FORWARD);        // Turning Right. Run right motor in forward direction and left motor in backward direction
        lm.run(BACKWARD);
    }
    else if (incomingByte == 'F') 
    {
        rm.run(RELEASE);        // Stop both motors
        lm.run(RELEASE);
    }
   }
   delay(20);
}

