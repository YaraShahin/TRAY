#include <SoftwareSerial.h>
#include <Servo.h>
#include <AFMotor.h>

//creates An object to control the terminals A1 and A0 to Act As TX and Rx Pins For Serial Communication Over Bluetooth
SoftwareSerial bluetooth(A0, A1);

Servo TrayServo; //Creates Servo Object and Names it TrayServo

//creates Four objects to control the terminals 1,2, 3 and 4 of motor shield
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

//Defining a Speed Variable For Movement
int M_Speed = 10;
//Defining an Angle Variable For Servo Rotation (Tray Extension)
float Angle = 90;

float Intial_Angle = 0;
void setup() {
  // put your setup code here, to run once:
  bluetooth.begin(9600);//Sets Up Data Transfer Rate Over Bluetooth
  Serial.begin(9600);//Sets Up Data Transfer Rate Over Serial Via USB

  myservo.attach(10);// Assigns Pin 10 to Servo
  myservo.write(Intial_Angle);//Set Servo to the Predefined Intial Angle
}

void loop() {
  // put your main code here, to run repeatedly:
  while (bluetooth.available())
  {
    DataString = bluetooth.readString();//Captures Data String From Bluetooth
    int Data = DataString.toInt();//Converts The Data String to Numerical Values
    //Checking Whether the Sender Sent 1 or -1
    if (Data == 1 or Data == -1)
    {
      Move(Data, M_Speed); // Calling A Move Function While Passing Data As a Parameter to Specify Direction
    }
    if (Data == 2 or Data == -2)
    {
      Extend_Tray(Data, Angle); //Calling A Extend Tray Function While Passing Data As a Parameter to Specify Direction
    }

  }
}
void Move(int Data, int Mspeed)
{
  //Code For Forward and Backward Movement

  if (Data > 0)
  {
    motor1.setSpeed(Mspeed); //Define maximum velocity
    motor1.run(FORWARD); //rotate the motor clockwise
    motor2.setSpeed(Mspeed); //Define maximum velocity
    motor2.run(FORWARD); //rotate the motor clockwise
  }
  else if (Data < 0)
  {
    motor1.setSpeed(Mspeed); //Define maximum velocity
    motor1.run(BACKWARD); //rotate the motor clockwise
    motor2.setSpeed(Mspeed); //Define maximum velocity
    motor2.run(BACKWARD); //rotate the motor clockwise
  }
  else
  {
    return;
  }

}
void Extend_Tray(int Data, int angle)
{
  //Code For Tray Extension and Retreival
  if (Data > 0) {
    myservo.write(angle);//Set Servo Angle to Variable angle Value
    delay(20);//Wait 20 milisecond Before Excuting any other Commands
  }
  else if (Data < 0)
  {
    myservo.write(Intial_Angle);//Set Servo to the Predefined Intial Angle
  } else
  {
    return;
  }

}
