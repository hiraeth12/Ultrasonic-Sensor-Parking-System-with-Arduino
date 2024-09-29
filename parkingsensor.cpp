#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define Buzzpin 2
#define Trigpin 3
#define Echopin 4
#define ledRed 5
#define ledYellow 6
#define ledWhite 7

long duration,cm,inches;

void setup(){
    pinMode(Buzzpin,OUTPUT);
    pinMode(Trigpin,OUTPUT);
    pinMode(Echopin,OUTPUT);
    pinMode(ledRed,OUTPUT);
    pinMode(ledWhite,OUTPUT);
    pinMode(ledYellow,OUTPUT);
    lcd.begin();
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.home();
    Serial.begin(19200);
}

void loop(){
    lcd.setBacklight(1000);
    digitalWrite(Trigpin,LOW);
    delayMicroseconds(2);
    digitalWrite(Trigpin,HIGH);
    delayMicroseconds(10);
    digitalWrite(Trigpin,LOW);
    int duration = pulseIn(Echopin,HIGH);
    int distance = duration/58;
    int echopin = digitalRead(echopin);

    if(distance<50){
        digitalWrite(ledRed,HIGH);
        digitalWrite(ledYellow,LOW);
        digitalWrite(ledWhite,LOW);
        tone(Buzzpin,900,500);
        lcd.setcursor(0,1);
        lcd.print("Bahaya !!!");
    }

    else if(distance < 150){
        digitalWrite(ledYellow,HIGH);
        digitalWrite(ledWhite,LOW);
        digitalWrite(ledRed,LOW);
        tone(Buzzpin,LOW);
        lcd.setcursor(0,1);
        lcd.print("Hati-Hati!");
        delay(10);
    }

    if(distance>=150){
        digitalWrite(ledRed,LOW);
        digitalWrite(ledYellow,LOW);
        digitalWrite(ledWhite,HIGH);
        digitalWrite(Buzzpin,LOW);
        lcd.setcursor(0,1);
        lcd.print("Aman ");
    }
    delay(10);

    lcd.setCursor(0,0);
    lcd.print("Jarak = ");
    lcd.print("cm    ");
}
