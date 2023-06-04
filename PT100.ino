#include "ThingSpeak.h"
#include "WiFi.h"
float pt_100= 36;
float ADC = 0;
const char* ssid = "644114016777";                        //SSID de vuestro router.
const char* password = "130796847174";                //Contraseña de vuestro router.

unsigned long channelID = 2084008;                //ID de vuestro canal.
const char* WriteAPIKey = "ZCXRBK1KTS8CYROD";     //Write API Key de vuestro canal.              

WiFiClient cliente;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);//Iniciar puerto serial a 115200 baudios
  Serial.println("Test de sensor:");

  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi conectado!");

  ThingSpeak.begin(cliente);


}

void loop() {

  delay(2000);
 
  ADC=analogRead(pt_100);//Lectura ADC en pin 36
  float voltaje=(ADC*3.3)/4095; //Conversion valor de ADC a voltaje.
  float temperatura=(10.6060606*voltaje)+25; //Ecuacion caracteristica del sensor PT100.



  Serial.println("Temperatura: ");
  Serial.print(temperatura,1);
  Serial.println(" ºC."); 
  ThingSpeak.setField (1,temperatura);

  
  ThingSpeak.writeFields(channelID,WriteAPIKey);
  Serial.println("Datos enviados a ThingSpeak!");
  Serial.println("-----------------------");
  delay(4000);
  }
  
