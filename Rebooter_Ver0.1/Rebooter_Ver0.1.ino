#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <EEPROM.h>

const int SerialID = 000001;

const char* Conf_ssid = "Rebooter_000001";
IPAddress Config_IP(192,168,4,1);

const char* ssid = "ye_EXT";
const char* password = "Amelia05";
IPAddress local_IP(192,168,1,200);

String MAC="",todo="";
const int buttonPin = 4;     // the number of the pushbutton pin
const int ledPin =  D4;      // the number of the LED pin

String pral = "<html>"
              "<meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>"
              "<title>WIFI CONFIG</title> <style type='text/css'> body,td,th { color: #036; } body { background-color: #999; } </style> </head>"
              "<body> "
              "<h4>Pruebas ESP8266, WIFI, Formulario</h4>"
              "<h4>Fingers 2.0</h4><br>"
              "<h1>CONFIGURACIÓN</h1><br>"
              "<form action='config' method='get' target='pantalla'>"
              "<fieldset align='left' style='border-style:solid; border-color:#336666; width:200px; height:180px; padding:10px; margin: 5px;'>"
              "<legend><strong>Configurar WI-FI</strong></legend>"
              "SSID: <br> <input name='ssid' type='text' size='15'/> <br><br>"
              "PASSWORD: <br> <input name='pass' type='password' size='15'/> <br><br>"
              "<input type='submit' value='Conexion' />"
              "</fieldset>"
              "</form>"
              "<iframe id='pantalla' name='pantalla' src='' width=900px height=400px frameborder='0' scrolling='no'></iframe>"
              "</body>"
              "</html>";


// variables:
int buttonState = 0;         // variable for reading the pushbutton status
int MODE = 0;                // variable for define the operation mode
boolean c=1;

ESP8266WebServer server(80);
WiFiServer server2(80);

void cambia(){
   c=!c;
   digitalWrite(ledPin, c);
   if (c==0)server.send(200, "text/html", "<h4>ENCENDIDO</h4>");
   else server.send(200, "text/html", "<h4>APAGADO</h4>");
   }

void setup() 
  {
  Serial.begin(115200);
  EEPROM.begin(4096);
  pinMode(ledPin, OUTPUT);   // initialize the LED pin as an output:
  pinMode(buttonPin, INPUT); // initialize the pushbutton pin as an input:
  digitalWrite(ledPin, LOW);
  buttonState = digitalRead(buttonPin);
  if( buttonState == 1 )
    {
    MODE = 0;
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
      {
      delay(500);
      Serial.print(".");
      }
    Serial.println("");
    Serial.println("WiFi conectado");
     // Inicializo el servidor
    server2.begin();
    Serial.println("Servidor iniciado");
 
    // Muestro la IP local asignada. URL del servidor
    Serial.print("Usa esta URL para conectar al servidor: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
    }
  else 
    {
    MODE = 1;
    WiFi.softAP(Conf_ssid);      //SSID por defecto
    server.on("/", []() { server.send(200, "text/html", pral);});
    server.on("/config", cambia);
    server.begin();
    }
  
  // pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, HIGH);
 
  }


void loop() 
  {
  //buttonState = digitalRead(buttonPin); // read the state of the pushbutton value:  
  if (MODE == 0)    // Active the Rebooter Mode
    {          
    //server.handleClient();
    WiFiClient client = server2.available();
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
  
  if (request.indexOf("/reboot") != -1)  {
    digitalWrite(ledPin, LOW);
    delay(3000);
    digitalWrite(ledPin, HIGH);
    todo="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nDevice Rebooted";
    todo+="</html>\n";
    client.print(todo);
  }

  delay(1);
  Serial.println("Cliente desconectado"); // Nos desconectamos del cliente
  Serial.println("");
   Serial.println("");
 
    digitalWrite(ledPin, HIGH); // turn LED on:
    }
  if (MODE == 1)  // Active the Configuration Mode
    {
    server.handleClient();
    //digitalWrite(ledPin, LOW);   // turn LED off:
    }
  }
