#define ledPin 10
#define relayPin 9
#define tempRightPin 1
#define tempLeftPin 0

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float tempRightC;
float tempLeftC;
int readingTempRight;
int readingTempLeft;
int timeOn;
int timeOff;
int razlikaTime;
int razlikaRealy = 5;
boolean relayStatus = false;
//float tempOffset = 4.14;
float tempOffset = 3.13;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  //pinMode(7, OUTPUT);
  analogReference(INTERNAL);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
readingTempRight = analogRead(tempRightPin);
readingTempLeft = analogRead(tempLeftPin);
if (relayStatus) {
tempRightC = (readingTempRight / 9.31) - tempOffset;
tempLeftC = (readingTempLeft / 9.31) - tempOffset;
}
else{
tempRightC = (readingTempRight / 9.31);
tempLeftC = (readingTempLeft / 9.31);
}
razlikaTime = (timeOn-timeOff);

lcd.setCursor(0, 0);
Serial.print("Left:");
Serial.print(tempLeftC);
lcd.print("l:");
lcd.print(tempLeftC);
Serial.print(" | Right:");
Serial.print(tempRightC);
lcd.print(" r:");
lcd.print(tempRightC);

Serial.print(" ## ");
//lcd.print(" ## ");

lcd.setCursor(0, 1);
Serial.print("TimeOn:");
Serial.print(timeOn);
lcd.print("o:");
lcd.print(timeOn%100);
Serial.print(" | TimeOff:");
lcd.print(" f:");
Serial.print(timeOff);
lcd.print(timeOff%100);
Serial.print(" | Razlika:");
Serial.print(razlikaTime);
lcd.print(" r:");
lcd.print(razlikaTime%1000);
lcd.print("  ");
//lcd.noDisplay();
//lcd.display();
//lcd.print("hello, world!");

//if ((tempLeftC > 22) && (tempRightC < 25))
if ((tempLeftC > 28) && (tempRightC < 35)) {
  timeOn = (int) (millis()/1000);
  }
else {
  timeOff = (int) (millis()/1000);
  }
if (razlikaTime > 15){
  digitalWrite(ledPin, 1);
  digitalWrite(relayPin, 1);
  //digitalWrite(7, 1);
  relayStatus = true;
}
else if (razlikaTime < -15){
  digitalWrite(ledPin, 0);
  digitalWrite(relayPin, 0);
  //digitalWrite(7, 0);
  relayStatus = false;
}
delay(1000);
}
