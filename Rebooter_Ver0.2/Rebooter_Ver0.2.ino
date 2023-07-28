#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <EEPROM.h>

const int SerialID = 000001;

const char* Conf_ssid = "Rebooter_000001";
IPAddress Config_IP(192,168,4,1);

const char* ssid2 = "ye_EXT";
const char* password2 = "Amelia05";
IPAddress local(192, 168, 0, 140);
IPAddress localip(192,168,0,200);     
IPAddress Gateway(192,168,0,1);   
IPAddress Subnet(255,255,255,0); 

String MAC="",todo="";

const int buttonPin = 9;     // the number of the pushbutton pin
const int ledPin =  D4;      // the number of the LED pin
const int Rst1 =  D0;
const int Rst2 =  D1;
const int Rst3 =  D2;
const int Rst4 =  D3;
const int Rst5 =  D5;
const int Rst6 =  D6;
const int Rst7 =  D7;
const int Rst8 =  D8;

String pral = "<html>"
  "<head>"
    "<meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>"
    "<title>Rebooter_000001</title>" 
    "<style type='text/css'> body,td,th { color: #036; } body { background-color: #999; overflow-x: hidden;} </style>" 
    "<script type='text/javascript'>"
      "function showContent()" 
      "{"
        "element = document.getElementById('form3');"
        "check = document.getElementById('Act1');"
        "if (check.checked)" 
        "{"
          "element.style.display='block';"
       "}"
       "else"
        "{"
          "element.style.display='none';"
        "}"
      "}"
      "function validityMessage(index)"
      "{"   
        "if (index == 1) ssid.setCustomValidity('Enter SSID');"
        "if (index == 2) pass.setCustomValidity('Enter your Password');"
        "if (index == 3) IP.setCustomValidity('Enter a valid IP address');"
        "if (index == 4) gateway.setCustomValidity('Enter a valid Gateway');"
        "if (index == 5)  subnet.setCustomValidity('Enter a valid Netmask');"
        "if (index == 10) ssid.setCustomValidity('');"
        "if (index == 20) pass.setCustomValidity('');"
        "if (index == 30) IP.setCustomValidity('');"
        "if (index == 40) gateway.setCustomValidity('');"
        "if (index == 50)  subnet.setCustomValidity('');"
      "}"
      "function enableWd(index)"
      "{"   
        "if (document.getElementById('Enable' + index).checked)" 
          "document.getElementById('IP' + index).required = true;"
        "else"
          "document.getElementById('IP' + index).required = false;"
      "}"
    "</script>"
  "</head>"
  "<body>" 
    "<h2>Rebooter Setting Interface</h2>"
    "<fieldset align='left' style='border-style:solid; border-color:#336666; width:200px; height:10px; padding:10px; margin: 5px; float: left;'>"
      "<script>document.write('S/N:000001');</script>"
    "</fieldset> <br><br>"
    "<h4></h4>"
    "<form action='config' method='get' target='pantalla' style='float: left'>"
      "<fieldset align='left' style='border-style:solid; border-color:#336666; width:200px; height:330px; padding:10px; margin: 5px;'>"
        "<legend><strong>WIFI Settings</strong></legend>"
        "SSID: <br> <input name='ssid' id='ssid' type='text' size='15' required oninvalid='validityMessage(1)' oninput='validityMessage(10)' /> <br><br>"
        "PASSWORD: <br> <input name='pass'id='pass' type='password' size='15' required  oninvalid='validityMessage(2)' oninput='validityMessage(20)'/> <br><br>"
        "IP: <br> <input name='IP' id='IP' type='text' size='15' required oninvalid='validityMessage(3)' oninput='validityMessage(30)' placeholder='192.168.1.100' pattern='[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]'/> <br><br>"
        "GATEWAY: <br> <input name='gateway' id='gateway' type='text' size='15' required oninvalid='validityMessage(4)' oninput='validityMessage(40)' placeholder='192.168.1.1' pattern='[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]'/> <br><br>"
        "SUBNET: <br> <input name='subnet' id='subnet' type='text' size='15' required oninvalid='validityMessage(5)' oninput='validityMessage(50)' placeholder='255.255.255.0' pattern='[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]'/> <br><br>"
        "<input type='submit' value='Connect' />"
      "</fieldset>"
    "</form>"
    "<form action='config' method='get' target='pantalla' style='float: left'>"
      "<fieldset align='left' style='border-style:solid; border-color:#336666; width:200px; height:330px; padding:10px; margin: 5px;'>"
        "<legend><strong>Control</strong></legend>"
        "ID: <br> <input name='ID' type='text' size='15'/> <br><br>"
        "<input name='ActivWD' type='checkbox' id='Act1' size='15' onchange='javascript:showContent()'/> Watchdog <br><br>"
        "<input type='submit' value='Save' /><br>"
        "<fieldset align='center' style='border-style:solid; border-color:#336666; width:160px; height:160px; padding:10px; margin: 5px;'>"
            "<legend><strong>Test Buttons</strong></legend>"
            "<input type='button' value='Reboot 1' />"
            "<input type='button' value='Reboot 5' /><br><br>"
            "<input type='button' value='Reboot 2' />"
            "<input type='button' value='Reboot 6' /><br><br>"
            "<input type='button' value='Reboot 3' />"
            "<input type='button' value='Reboot 7' /><br><br>"
            "<input type='button' value='Reboot 4' />"
            "<input type='button' value='Reboot 8' />"
        "</fieldset>"
      "</fieldset>"
    "</form>"
    "<form action='config' name='formWD' id='form3' method='get' target='pantalla' style='float: left; display: none; '>"
      "<fieldset align='left' style='border-style:solid; border-color:#336666; width:200px; height:330px; padding:10px; margin: 5px;'>"
        "<legend><strong>Watchdog</strong></legend>"
        "<br>"
        "<table>"
          "<tr>"
            "<td></td>"
            "<td><strong>Machine IP</strong></td>"
            "<td><strong>Enable</strong></td>"
          "</tr>"
          "<tr>"
            "<td>1</td>"
            "<td><input name='IP1' id='IP1' type='text' size='15' title='Enter IP address format' pattern='[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]' /></td>"
            "<td><input type='checkbox' value='Enable1' id='Enable1' onchange='enableWd(1);' /></td>"
          "</tr>"
          "<tr>"
            "<td>2</td>"
            "<td><input name='IP2' id='IP2' type='text' size='15' title='Enter IP address format' pattern='[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]' /></td>"
            "<td><input type='checkbox' value='Enable2' id='Enable2' onchange='enableWd(2);'/></td>"
          "</tr>"
          "<tr>"
            "<td>3</td>"
            "<td><input name='IP3' id='IP3' type='text' size='15' title='Enter IP address format' pattern='[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]' /></td>"
            "<td><input type='checkbox' value='Enable3' id='Enable3' onchange='enableWd(3);'/></td>"
          "</tr>"
          "<tr>"
            "<td>4</td>"
            "<td><input name='IP4' id='IP4' type='text' size='15' title='Enter IP address format' pattern='[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]' /></td>"
            "<td><input type='checkbox' value='Enable4' id='Enable4' onchange='enableWd(4);'/></td>"
          "</tr>"
          "<tr>"
            "<td>5</td>"
            "<td><input name='IP5' id='IP5' type='text' size='15' title='Enter IP address format' pattern='[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]' /></td>"
            "<td><input type='checkbox' value='Enable5' id='Enable5' onchange='enableWd(5);'/></td>"
          "</tr>"
          "<tr>"
            "<td>6</td>"
            "<td><input name='IP6' id='IP6' type='text' size='15' title='Enter IP address format' pattern='[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]' /></td>"
            "<td><input type='checkbox' value='Enable6' id='Enable6' onchange='enableWd(6);'/></td>"
          "</tr>"
          "<tr>"
            "<td>7</td>"
            "<td><input name='IP7' id='IP7' type='text' size='15' title='Enter IP address format' pattern='[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]' /></td>"
            "<td><input type='checkbox' value='Enable7' id='Enable7' onchange='enableWd(7);'/></td>"
          "</tr>"
          "<tr>"
            "<td>8</td>"
            "<td><input name='IP8' id='IP8' type='text' size='15' title='Enter IP address format' pattern='[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]\\.[0-2]?[0-9]?[0-9]' /></td>"
            "<td><input type='checkbox' value='Enable8' id='Enable8' onchange='enableWd(8);'/></td>"
          "</tr>"
        "</table><br><br>"
        "<input type='submit' value='Save' />"
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

