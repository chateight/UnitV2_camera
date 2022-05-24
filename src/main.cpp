#include <M5Stack.h>
#include <ArduinoJson.h>

int x;
int y;
long k;
char data[50];

void setup() {
  M5.begin();
  M5.Lcd.setCursor(20, 40);
  M5.Lcd.setTextSize(2);
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 32, 33);
  M5.Lcd.print("--initialized--");      // display M5 Lcd message
  Serial.print("---initialized---");    // output serial line
}

void readJSON(void){
  String recvStr = Serial2.readStringUntil('\n');
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
  if(Serial2.available()) {
    readJSON();
    sprintf(data,"x = %d , y = %d , k = %ld",x,y,k);
    Serial.println(data);
  }
}

