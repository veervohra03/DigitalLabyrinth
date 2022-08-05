#include <Servo.h>
#include <LiquidCrystal.h>

int sensorState = 0;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo FRservo, FLservo, BRservo, BLservo;
const int Rbutton = A0, Lbutton = A1, Bbutton = A2, Fbutton = A3, Mbutton = A4;
int Rstate, Lstate, Bstate, Fstate, Mstate;
const int pull = 180, push = 0, eqlbrm = 90, pressedVal = 500;

bool play = false;

void setup() {
  Serial.begin(9600);
  FRservo.attach(7);
  FLservo.attach(8);
  BRservo.attach(9);
  BLservo.attach(10);
  servoReset();
  analogWrite(A5, HIGH);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
}

void loop() { 
  while (!play) {
    lcd.setCursor(0, 0);
    lcd.print("Press the center");
    lcd.setCursor(0, 1);
    lcd.print("button to begin");
    Mstate = analogRead(Mbutton);
    if (Mstate > pressedVal){
      play = true;    
    }
    lcd.clear();
  }
  
  Rstate = analogRead(Rbutton);
  Lstate = analogRead(Lbutton);
  Bstate = analogRead(Bbutton);
  Fstate = analogRead(Fbutton);
  sensorState = analogRead(A5);
  
  if (Rstate > pressedVal) {
    if (Fstate > pressedVal){
      FRservo.write(pull);
      BRservo.write(eqlbrm);
      FLservo.write(eqlbrm);
      BLservo.write(push);
    }
    if (Bstate > pressedVal) {
      FRservo.write(eqlbrm);
      BRservo.write(pull);
      FLservo.write(push);
      BLservo.write(eqlbrm);
    }
    else {
      FRservo.write(pull);
      BRservo.write(pull);
      FLservo.write(push);
      BLservo.write(push);
    }
  }
  if (Lstate > pressedVal) {
    if (Fstate > pressedVal){
      FRservo.write(eqlbrm);
      BRservo.write(push);
      FLservo.write(pull);
      BLservo.write(eqlbrm);
    }
    if (Bstate > pressedVal) {
      FRservo.write(push);
      BRservo.write(eqlbrm);
      FLservo.write(eqlbrm);
      BLservo.write(pulls); 
    }
    else {
      FRservo.write(push);
      BRservo.write(push);
      FLservo.write(pull);
      BLservo.write(pull);
    }
  }
  if (Fstate > pressedVal) {
    if (Rstate > pressedVal){
      FRservo.write(pull);
      BRservo.write(eqlbrm);
      FLservo.write(eqlbrm);
      BLservo.write(push);
    }
    if (Lstate > pressedVal) {
      FRservo.write(eqlbrm);
      BRservo.write(push);
      FLservo.write(pull);
      BLservo.write(eqlbrm);
    }
    else {
      FRservo.write(pull);
      FLservo.write(pull);
      BRservo.write(push);
      BLservo.write(push);  
    }
  }
  if (Bstate > pressedVal) {
    if (Rstate > pressedVal){
      FRservo.write(eqlbrm);
      BRservo.write(pull);
      FLservo.write(push);
      BLservo.write(eqlbrm); 
    }
    if (Lstate > pressedVal) {
      FRservo.write(push);
      BRservo.write(eqlbrm);
      FLservo.write(eqlbrm);
      BLservo.write(pulls);
    }
    else {
      FRservo.write(push);
      FLservo.write(push);
      BRservo.write(pull);
      BLservo.write(pull);  
    }
  }
  else {
    servoReset();  
  }

  if (sensorState == HIGH){
    servoReset();
    Serial.println("DONE");
    play = false;
    delay(100);
  }

}

void servoReset(){
    FRservo.write(eqlbrm);
    FLservo.write(eqlbrm);
    BRservo.write(eqlbrm);
    BLservo.write(eqlbrm);
}
