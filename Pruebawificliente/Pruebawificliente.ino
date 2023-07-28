#include <ESP8266WiFi.h> //Incluimos la librería para del WiFi
 
//Credenciales del WiFi
const char* ssid = "ye_EXT";
const char* password = "Amelia05";



void setup() {
  Serial.begin(115200); //Inicio el puerto serie 
  delay(10);
 
// Conecto con la red WiFi en modo estación (STA)
  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print(WiFi.localIP());
  Serial.println("/");
}
 
void loop() {}
