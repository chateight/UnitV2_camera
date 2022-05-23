#include <M5Stack.h>

void setup() {
  M5.begin();

  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 33, 32);  //33,32はそれぞれTX,RX。
}

void loop(){

  if(Serial2.available()) {
    String recvStr = Serial2.readStringUntil('\n');
    if(recvStr[0] == '{'){
      Serial.print(recvStr);
    }
  }
}

