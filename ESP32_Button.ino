// 1. esp32連到localhost:8080
// 2. esp32按鈕按下傳送訊號到localhost:8080

#include "WiFi.h";
#include <HTTPClient.h>;

const char* ssid = "HOLIO";
const char* password = "29183755";
const char* serverIP = "192.168.0.185";
const int serverPort = 8080;

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.println("Connecting to WiFi");
    }
  Serial.println("Connected to WiFi");

}

void loop() {
  /*
  WiFiClient client;
   if (client.connect(serverIP,serverPort)) {
    Serial.println("Connected to server");
   
  } else {
    Serial.println("Connection failed");
  }
  
  delay(500); 
  */
  
  HTTPClient http;
  uint16_t port = 8080;
  String uri = "/";
  bool begined = http.begin("192.168.0.185", port);
  int httpCode = http.GET();
  Serial.println("httpCode: " + httpCode);

  if(httpCode > 0)
  {
    if(httpCode == HTTP_CODE_OK)
    {
      String payload = http.getString();
      Serial.print(payload);
      }
  }else
  {
    String error = http.errorToString(httpCode);
    Serial.println("error:" + error);
  }
}
