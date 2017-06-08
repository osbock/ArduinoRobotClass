#include <NewPing.h>
#include <DRV8835MotorShield.h>  //Pololu DRV8835 Dual Motor Driver Shield Library
#define TRIGGER_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.



//Create DRV8853 Motor Shield object
DRV8835MotorShield motors;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup()
{
  // uncomment one or both of the following lines if your motors' directions need to be flipped
  motors.flipM1(true);
  motors.flipM2(true);
  Serial.begin(115200);
  delay(2000);
}

void loop()
{
  delay(50);
  unsigned int uS = sonar.ping();
  unsigned int cmDistance = uS/US_ROUNDTRIP_CM;

  if (cmDistance <50 && cmDistance >0){
    turnAndReverse(100);
  }
  else
    straight(100);
  
}
void straight(int speed){
  motors.setM1Speed( speed );
  motors.setM2Speed( speed );
}
void turnAndReverse(int speed){
  motors.setM1Speed( -speed );
  motors.setM2Speed( -speed );
  delay(1000);
  motors.setM1Speed( speed );
  motors.setM2Speed( -speed );
  delay(750);
  motors.setM1Speed(0);
  motors.setM2Speed(1);
}