char ssid[20];
char pass[20];
String ssid_leido;
String pass_leido;
int ssid_tamano = 0;
int pass_tamano = 0;
char ip[20];
char id[20];
String ip_leido;
String id_leido;
int ip_tamano = 0;
int id_tamano = 0;
char gateway[20];
char subnet[20];
String gateway_leido;
String subnet_leido;
int gateway_tamano = 0;
int subnet_tamano = 0;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
String arregla_simbolos(String a) {
  a.replace("%C3%A1", "á");
  a.replace("%C3%A9", "é");
  a.replace("%C3%A", "i");
  a.replace("%C3%B3", "ó");
  a.replace("%C3%BA", "ú");
  a.replace("%21", "!");
  a.replace("%23", "#");
  a.replace("%24", "$");
  a.replace("%25", "%");
  a.replace("%26", "&");
  a.replace("%27", "/");
  a.replace("%28", "(");
  a.replace("%29", ")");
  a.replace("%3D", "=");
  a.replace("%3F", "?");
  a.replace("%27", "'");
  a.replace("%C2%BF", "¿");
  a.replace("%C2%A1", "¡");
  a.replace("%C3%B1", "ñ");
  a.replace("%C3%91", "Ñ");
  a.replace("+", " ");
  a.replace("%2B", "+");
  a.replace("%22", "\"");
  return a;
}
//*******  G R A B A R  EN LA  E E P R O M  ***********
void graba(int addr, String a) {
  int tamano = (a.length() + 1);
  Serial.print(tamano);
  char inchar[30];    //'30' Tamaño maximo del string
  a.toCharArray(inchar, tamano);
  EEPROM.write(addr, tamano);
  for (int i = 0; i < tamano; i++) {
    addr++;
    EEPROM.write(addr, inchar[i]);
  }
  EEPROM.commit();
}

