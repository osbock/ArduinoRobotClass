#include <DRV8835MotorShield.h>  //Pololu DRV8835 Dual Motor Driver Shield Library
#include <QTRSensors.h>         //Pololu QTR-1RC Reflectance Sensor Library

//***********DEFINE PARAMETERS*************************
#define LeftSensePin    2    //Left Line Sensor Pin
#define RightSensePin   3    //Right Line Sensor Pin 
#define MaxMotorSpeed 400  //Maximum speed value to send to motors
int MaxDesiredSpeed = MaxMotorSpeed*0.25;
#define MinSpeed 15
int leftSpeed = 0;
int rightSpeed = 0;
int leftDarkness = 0;
int rightDarkness = 0;
int darkest = 0;
int lightest;
int contrast;
int contrastThreshold = 170;// default 170
//*******************************************************

//Create QTR Sensor Line Following Object
QTRSensorsRC qtrrc((unsigned char[]) {LeftSensePin, RightSensePin},2, 2500, QTR_NO_EMITTER_PIN);
unsigned int sensorValues[2];


//Create DRV8853 Motor Shield object
DRV8835MotorShield motors;


void setup()
{
  // uncomment one or both of the following lines if your motors' directions need to be flipped
  motors.flipM1(true);
  motors.flipM2(true);
  Serial.begin(115200);
}

void loop()
{
  
  qtrrc.read(sensorValues); //Read Sensors - High Value shows darker line.
  leftDarkness = sensorValues[0];
  rightDarkness = sensorValues[1];
  //Serial.print("right: ");Serial.print(rightDarkness);
  //Serial.print(" left: ");Serial.println(leftDarkness);
  
  rememberExtremes();
  
  contrast = abs(leftDarkness - rightDarkness);

  if( contrast <= contrastThreshold ){
    //both sides are really similar... go straight
    motors.setM1Speed( MaxDesiredSpeed );
    motors.setM2Speed( MaxDesiredSpeed );
  }else{
    
    //map(value, fromLow, fromHigh, toLow, toHigh)
    leftSpeed = map(rightDarkness, lightest, darkest, MinSpeed, MaxDesiredSpeed);
    rightSpeed = map(leftDarkness, lightest, darkest, MinSpeed, MaxDesiredSpeed);
    
    motors.setM1Speed(rightSpeed);
    motors.setM2Speed(leftSpeed);
    
  }
}

void rememberExtremes(){
  if(leftDarkness > darkest){
    darkest = leftDarkness;
  }
  
  if(rightDarkness > darkest){
    darkest = rightDarkness;
  }
    
  if(leftDarkness < lightest){
    lightest = leftDarkness;
  }
  
  if(rightDarkness < lightest){
    lightest = rightDarkness;
  }
}

