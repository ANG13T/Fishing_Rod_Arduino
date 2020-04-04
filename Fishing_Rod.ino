#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>

Servo baseServo;
Servo armServo;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

int potpin = 0;
int potVal;
int buttonInput = 5;
int buttonVal;

void setup() {
  // put your setup 
  Serial.begin(9600);
  baseServo.attach(7);
  armServo.attach(6);
  lcd.init();
  lcd.begin(16, 2); //Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
  lcd.setCursor(0, 0);
  lcd.print("Lets Catch Fish!");
}

void loop() {
  // put your main code here, to run repeatedly:
  potVal = analogRead(potpin); // reads the value of the potentiometer (value between 0 and 1023)
  buttonVal = digitalRead(buttonInput);
  potVal = map(potVal, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  baseServo.write(potVal);                  // sets the servo position according to the scaled value
  delay(15);  
  if(buttonVal == HIGH){
    Serial.println("yee");
    fishRodDown();
    delay(100);
    lcd.clear();
    lcd.print("Points: ");
  }
}

void fishRodDown(){
  lcd.clear();
  lcd.print("Reeling...");
  int angle;
    for(angle = 180; angle > 50; angle -= 1)    // command to move from 0 degrees to 180 degrees 
  {                                  
    armServo.write(angle);
    delay(15);                       
  } 
  for(angle = 50; angle < 250; angle += 1)    // command to move from 0 degrees to 180 degrees 
  {                                  
    armServo.write(angle);
    delay(15);                       
  } 
}
