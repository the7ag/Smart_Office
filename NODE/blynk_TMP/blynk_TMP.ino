#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "6aWTWokE6MrEW6faUZn7hsHcRbvRD7rY";
char ssid[] = "WE_822896";
char pass[] = "95552132";


//char buff[] = "T=25N=08a=0b=0c=1";
String klm[10];

//BLYNK_WRITE(V0) {
 // digitalWrite(D0, param.asInt());
//}

 int i=0;
 String x[5];
 String buff;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 // Blynk.begin();
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  /*int j = 0;
  for (int i = 0; buff[i] != '\0'; i++) {  //  2 3_ 6 7_ 10 _13_ 16
    if (isdigit(buff[i])) {
      klm[j] = buff[i];
      j++;
    }
    Serial.print(buff[i]);
  }
  Serial.println("");
  klm[j] = '\0';
  for (int k = 0; k <= 9; k++)
    Serial.print(klm[k]);*/
}

void loop() {
//communication with arduino

Blynk.run();


if(Serial.available()>0){
  //x[i]=Serial.read();
  //i=(i+1)%16;
  buff=Serial.read();
  if(buff=="Z")
  {
    x[0]="2";
    x[1]="3";
  }
  if (buff=="z") {
    x[0]="2";
    x[1]="4";
  }
  if (buff=="X") {
    x[0]="2";
    x[1]="5";
  }
  if (buff=="x") {
    x[0]="2";
    x[1]="6";
  }
  if (buff>="0"&&buff<="9") {
  x[2]=buff;
  }
  if (buff=="A") {
  x[3]="1";
  }
   if (buff=="a") {
  x[3]="0";
  }
   if (buff=="B") {
  x[4]="1";
  }
  if(buff=="b")
  {
    x[4]="0";
  }
}
for(int i=0;i<5;i++)
Serial.println(x[i]);


///dealing with Blynk interface
  if (x[3] == "1"){
     Blynk.virtualWrite(V1, "Desk A is available");
    Blynk.setProperty(V1, "color", "#FF0000");
  }
   
  else{
    Blynk.virtualWrite(V1, "Desk A is unavailable");
    Blynk.setProperty(V1, "color", "#00FF00");
  }
    
  if (x[4] == "1"){
    Blynk.virtualWrite(V3, "Desk B is available");
    Blynk.setProperty(V3, "color", "#FF0000");
  }
  else{
Blynk.virtualWrite(V3, "Desk B is unavailable");
Blynk.setProperty(V3, "color", "#00FF00");
  }
    

  Blynk.virtualWrite(V2, x[0] + x[1]);
  Blynk.virtualWrite(V5, x[2]);
}