//*******  L E E R   EN LA  E E P R O M    **************
String lee(int addr) {
  String nuevoString;
  int valor;
  int tamano = EEPROM.read(addr);
  for (int i = 0; i < tamano; i++) {
    addr++;
    valor = EEPROM.read(addr);
    nuevoString += (char)valor;
  }
  return nuevoString;
}
//**** CONFIGURACION WIFI  *******
void wifi_conf() {
  int cuenta = 0;

  String getssid = server.arg("ssid"); //Recibimos los valores que envia por GET el formulario web
  String getpass = server.arg("pass");
  String getip = server.arg("IP");
  String getid = server.arg("ID");
  String getgateway = server.arg("gateway");
  String getsubnet = server.arg("subnet");
  
  getssid = arregla_simbolos(getssid); //Reemplazamos los simbolos que aparecen cun UTF8 por el simbolo correcto
  getpass = arregla_simbolos(getpass);
  getip = arregla_simbolos(getip);
  getid = arregla_simbolos(getid);
  getgateway = arregla_simbolos(getgateway);
  getsubnet = arregla_simbolos(getsubnet);

  ssid_tamano = getssid.length() + 1;  //Calculamos la cantidad de caracteres que tiene el ssid y la clave
  pass_tamano = getpass.length() + 1;
  ip_tamano = getip.length() + 1;
  id_tamano = getid.length() + 1;
  gateway_tamano = getgateway.length() + 1;
  subnet_tamano = getsubnet.length() + 1;

  getssid.toCharArray(ssid, ssid_tamano); //Transformamos el string en un char array ya que es lo que nos pide WIFI.begin()
  getpass.toCharArray(pass, pass_tamano);
  getip.toCharArray(ip, ip_tamano);
  getid.toCharArray(id, id_tamano);
  getgateway.toCharArray(gateway, gateway_tamano);
  getsubnet.toCharArray(subnet, subnet_tamano);

  local.fromString(getip);
  Gateway.fromString(getgateway);
  Subnet.fromString(getsubnet);
  
  Serial.println(ssid);     //para depuracion
  Serial.println(pass);
  Serial.println(ip);
  Serial.println(id);
  Serial.println(local);

  //WiFi.mode(WIFI_AP_STA);
  WiFi.config(local, Gateway, Subnet);
  //WiFi.begin(ssid, password);
  //WiFi.config(local);
  WiFi.begin(ssid, pass);     //Intentamos conectar
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    cuenta++;
    if (cuenta > 20) {
      graba(70, "noconfigurado");
      server.send(200, "text/html", String("<h2>No se pudo realizar la conexion<br>no se guardaron los datos.</h2>"));
      return;
    }
  }
  Serial.print(WiFi.localIP());
  graba(70, "configurado");
  graba(1, getssid);
  graba(30, getpass);
  graba(90, getip);
  graba(110, getid);
  graba(140, getgateway);
  graba(170, getsubnet);
  server.send(200, "text/html", String("<h2>Conexion exitosa a: "
                                       + getssid + "<br> El pass ingresado es: " + getpass + "<br>Datos correctamente guardados."));

}
void intento_conexion() {
  if (lee(70).equals("configurado")) {
    ssid_leido = lee(1);      //leemos ssid y password
    pass_leido = lee(30);
    ip_leido = lee(90);      
    id_leido = lee(110);
    gateway_leido = lee(140);
    subnet_leido = lee(170);

    Serial.println(ssid_leido);  //Para depuracion
    Serial.println(pass_leido);
    Serial.println(ip_leido);
    Serial.println(id_leido);
    Serial.println(gateway_leido);
    Serial.println(subnet_leido);

    ssid_tamano = ssid_leido.length() + 1;  //Calculamos la cantidad de caracteres que tiene el ssid y la clave
    pass_tamano = pass_leido.length() + 1;
    ip_tamano = ip_leido.length() + 1;
    id_tamano = id_leido.length() + 1;
    gateway_tamano = gateway_leido.length() + 1;
    subnet_tamano = subnet_leido.length() + 1;

    ssid_leido.toCharArray(ssid, ssid_tamano); //Transf. el String en un char array ya que es lo que nos pide WiFi.begin()
    pass_leido.toCharArray(pass, pass_tamano);
    ip_leido.toCharArray(ip, ip_tamano);
    id_leido.toCharArray(id, id_tamano);
    gateway_leido.toCharArray(gateway, gateway_tamano);
    subnet_leido.toCharArray(subnet, subnet_tamano);
    local.fromString(ip_leido);
    Gateway.fromString(gateway_leido);
    Subnet.fromString(subnet_leido);
    int cuenta = 0;
    
    //WiFi.mode(WIFI_STA);
    WiFi.config(local, Gateway, Subnet);
    //WiFi.config(local, gateway, subnet);
    WiFi.begin(ssid, pass);      //Intentamos conectar
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      cuenta++;
      if (cuenta > 20) {
        Serial.println("Fallo al conectar");
        return;
      }
    }
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Conexion exitosa a: ");
    Serial.println(ssid);
    Serial.println(WiFi.localIP());
  }
}
/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
 
