#include <Servo.h>

const int pingPin = 7;
int ledPin = 13;
Servo bottomServo;


int topServo = 10;//Define servo PWM control as digital 10
int myangle = 10;//define variable angle
int pulsewidth;//define variable pulse width
int val;

int forward = 20;
int forwardFast = 1;
int backward = 600; //increase to increase backward speed
int backwardFast = 1000;

int topRocker = 2;
int bottomRocker = 3;

boolean DeathStarShouldLower = false;

boolean HasStartedMovingForward = false;
 

void setup() {
 
  
  pinMode(ledPin, OUTPUT);
  bottomServo.attach(4);

  pinMode(topServo,OUTPUT);
  Serial.begin(9600);
  
}


void loop(){
  
  while(DeathStarShouldLower == true){
    servopulse(topServo,backward);
    
    if(digitalRead(bottomRocker) == HIGH){
     DeathStarShouldLower = false; 
     HasStartedMovingForward = false;
    }
    
      
  }
  
  
  long duration, inches, cm;

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  inches = microsecondsToInches(duration);
 
  delay(100);
  
  if (inches <=12){
   digitalWrite(ledPin, HIGH);
   servopulse(topServo, forwardFast);
   HasStartedMovingForward = true;
  }else if(inches > 12 && inches < 36){
    if(HasStartedMovingForward == true){
      DeathStarShouldLower = true;
      digitalWrite(ledPin, LOW);
    }else{
      digitalWrite(ledPin, HIGH);
    }
    
  }else{
     digitalWrite(ledPin,LOW);
     if(HasStartedMovingForward == true){
       DeathStarShouldLower = true;
     }
  
  }
  
  if(digitalRead(topRocker) == HIGH){
    bottomServo.write (90);
    delay(1000);
    bottomServo.write (-90);
    delay(1000);
    DeathStarShouldLower = true;
   
  }
  

}

////////////////////////////////////////////////////


long microsecondsToInches(long microseconds){
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}


void servopulse(int servopin,int spinSpeed){//define a pulse function

  pulsewidth = (spinSpeed) + 400;//translate angle to a pulse width value between 500-2480
  digitalWrite(servopin,HIGH);//pull the interface signal level to high
  if(spinSpeed > 1){
    delayMicroseconds(pulsewidth);//delay in microseconds
  }
  digitalWrite(servopin,LOW);//pull the interface signal level to low
  
}
