#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "ngadim1n";
const char* password = "12345678";
int led1 = 5;
int led2 = 4;
int led3 = 0;
int led4 = 2;

#define ON HIGH
#define OFF LOW

void setup() {
  Serial.begin(115200);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++) {
    if(data.charAt(i)==separator || i==maxIndex) {
      found++;
      strIndex[0] = strIndex[1]+1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  String foundData = found>index ? data.substring(strIndex[0], strIndex[1]) : "";
  return foundData;
}

void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, "http://192.168.196.150/eslolin/config.php"); // Perubahan pada baris ini
    int httpCode = http.GET();
    
    if(httpCode > 0) {
      String status = http.getString();

      Serial.print("LED 1 --> ");
      String nilai1 = getValue(status, ',', 0);
      Serial.println(nilai1);
      
      Serial.print("LED 2 --> ");
      String nilai2 = getValue(status, ',', 1);
      Serial.println(nilai2);
      
      Serial.print("LED 3 --> ");
      String nilai3 = getValue(status, ',', 2);
      Serial.println(nilai3);
      
      Serial.print("LED 4 --> ");
      String nilai4 = getValue(status, ',', 3);
      Serial.println(nilai4);
      Serial.println("------------------------");
      
      digitalWrite(led1, nilai1 == "1" ? OFF : ON);
      digitalWrite(led2, nilai2 == "1" ? OFF : ON);
      digitalWrite(led3, nilai3 == "1" ? OFF : ON);
      digitalWrite(led4, nilai4 == "1" ? OFF : ON);
    }
    http.end();
  } else {
    Serial.println("Delay..."); 
  }
  delay(500); 
}