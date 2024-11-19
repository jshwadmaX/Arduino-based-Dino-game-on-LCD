#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int switchState=0;
int switchFirstPress=0;

bool buttonPressed=0;
int jumpButton=7;
bool dinoLast=0;

int j;
int score=0;
unsigned int number=16;

unsigned long t; //unsigned long used for millis
unsigned long t1;
unsigned long t2;
unsigned long t3;

int objectDelay=200; //basic cactus moving speed
int objectDecrease=20; //decreases delay

bool dinoUp=0;

byte cactus[8] = { //cactus
  B00101,
  B10101,
  B10101,
  B10101,
  B10110,
  B01100,
  B00100,
  B00100,
};

byte dino[8] = { //dino
  B01110,
  B10111,
  B11110,
  B11111,
  B11000,
  B11111,
  B11010,
  B10010,
};
byte dinoPositionTwo[8] = { //dino 2nd position
  B01110,
  B10111,
  B11110,
  B11111,
  B11000,
  B11111,
  B11010,
  B10010,
};

void text() {
  lcd.print("PRESS TO START");
  delay(500);
  lcd.clear();
  lcd.print(" ");
  delay(500);
  lcd.clear();
}
void setup() {
lcd.begin(16, 2);

lcd.createChar(7, cactus);
lcd.createChar(6, dino);
lcd.createChar(5, dinoPositionTwo);

j=15;

t=millis();
t1=millis();
t2=millis();
t3=millis();
Serial.begin(9600);

switchFirstPress = digitalRead(jumpButton);
while(switchFirstPress == LOW) {
  lcd.setCursor(2, 1);
  lcd.write(6);
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("PRESS TO START");
  delay(500);
  lcd.print(" ");
  lcd.clear();
switchFirstPress = digitalRead(jumpButton);
  if (switchFirstPress == HIGH) {
    break;
  }
}
delay(500);
}
void dinoRunMovement() {
  
}
void loop() {
switchState = digitalRead(jumpButton);
if((millis()-t)>=objectDelay) { //delay on cactus move
  t=millis();
  lcd.clear();
  lcd.setCursor(j, 1);
  lcd.write(7);
  j=j-1;
    if(j == -1) {
      j=15;
    }
  byte digits = (score > 9999) ? 5 : (score > 999) ? 4 : (score > 99) ? 3 : (score > 9) ? 2 : 1;
  lcd.setCursor(number-digits, 0);
  lcd.print(score);
}
if((millis()-t1)>=50) {
  t1=millis();
  if (switchState == HIGH && dinoUp == false) {
    lcd.setCursor(2, 0);
    lcd.write(6);
    dinoUp = true; 
    t2=millis();
  }
  else if(dinoUp == true) {
    lcd.setCursor(2, 0);
    lcd.write(6);
  }
  else if(dinoUp == false) {
    lcd.setCursor(2, 0);
    lcd.print(" ");
    lcd.setCursor(2, 1);
    lcd.write(6);
  }
}
if((millis()-t2)>=500 && dinoUp == true) {
  t2=millis();
  lcd.setCursor(2, 1);
  lcd.write(6);
  lcd.setCursor(2, 0);
  lcd.print(" ");
  dinoUp = false;
}
if(((millis()-t3)>=1000) && (j == 1)) {
  t3=millis();
  if (dinoUp == true) {
    score=score+1;
    if (score%2 == 0) {
    objectDelay=objectDelay-objectDecrease;
      if(objectDelay <= 200) { //makes 200 highest speed 
        objectDecrease=0; //keeps cactus/object at max speed and wont keep increasing it
      }
    }
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GAME OVER!");
    lcd.setCursor(0, 1);
    lcd.print("TAP TO RETRY");
    score=0;
    j=15;
    objectDelay=500; //toggles back to basic speed
    switchState = digitalRead(jumpButton);
      while(switchState == LOW) {
        switchState = digitalRead(jumpButton);
      }
      delay(500);
  }
}
}
