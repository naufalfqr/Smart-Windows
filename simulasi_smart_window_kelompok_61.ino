#include <LiquidCrystal.h>
#include <Servo.h>

#define RS 7
#define E  6
#define D4 5
#define D5 4
#define D6 3
#define D7 2

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

byte degree[] = { 7, 5, 7, 0, 0, 0, 0, 0 };

#define sensorTMP36   A1

int sensorLDR = A0;
const int pinDC = 8;

String msg;

Servo myservo;
int value;
int angle;

void setup() {
  Serial.begin(9600);
  
  pinMode(pinDC, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.createChar(0, degree);
  lcd.clear();
  lcd.print("Temperature");
  delay(5000);
  delline(1);
  
  myservo.attach(9);
}

void Temperature ( int v ) {
  msg = "";
  if (v >= 56 && v <= 125)        {

    msg =  " HOT    ";
  }
  else if (v >= 40  && v <= 55) {

    msg =  " WARM   ";
  }
  else if (v >= 25  && v <= 39) {

    msg = " NORMAL ";
  }
  else if (v >= 10  && v <= 24) {

    msg = " COOL   ";
  }
  else if (v >= 0   && v <= 9)  {

    msg = " COLD   ";
  }
  else if (v >= -40 && v <= -1) {

    msg =  " FREEZE ";
  }
}

float fmap(long x, long in_min, long in_max, long out_min, long out_max) {
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

void delline(int line) {
  lcd.setCursor(0, line);
  lcd.setCursor(0, line);
}


void loop() {
  int nilaiSensor;
  nilaiSensor = analogRead(sensorLDR);
  
  if(nilaiSensor <=200){
    digitalWrite(pinDC, HIGH);
  }else{
    digitalWrite(pinDC, LOW);
  }
  delay(1000);
  
  float C = fmap(((analogRead(sensorTMP36) - 20 ) * 3.04), 0, 1023, -40, 125);
  Temperature(C);
  
  float Celsius    = C;
  lcd.setCursor(4, 1);
  delay(250); delline(1);
  lcd.print(Celsius);
  lcd.write((byte)0); lcd.print("C  ");
  lcd.setCursor(9, 1); lcd.print(msg);
  delay(100); delline(1);
  
  value = analogRead(A1);
  angle = map(value, 0, 50, 0, 180);
  Serial.println(angle);
  if (value >= 25){
    myservo.write(angle);                 
    delay(15);
  }
}