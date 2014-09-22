#include <Servo.h>

const int pingPin = 7;
int ledPin = 13;
Servo servo1;


int angle;
int minAngle = 0;
int maxAngle = 720;


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  servo1.attach(9);
}

void loop()
{
 // int position;
  
  //servo1.write(90);
  //delay(1000);
  //servo1.write(180);
  //delay(1000);
  //servo1.write(0);
  //delay(1000);
  
  //for(position = 0; position < 180; position += 100)
  //{
    //servo1.write(position);  // Move to next position
    //delay(20);               // Short pause to allow it to move
 // }

  // Tell servo to go to 0 degrees, stepping by one degree

 // for(position = 180; position >= 0; position -= 100)
 // {                                
  //  servo1.write(position);  // Move to next position
  //  delay(20);               // Short pause to allow it to move
 // }
  
  
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
  
  //This section is for when the user walks up to the installation
  //and the light turns on to let the user know he is close enough to 
  //begin using the force.
      if (inches <=36) {
          digitalWrite(ledPin, HIGH);
          servo1.write(maxAngle);
      }
      else {
          digitalWrite(ledPin,LOW);
          servo1.write(minAngle);
      }
      
      
  /*This section is for if the user is too close to the installation,
  the light will blink and a noise will play saying "The force is too strong
  with this one. DO I EVEN NEED TO HAVE THIS FUNCTION? 
      
      if (inches<=12) {
          digitalWrite(ledPin,HIGH);
          delay(50);
          digitalWrite(ledPin,LOW);
          delay(50);
      }
      else {
          digitalWrite(ledPin,LOW);
      }
  */
      
     
  //This section is for when the user holds up his hand to begin using
  //the force. The PING))) sensor should trigger the top servo to begin
  //winding up the string the Deathstar is hanging from.     
  
      
  
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
