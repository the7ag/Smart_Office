#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "6aWTWokE6MrEW6faUZn7hsHcRbvRD7rY";
char ssid[] = "Noha's iPhone";
char pass[] = "12345678";

int i = 0;
String x[5];
String buff;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Blynk.begin();
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  //communication with arduino

  Blynk.run();

  if (Serial.available() > 0) {
    buff = Serial.read();
    if (buff == "Z") {
      x[0] = "2";
      x[1] = "3";
    }
    if (buff == "z") {
      x[0] = "2";
      x[1] = "4";
    }
    if (buff == "X") {
      x[0] = "2";
      x[1] = "5";
    }
    if (buff == "x") {
      x[0] = "2";
      x[1] = "6";
    }
    if (buff >= "0" && buff <= "9") {
      x[2] = buff;
    }
    if (buff == "A") {
      x[3] = "1";
    }
    if (buff == "a") {
      x[3] = "0";
    }
    if (buff == "B") {
      x[4] = "1";
    }
    if (buff == "b") {
      x[4] = "0";
    }
  }
  ///dealing with Blynk interface
  if (x[3] == "1") {
    Blynk.virtualWrite(V1, "Desk A is available");
    Blynk.setProperty(V1, "color", "#00FF00");
  }

  else {
    Blynk.virtualWrite(V1, "Desk A is unavailable");
    Blynk.setProperty(V1, "color", "#FF0000");
  }

  if (x[4] == "1") {
    Blynk.virtualWrite(V3, "Desk B is available");
    Blynk.setProperty(V3, "color", "#00FF00");
  } else {
    Blynk.virtualWrite(V3, "Desk B is unavailable");
    Blynk.setProperty(V3, "color", "#FF0000");
  }

  Blynk.virtualWrite(V2, x[0] + x[1]);
  Blynk.virtualWrite(V5, x[2]);
}
