#include <DHT.h> //Librairie pour le capteur 
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#define DHTPIN 13  //GPIO13 = broche D7
#define DHTTYPE DHT22

//Initialisation du capteur
DHT dht(DHTPIN, DHTTYPE); 

SoftwareSerial Serial_to_LoRa (D5, D6); //D5 : GPIO14 Rx to Lora D6 : GPIO12 Tx to Lora 
//GPIO3 to RX, GPIO1 to TX reserved to ESP8266 to USB convert

//Envoi commande via le port serie de LoRa to TTN et affaichage de commande par liasion serie de ESP to PC
void Serial_to_LoRa_function(String commande, String texte_affiche, int delayTime) 
{
  //Serial.print("\nSerial_to_LoRa" + texte_affiche);  //Utile au deboguage
  Serial_to_LoRa.write(commande.c_str());
  Serial.print(Serial_to_LoRa.readString());
  
  delay(delayTime);
}

void setup()
{
  delay (3000);
  Serial.println("\nDebut du programme :");
  Serial.begin(9600); //Monitor
  Serial_to_LoRa.begin(9600); //LoRa  
  delay (2000);

  Serial.println();
  Serial_to_LoRa_function("AT", " \"AT\"", 2000); 

  //Configuration des parametres de connection
  Serial_to_LoRa_function("AT+ID=DevEUI,70B3D57ED006AE59", " \"AT+ID=DevEUI\"", 5000);
  Serial_to_LoRa_function("AT+ID=AppEUI,A0A0A0A0A0A0A0A0", " \"AT+ID=AppEUI\"", 5000);
  Serial_to_LoRa_function("AT+KEY=APPKEY,B3C21FF5B9ECD87A0BB702B2C3D87459", " \"AT+KEY=APPKEY\"", 5000);
  Serial.println();
  //Commande Annexe
  Serial_to_LoRa_function("AT+DR=EU868", " \"AT+DR=EU868\"", 5000);
  Serial_to_LoRa_function("AT+MODE=LWOTAA", " \"AT+MODE=LWOTAA\"", 5000);
  Serial_to_LoRa_function("AT+JOIN", " \"AT+JOIN\"", 10000);
  Serial_to_LoRa_function("AT", " \"AT\"", 2000); 

  Serial.println("Demarrage communication avec DTH22");
  dht.begin();
  Serial.println("Debut des relevees capteur DTH22 avec un intervalle de mesure de 8s s");
  Serial.println();
}

void loop() 
{
  Serial.println();
  Serial.println("Debut de transmission :");

  if (Serial_to_LoRa.readString())
  {
    //Collecte de donnees brutes
    float temperature = dht.readTemperature();
    float humidite = dht.readHumidity();
    
    //Formatage des donnees brutes
    int temperature_formated =(int)(temperature * 100);
    int humidite_formated =(int)(humidite * 100);

    //Fomat pour envoie en ASCii
    int resultat_formated = temperature_formated * 10000 + humidite_formated; 
    delay(4000);

    Serial.println("Formated Data: " + String(resultat_formated)+"\n");
    Serial_to_LoRa.write(("AT+MSG=" + String(resultat_formated)).c_str());
    Serial.print(Serial_to_LoRa.readString());

    delay(4000);
  }
  else
  {
    Serial.print("Attente de reponse - Cablage a verifier");
    delay(500);

    //Pause visuelle avec des petits points pour savoir que le systeme n est pas bloque
    int nb_point = 10;
    int delay_tot = 2000; //ms
    for (int i = 0; i < nb_point; i++)
    {
      Serial.printf(" .");
      if (i == nb_point-1)
      {
        Serial.print("\n");
      }
      delay(delay_tot/nb_point);
    }
  }
}
