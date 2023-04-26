#include<LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);
#include <SoftwareSerial.h>
long  t2=0;
long  t1=0;
SoftwareSerial ser(5, 6); // RX, TX
String stri;

char buf1[16];

// MY channel's thingspeak API key
String apiKey = "IHB5AUKVFV0FIJJX";
int sem1=0;
int count3=0;
int i=0;
int sem=0;
int count =0;
int count1 =0;s
int count2 =0;

long measurementStartTime = 0;

void setup(){
  Serial.begin(9600);
   
  lcd.begin(16,2);
 
  lcd.setCursor(0,0);
      lcd.print("IOT Energy Meter");
 
      lcd.setCursor(0,1);
      lcd.print("Count:");
     
      analogReference(DEFAULT);
    // enable software serial
  ser.begin(115200);
// reset ESP8266
  ser.println("AT+RST");
   delay(500);
  ser.println("AT+CWMODE=3");
   delay(500);
  ser.println("AT+CWJAP=\"project\",\"12345678\"");
  delay(500);
}
 
void loop(){
 
//Serial.println(analogRead(A4));

  if((analogRead(A4) < 850) && (sem == 0))
{
  sem = 1;

  count++;
  //Serial.println(count1);
}
count1=count*10;
lcd.setCursor(8,1);
      lcd.print(count1);
      lcd.print("    ");
if((analogRead(A4) >= 850) && (sem == 1))
{
  sem = 0;
 
}

stri = dtostrf(count1, 4, 1, buf1);

    Serial.print(stri);
    Serial.println(" ");
 delay(100);
 
     if(millis() - t2>15000)
  {
    t2=millis();
 
   // TCP connection
  String cmd1 = "AT+CIPSTART=\"TCP\",\"";
  cmd1 += "184.106.153.149"; // api.thingspeak.com
  cmd1 += "\",80";
  ser.println(cmd1);

  if(ser.find("Error")){
    //Serial.println("AT+CIPSTART error");
    return;
  }

  String getStr1 = "GET /update?api_key=";
  getStr1 += apiKey;
  getStr1 +="&field1=";
  getStr1 += String(stri);
  getStr1 += "\r\n\r\n";
// send data length
  cmd1 = "AT+CIPSEND=";
  cmd1 += String(getStr1.length());
  ser.println(cmd1);


   if(ser.find(">")){
    ser.print(getStr1);
  }
   else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
  }
 
}