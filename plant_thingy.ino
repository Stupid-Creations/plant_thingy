#include <LiquidCrystal.h>
#include <SimpleDHT.h>

LiquidCrystal lcd(11, 10, 9, 8, 7,6);

const int R = 1;
const int G = 2;
const int DHT  = 12;
const int photoresistor = 27;
const int pins[] = {16,17,18,19,20,21,22,26,5,28};
//28,5,26,22,21,20,19,18,17,16
SimpleDHT22 dht22(DHT);

uint8_t drop[8] = {
  0b00001,
  0b00011,
  0b00101,
  0b01001,
  0b10001,
  0b10010,
  0b01100,
  0b00000,
};

void setup() {
  lcd.createChar(1,drop);
  Serial1.begin(115200);
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

  String text = "";

  float temperature = 0;
  float humidity = 0;

  int err = SimpleDHTErrSuccess;

  float bright = analogRead(photoresistor);
  float brightness = map(bright,8,1016,10,0);

  Serial1.println(brightness);
  for(int i = 0; i < 10;i++){
    if(i<brightness){
      digitalWrite(pins[i],HIGH);
    }else{
      digitalWrite(pins[i],LOW);
    }
  }
  

  if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    lcd.print("oops, DHT fail"); lcd.print(SimpleDHTErrCode(err));
    lcd.print(","); lcd.println(SimpleDHTErrDuration(err)); delay(2000);
    return;
  }
  lcd.clear();
  lcd.print((temperature*(9/5))+32); lcd.print("F, ");
  lcd.print((float)humidity); lcd.println("%");
  if(humidity < 20){
    lcd.setCursor(0,1);
    text += "\x01 ";
    okay = false;
  }
  if(temperature < 25){
    lcd.setCursor(0,1);
    text += "brr, cold";
    okay = false;
  }
  if(temperature > 35){
    lcd.setCursor(0,1);
    text += "too hot";
    okay = false;
  }
  if(okay == false){
    analogWrite(R,255);
    analogWrite(G,0);

  }if(okay == true){
    analogWrite(G,255);
        analogWrite(R,0);

  }
  lcd.print(text);
  // DHT22 sampling rate is 0.5HZ.
  delay(2500);

}
