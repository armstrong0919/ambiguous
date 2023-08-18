//V 1. esp32連到Server
//V 2. esp32 send message to Server
//V 3. esp32按鈕持續按著
//  4. esp32按鈕結束傳到Server
//  5. esp32開啟錄音功能
//  6. 

#include "WiFi.h";
#include <HTTPClient.h>;

#define LED_BUILTIN  2

const char* ssid = "HITRON-ZHEN"; //HOLIO
const char* password = "l0988184910"; //29183755
const char* serverIP = "192.168.0.12";
const int serverPort = 8080;
const int LEDPin = 2;
const int BTNPin = 4;


void setup() {
  Serial.begin(115200);
  pinMode(BTNPin, INPUT_PULLUP);
  pinMode(LEDPin, OUTPUT);
  
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    //Serial.println("Try to Connecting to WiFi");
    }
  //Serial.println("Connected to WiFi");

}

void loop() {  


  //Detect 
  int buttonState = digitalRead(BTNPin); // 0 = low ; 1 = high

  
  if (buttonState == LOW)
  {
      // LED
      digitalWrite(LEDPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      Serial.print("click\n");

      // Server
      HTTPClient http;
      uint16_t port = 8080;
      bool begined = http.begin("192.168.0.12", port);
      //Server - POST
      String payload = "i'm big! i'm brave! i'm beautiful!";
      int httpResponseCode = http.POST(payload);
      if(httpResponseCode > 0)
      {
        String response = http.getString();
        Serial.println("HTTP Response: " + response);
      }else
      {
        Serial.println("Cannot connect to Server");
      }
  }else if (buttonState == HIGH)
  {
    // LED
    digitalWrite(LEDPin, LOW);   // turn the LED on (HIGH is the voltage level)
    Serial.print("UNclick\n");
   }
    
  /*  
  HTTPClient http;
  uint16_t port = 8080;
  bool begined = http.begin("192.168.0.12", port);
  //POST
  String payload = "i'm big! i'm brave! i'm beautiful!";
  int httpResponseCode = http.POST(payload);
  if(httpResponseCode > 0)
  {
    Serial.print(payload);
    String response = http.getString();
    //Serial.println("HTTP Response: " + response);
  }*/
  
  /* GET
  int httpCode = http.GET();
  if(httpCode > 0)
  {
    if(httpCode == HTTP_CODE_OK)
    {
      String payload = http.getString();
      Serial.print(payload);
      //Serial.print("Successfully connect to server");
      }
  }
  else
  {
    String error = http.errorToString(httpCode);
    //Serial.println("error:" + error);
  }
  */ 
}
