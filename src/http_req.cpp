#include <ai_camera.hpp>

//
// reference : https://itbulog.com/index.php/2021/09/25/m5stack_09_http/
//

const char ssid[] = "M5UV2_68f7";       // UnitV2 AP ssid
const char password[] = "12345678";     // pw


void http_setup() {
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500); 
    Serial.print("."); 
  }

  HTTPClient http;                          // define Http client
  http.begin("http://10.254.239.1");        // connect to the UnitV2
  int httpCode = http.GET();                // Get request

  if(httpCode > 0) {
    Serial.printf("Response Code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
    //  String payload = http.getString();
    //  Serial.printf("Response Payload: %s\n", payload.c_str());
    }
  } else {
    Serial.printf("Error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();

}