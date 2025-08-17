#include <WiFi.h>    
#include <HTTPClient.h>
#include <UrlEncode.h>

const char* ssid = "";
const char* password = "";

long messageTime= 0;
float LDR= 0;

// +international_country_code + phone number
// Portugal +351, example: 351912345678
// Brazil +55, example: 551191234567 (skip the first 9 in front of the number)
String phoneNumber = "";
String apiKey = "";

void sendMessage(String message) {
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + 
               "&text=" + urlEncode(message) + 
               "&apikey=" + apiKey;    

  HTTPClient http;
  http.begin(url);

  // Send HTTP GET request
  int httpResponseCode = http.GET();

  if (httpResponseCode == 200) {
    Serial.println("Message sent successfully");
  } else {
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}


void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  // Send Message to WhatsAPP
  sendMessageFunction();
}

void loop() {

  
  if(millis() - messageTime > 600000){
    messageTime= millis();
    sendMessageFunction();
  }
  
}
void sendMessageFunction(void){
  LDR= analogRead(D0);
  sendMessage("Light level= " + String(LDR));
}