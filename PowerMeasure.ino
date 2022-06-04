#include <LiquidCrystal.h>
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; 
const int INPUTPIN = 1;
float READVAL =0;
double VOLTAGE=0;
double CURRENT=0;
bool control = true;


LiquidCrystal lcd(pin_RS,pin_EN,pin_d4,pin_d5,pin_d6,pin_d7);
void setup() {
  LCDSETUP();
  Serial.begin(9600);
}

void loop() {
  while(control){
    Serial.println("Current, Power");
    control = false;
  }
  Measure();
}
void LCDSETUP(){
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("AMPS: ");
  
  lcd.setCursor(0,1);
  lcd.print("Watts: ");
  
}
void LCDUPDATE(double amp, double watt){
  LCDSETUP();
  lcd.setCursor(7,0);
  lcd.print(amp);
  lcd.setCursor(7,1);
  lcd.print(watt);
  delay(100);
}
void Measure(){

  int temp=0;
  float maxpoint = 0;
  for(int i =0;i<500;i++){
    if(temp = analogRead(INPUTPIN),temp>maxpoint){
      maxpoint=temp;
    }
  }
  READVAL = maxpoint;
  VOLTAGE = (READVAL/1024.0)*5000;
  CURRENT = ((VOLTAGE-2504.88)/66);
  CURRENT = (CURRENT)/(sqrt(2));
  Serial.print(CURRENT);
  Serial.print(",");
  Serial.println(CURRENT*220);
  delay(1000);
  LCDUPDATE(CURRENT,CURRENT*220);
  
  
  

} 
