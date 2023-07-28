#include <ESP8266WiFi.h> //Incluimos la librería para del WiFi
 
//Credenciales del WiFi
const char* ssid = "CeDralaNET";
const char* password = "Amelia05";
const char* host = "192.168.1.120";
String MAC="",todo="";
int RELAY1=0,RELAY2=0,RELAY3=0,RELAY4=0,RELAY5=0,AUX=0;
 
int ledPin = D0; // D0 is the LEDBUILDIN (Active LOW)
WiFiServer server(80);
 
void MacAddress() {
  // the MAC address of your Wifi shield
  byte mac[6];
  // print your MAC address:
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  if(mac[5]==0)MAC+="00";
  else MAC+=String(mac[5],HEX);
  MAC+=":";
  if(mac[4]==0)MAC+="00";
  else MAC+=String(mac[4],HEX);
  MAC+=":";
  if(mac[3]==0)MAC+="00";
  else MAC+=String(mac[3],HEX);
  MAC+=":";
  if(mac[2]==0)MAC+="00";
  else MAC+=String(mac[2],HEX);
  MAC+=":";
  if(mac[1]==0)MAC+="00";
  else MAC+=String(mac[1],HEX);
  MAC+=":";
  if(mac[0]==0)MAC+="00";
  else MAC+=String(mac[0],HEX);
  Serial.print(MAC);
}
void setup() {
  Serial.begin(115200); //Inicio el puerto serie 
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
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
  Serial.println("");
  Serial.println("WiFi conectado");
 
  // Inicializo el servidor
  server.begin();
  Serial.println("Servidor iniciado");
 
  // Muestro la IP local asignada. URL del servidor
  Serial.print("Usa esta URL para conectar al servidor: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  MacAddress();
 Serial.println();
 Serial.println();
}
 
void loop() {
  // Compruebo si hay un cliente disponible (una petición)
  WiFiClient client = server.available();
  if (!client) {
    return; // En caso de no haber un cliente, no hago nada
  }
 
  // Espero hasta que el cliente realice una petición
  Serial.println("¡Nuevo cliente!");
  while(!client.available()){
    delay(1);
  }
 
  // Leo la primera linea de la petición del cliente
  String request = client.readStringUntil('\r'); // Leo hasta retorno de carro
  Serial.println(request); //Imprimo la petición
  client.flush(); //Limpio el buffer
 
  // Interpreto lo que he recibido
 
  int value = LOW;
  if (request.indexOf("/RELAY1=true") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nRELAY1=ON</html>\n");
   RELAY1=1;
   AUX=1;
  
  }
  
  if (request.indexOf("/reboot") != -1)  {
    digitalWrite(ledPin, LOW);
    delay(3000);
    digitalWrite(ledPin, HIGH);
    value = HIGH;
    todo="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nDevice Rebooted";
   // todo+=MAC;
    todo+="</html>\n";
    client.print(todo);
  }
  
    if(AUX==1){
        Serial.print("ESTADO DEL Rele1=");
          Serial.println(RELAY1);
       Serial.print("ESTADO DEL Rele2=");
          Serial.println(RELAY2);
       Serial.print("ESTADO DEL Rele3=");
          Serial.println(RELAY3);
       Serial.print("ESTADO DEL Rele4=");
          Serial.println(RELAY4);
       Serial.print("ESTADO DEL Rele5=");
          Serial.println(RELAY5);
  delay(100);
          Serial.print("connecting to ");
  Serial.println(host);

    WiFiClient client;
  const int httpPort = 80;
  delay(10);
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URL for the request
  String url = "/releremoto/dispos.php?MAC=";
  String key = "?SERIE=1234";
  String dato1 = "&R1=";
  String dato2 = "&R2=";

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
/*  client.print(String("GET ") + url + key + dato1 + RELAY1 + dato2 + RELAY2 + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");*/
    client.print(String("GET ") + url +  MAC + " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" +
    "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
      AUX=0;
      }
 
  delay(1);
  Serial.println("Cliente desconectado"); // Nos desconectamos del cliente
  Serial.println("");
   Serial.println("");
 
}
