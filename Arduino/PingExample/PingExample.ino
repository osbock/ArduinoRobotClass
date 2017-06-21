#include <NewPing.h>
#include <DRV8835MotorShield.h>  //Pololu DRV8835 Dual Motor Driver Shield Library
#define TRIGGER_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup()
{

  Serial.begin(115200);
  delay(2000);
}

void loop()
{
  delay(50);
  unsigned int uS = sonar.ping();
  unsigned int cmDistance = uS/US_ROUNDTRIP_CM;
  Serial.println(cmDistance);
  delay(200);
}
