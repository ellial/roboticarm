#include <Servo.h>
#define Bluetooth Serial1
#define motorPin1 3
#define motorPin2 5
#define dirPin 6
#define stepPin 7
Servo grip, wPitch, wRoll, elbow;
int servo1Pos, servo2Pos, servo3Pos, servo4Pos; // current position
int servo1PPos, servo2PPos, servo3PPos, servo4PPos; // previous position
int speedDelay = 20;
int stepSpeedDelay = 1500;
int dataIn;
int m = 0;

void setup() {
  // put your setup code here, to run once:
  //setup bluetooth
  Bluetooth.begin(9600);
  Bluetooth.setTimeout(5);

  //setup servo
  grip.attach(9);
  wPitch.attach(10);
  wRoll.attach(11);
  elbow.attach(12);

  //start positions
  servo1PPos = 50;
  servo2PPos = 90;
  servo3PPos = 90;
  servo4PPos = 90;
  grip.write(servo1PPos);
  wPitch.write(servo2PPos);
  wRoll.write(servo3PPos);
  elbow.write(servo4PPos);

  //setup motors(PWM pins)
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  //setup stepper
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  if (Bluetooth.available() > 0) {
    dataIn = Bluetooth.read();  // Read the data
    if (dataIn == 0) {
      m = 0;
    }
    if (dataIn == 1) {
      m = 1;
    }
    if (dataIn == 2) {
      m = 2;
    }
    if (dataIn == 3) {
      m = 3;
    }
    if (dataIn == 4) {
      m = 4;
    }
    if (dataIn == 5) {
      m = 5;
    }
    if (dataIn == 6) {
      m = 6;
    }
    if (dataIn == 7) {
      m = 7;
    }
    if (dataIn == 8) {
      m = 8;
    }
    if (dataIn == 9) {
      m = 9;
    }
    if (dataIn == 10) {
      m = 10;
    }
    if (dataIn == 11) {
      m = 11;
    }
    if (dataIn == 12) {
      m = 12;
    }
    if (dataIn == 13) {
      m = 13;
    }
    if (dataIn == 14) {
      m = 14;
    }
    // Move grip in positive direction
    while (m == 1) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();
      }
      grip.write(servo1PPos);
      servo1PPos = constrain(servo1PPos++, 0, 80);
      delay(speedDelay);
    }
    // Move servo 1 in negative direction
    while (m == 2) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();
      }
      grip.write(servo1PPos);
      servo1PPos = constrain(servo1PPos--, 0, 80);
      delay(speedDelay);
    }
    // Move wPitch
    while (m == 3) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();
      }
      wPitch.write(servo2PPos);
      servo2PPos = constrain(servo2PPos++, 0, 180);
      delay(speedDelay);
    }
    while (m == 4) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();
      }
      wPitch.write(servo2PPos);
      servo2PPos = constrain(servo2PPos--, 0, 180);
      delay(speedDelay);
    }
    // Move wRoll
    while (m == 5) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();
      }
      wRoll.write(servo3PPos);
      servo3PPos = constrain(servo3PPos++, 0, 180);
      delay(speedDelay);
    }
    while (m == 6) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();
      }
      wRoll.write(servo3PPos);
      servo3PPos = constrain(servo3PPos--, 0, 180);
      delay(speedDelay);
    }
    // Move elbow sinchronyze
    while (m == 7) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();
      }
      wPitch.write(servo2PPos);
      elbow.write(servo4PPos);
      if (servo4PPos >= 0 && servo4PPos <= 180) {
        servo2PPos = constrain(servo2PPos--, 0, 180);
        servo4PPos = constrain(servo4PPos++, 0, 180);
      }
      delay(speedDelay);
    }
    while (m == 8) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();
      }
      wPitch.write(servo2PPos);
      elbow.write(servo4PPos);
      if (servo4PPos >= 0 && servo4PPos <= 180) {
        servo2PPos = constrain(servo2PPos++, 0, 180);
        servo4PPos = constrain(servo4PPos--, 0, 180);
      }
      delay(speedDelay);
    }
    // Move stepper
    while (m == 9) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();
      }
      digitalWrite(dirPin, LOW); // Enables the motor to move in a first direction
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(stepSpeedDelay);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(stepSpeedDelay);
    }
    while (m == 10) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();
      }
      digitalWrite(dirPin, HIGH); // Enables the motor to move in a second direction
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(stepSpeedDelay);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(stepSpeedDelay);
    }
    // Move DC-base
    while (m == 11) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();
      }
      analogWrite(motorPin1, 255);
      digitalWrite(motorPin2, LOW);
    }
    while (m == 12) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();
      }
      analogWrite(motorPin2, 255);
      digitalWrite(motorPin1, LOW);
    }
    if (m == 13) {//hello
      grip.write(50);
      wPithc.write(60);
      wRoll.write(90);
      elbow.write(120);
      delay(1000);
      wRoll.write(120);
      delay(1000);
      wRoll.write(60);
      delay(1000);
      grip.write(30);
      delay(1000);
      grip.write(80);
      delay(1000);
      wRoll.write(90);
      delay(1000);
      wPitch.write(90);
      delay(500);
      wPitch.write(30);
      delay(500);
      wPitch.write(90);
      delay(500);
      wPitch.write(30);
      delay(500);
      wPitch.write(60);
      delay(500);
      Bluetooth.flush();
      m = 0;
    }
    if (dataIn > 101 & dataIn < 250) {
      speedDelay = dataIn / 10; // Change servo speed (delay time)
      stepSpeedDelay = constrain(1500 + (dataIn - 100) * 3, 1500, 2000);
    }
  }
}
