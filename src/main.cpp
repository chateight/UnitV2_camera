#include <ai_camera.hpp>


SoftwareSerial Grove(22, 21);     // define rx/tx connecting to the UnitV2 camera
                                  // SoftwareSerial(rxPin, txPin, inverse_logic)
float x;
String f_id;    // face_id
int y;
long k;
char data[1000];

void setup() {
  M5.begin();
  M5.Lcd.setCursor(20, 20);
  M5.Lcd.setTextSize(2);
  M5.Speaker.begin(); 
  Serial.begin(115200);
  Grove.begin(115200);
  M5.Lcd.print("--init sequence start--");
  http_setup();       // connect to the UnitV2 camera via wi-fi AP
  M5.Lcd.setCursor(20, 40);
  M5.Lcd.print("--initialized--");      // display M5 Lcd message
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
  StaticJsonDocument<1024> doc;                   // allocates the memory pool in the stack memory
  DeserializationError error = deserializeJson(doc, recvStr);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  x = doc["face"][0]["match_prob"];
  String id = doc["face"][0]["name"];
  f_id = id;
  Serial.println(f_id);
}

void loop(){
  M5.Lcd.setCursor(20, 70);
  //M5.Lcd.print("                          ");
  M5.Speaker.mute();
  if(Grove.available()) {
    readJSON();
    Serial.println(x);
    if (x > 0.7f)
    {
      M5.Lcd.setCursor(20, 70);
      M5.Lcd.printf("Face ID : %s", f_id);
      M5.Speaker.setVolume(3);
      M5.Speaker.beep();
      delay(200);     
    }
  }
}