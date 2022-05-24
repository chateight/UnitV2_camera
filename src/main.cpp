#include <M5Stack.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

SoftwareSerial GroveA(21, 22);

int x;
int y;
long k;
char data[50];

void setup() {
  M5.begin();
  M5.Lcd.setCursor(20, 40);
  M5.Lcd.setTextSize(2);
  Serial.begin(115200);
  GroveA.begin(115200);
  M5.Lcd.print("--initialized--");      // display M5 Lcd message
  Serial.print("---initialized---");    // output serial line
}

void readJSON(void){
  String recvStr = GroveA.readStringUntil('\n');
  StaticJsonDocument<128> doc;
  DeserializationError error = deserializeJson(doc, recvStr);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  x = doc["x"];
  y = doc["y"];
  k = doc["k"];
  const char* running = doc["running"]; // "Lane Line Tracker"  
}

void loop(){
  if(GroveA.available()) {
    readJSON();
    sprintf(data,"x = %d , y = %d , k = %ld",x,y,k);
    Serial.println(data);
  }
}