void handleRoot() {
  server.send(200, "text/html", pral);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
  pinMode(ledPin, OUTPUT);
  pinMode(Rst1, OUTPUT);// initialize the LED pin as an output:
  pinMode(buttonPin, INPUT); // initialize the pushbutton pin as an input:
  digitalWrite(ledPin, HIGH);
  digitalWrite(Rst1, LOW);
  buttonState = digitalRead(buttonPin);
  if( buttonState == 1 )
    {
    MODE = 0;
   
   /* WiFi.begin(ssid2, password2);
    while (WiFi.status() != WL_CONNECTED)
      {
      delay(500);
      Serial.print(".");
      }
    Serial.println("");
    Serial.println("WiFi conectado");
     // Inicializo el servidor*/
     intento_conexion();
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
    //WiFi.mode(WIFI_AP);
    WiFi.softAP(Conf_ssid);      //SSID por defecto

  server.on("/", []() {
    server.send(200, "text/html", pral);
  });
  server.on("/config", wifi_conf);
  server.begin();
  Serial.println("Webserver iniciado...");

  Serial.println(lee(70));
  Serial.println(lee(1));
  Serial.println(lee(30));
  intento_conexion();
    /*WiFi.softAP(Conf_ssid);      //SSID por defecto
    server.on("/", []() { server.send(200, "text/html", pral);});
    server.on("/config", cambia);
    server.begin();*/
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
    digitalWrite(Rst1, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(3000);
    digitalWrite(Rst1, LOW);
    digitalWrite(ledPin, LOW);
    todo="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nDevice Rebooted";
    todo+="</html>\n";
    client.print(todo);
  }

  delay(1);
  Serial.println("Cliente desconectado"); // Nos desconectamos del cliente
  Serial.println("");
   Serial.println("");
 
   // digitalWrite(ledPin, HIGH); // turn LED on:
    }
  if (MODE == 1)  // Active the Configuration Mode
    {
    server.handleClient();
    delay(2000);
    //digitalWrite(ledPin, LOW);   // turn LED off:
    }
  }
