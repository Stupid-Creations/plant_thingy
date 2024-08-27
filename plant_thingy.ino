#include <LiquidCrystal.h>

LiquidCrystal lcd(11, 10, 9, 8, 7,6);

const int R = 1;
const int G = 2;
const int photoresistor = 5;
const int pins[] = {16,17,18,19,20,21,22,26,27,28};

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  //lcd.print("Hello World!");
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(photoresistor,INPUT);
  for(int i = 0; i < 10; i++){
    pinMode(pins[i],OUTPUT);
  }
}

bool okay = true;

void loop() {
  okay = true;
  lcd.clear();
  lcd.setCursor(0,0);

  float brightness = map(analogRead(photoresistor),0,1024,0,10);

  for(int i = 0; i < 10;i++){
    if(i < brightness){
      digitalWrite(pins[i],HIGH);
    }else{
      digitalWrite(pins[i],LOW);
    }
  }


  lcd.clear();
  lcd.print(analogRead(photoresistor)); lcd.print("*C, ");


  if(okay == false){
    analogWrite(R,255);
    analogWrite(G,0);

  }if(okay == true){
    analogWrite(G,255);
        analogWrite(R,0);

  }

}
