#include<LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);
#define in 4
#define out 5
int count=0;

void IN()
{
delay(100);
while(digitalRead(out)==1);
  if(digitalRead(out)==0)
  {
    count++;
  }
 
      lcd.setCursor(0,0);
    lcd.print("Count:");
  
    lcd.print(count);
      lcd.print(" ");
    delay(1200);
}

void OUT()
{
delay(100);
while(digitalRead(in)==1);
  if(digitalRead(in)==0 && count>0)
  {
    count--;
  }

  
      lcd.setCursor(0,0);
    lcd.print("Count:");
  
    lcd.print(count);
      lcd.print(" ");
    delay(1200);
   
}
void setup() {

Serial.begin(9600);
 
analogReference(DEFAULT);
  Serial.println("Counter");
   lcd.begin(16,2);
  lcd.print("Visitor Counter");
  delay(2000);
 
  
 
  pinMode(in, INPUT); // in sensor
  pinMode(out, INPUT); // out sensor
 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Count:");
    pinMode(6, OUTPUT); //r
     digitalWrite(6, HIGH);
       
  lcd.print(count);
  
}

void loop() {

  
while(digitalRead(in)==0)
  IN();
  while(digitalRead(out)==0)
  OUT();


  if(count>0)
 {
  digitalWrite(6, LOW);
 
 }
 else
 {
  digitalWrite(6, HIGH);
 
 }


}
