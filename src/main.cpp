#include <M5Stack.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

SoftwareSerial Grove(22, 21);     // define rx/tx connecting to the UnitV2 camera
                                  // SoftwareSerial(rxPin, txPin, inverse_logic)

int x;
int y;
long k;
char data[50];

void setup() {
  M5.begin();
  M5.Lcd.setCursor(20, 40);
  M5.Lcd.setTextSize(2);
  Serial.begin(115200);
  Grove.begin(115200);
  M5.Lcd.print("--initialized--");      // display M5 Lcd message
  Serial.print("---initialized---");    // output serial line
}


void loop_(){

  if(Grove.available()) {
    String recvStr = Grove.readStringUntil('\n');
    if(recvStr[0] == '{'){
      Serial.print(recvStr);
    }
  }
}

void readJSON(void){
  String recvStr = Grove.readStringUntil('\n');
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
  if(Grove.available()) {
    readJSON();
    sprintf(data,"x = %d , y = %d , k = %ld",x,y,k);
    Serial.println(data);
  }
}

