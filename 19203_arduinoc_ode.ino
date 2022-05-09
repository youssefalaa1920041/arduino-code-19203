// steper motor
#include <Stepper.h>
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
// arms
#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
int pos = 0;
// ultra
#define trig 26
#define echo 25
int distanceus = 0, t = 0;

// ir
unsigned long beginTime = 0;
unsigned long endTime;
unsigned long distance[3];
int i = 0;
unsigned long sp = 4.5;
int cir = 0;



void setup() {

  // convey
  digitalWrite(3, HIGH); //gate1
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  digitalWrite(4, HIGH); //gate2
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  // hand one
  digitalWrite(3, HIGH);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  // hand two
  digitalWrite(4, HIGH);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  // arms
  servo1.attach(30);
  servo2.attach(31);
  servo3.attach(32);
  servo4.attach(33);
  servo5.attach(34);
  servo6.attach(35);
  servo7.attach(36);
  
  // steper motor
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
  
  // moving ir
  digitalWrite(3, HIGH);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  //
  //
  //
  // ultra
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  // ir
  pinMode(22, INPUT);
  Serial.begin(9600);
  pinMode(23, OUTPUT);
  mechanism(1);

}

void loop() {
  i = 0;
  // dc beta3 ir
  while (i < 3)
  {
    digitalWrite(13, HIGH);
    digitalWrite(14, LOW);
    //
    // ir
    if (digitalRead(22) == 1)
    {
      beginTime = millis();
      while (digitalRead(22))
        endTime = millis();
      digitalWrite(13, LOW);
      Serial.print("begin : ");
      Serial.println(beginTime);
      Serial.print("end : ");
      Serial.println(endTime);
      distance[i] = endTime - beginTime;
      distance[i] *=  sp;
      distance[i] /=  1000;
      Serial.print("distance : ");
      Serial.println(distance[i]);
      if (i == 2)
      {
        digitalWrite(trig, LOW);
        delayMicroseconds(5);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        t = pulseIn(echo, HIGH);
        distanceus = t / 57;
        Serial.println(distanceus);
        if (distanceus < 2)
        {
          //increase the cutting distance
        }
        if ((distance[0] > 1 || distance[0] < 4) && (distance[1] > 1 || distance[1] < 4) && (distance[2] > 1 || distance[2] < 4))
        {
          //positive feed back
          mechanism(1);
        }
        else if (distance[0] > 3 && distance[1] > 3 && distance[2] > 3 )
        {
          //moving mechanism motor
          //greater than 3
          mechanism(2);
        }
      }
      i++;
    }
    delay(50);
  }
  //  Serial.println(millis());
  //  digitalWrite(23, HIGH);
  // ultra

  delay(300);
  //

}

void mechanism(int x)
{
  if (x == 1)
  {
    // convey
    /*------------------------*/
    digitalWrite(5, HIGH); //gate1
    digitalWrite(6, LOW);
    delay(3000);
    digitalWrite(5, LOW);

    digitalWrite(7, LOW); //gate2
    digitalWrite(8, LOW);
    //..................................
  }
  else
  {
    //from 1 : 4
    digitalWrite(7, HIGH); //gate1
    digitalWrite(8, LOW);
    delay(3000);
    digitalWrite(7, LOW);
    digitalWrite(5, LOW); //gate2
  }

  //hand one and two open
  digitalWrite(13, HIGH);
  digitalWrite(14, LOW);
  digitalWrite(17, HIGH);
  digitalWrite(18, LOW);
  delay(1000);

  digitalWrite(13, LOW);
  digitalWrite(17, LOW);
  // arm one and two forward
  for (pos = 180; pos >= 150; pos -= 1)
  {
    servo1.write(pos);
    servo2.write(pos);
    delay(15);
  }

  //hand one and two close
  digitalWrite(14, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(18, HIGH);
  digitalWrite(17, LOW);
  delay(1000);

  digitalWrite(14, LOW);
  digitalWrite(18, LOW);
  /*..............................*/
  //steper motor
  // step one revolution in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
  /*................................*/
  // arm one and two backward
  for (pos = 150 ; pos <= 180; pos += 1)
  {
    servo1.write(pos);
    servo2.write(pos);
    delay(15);
  }
  // arm one bases rotate forward
  for (pos = 180; pos >= 150; pos -= 1)
  {
    servo3.write(pos);
    delay(15);
  }
  // arm two bases rotate forward
  for (pos = 180; pos >= 150; pos -= 1)
  {
    servo4.write(pos);
    delay(15);
  }
  //hand one and two open
  digitalWrite(13, HIGH);
  digitalWrite(14, LOW);
  digitalWrite(17, HIGH);
  digitalWrite(18, LOW);
  delay(1000);

  digitalWrite(14, LOW);
  digitalWrite(18, LOW);
  // arm one bases rotate backward
  for (pos = 180; pos >= 150; pos -= 1)
  {
    servo3.write(pos);
    delay(15);
  }
  // arm two bases rotate backward
  for (pos = 180; pos >= 150; pos -= 1)
  {
    servo4.write(pos);
    delay(15);
  }
  // moving ir
  for (pos = 180; pos >= 150; pos -= 1)
  {
    servo5.write(pos);
    delay(15);
  }
}
