#include <DHT.h> //Librairie pour le capteur 
#include <ESP8266WiFi.h>

#define DHTPIN 13  //GPIO13 = broche D7
#define DHTTYPE DHT22

//Initialisation du capteur
DHT dht(DHTPIN, DHTTYPE); 

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Communication avec DTH22 demarree");
  dht.begin();
  Serial.println("Debut des relevees capteur DTH22 avec un intervalle de mesure de 0,5 s");
}

// Boucle pour la lecture des donnees
void loop() 
{
  // put your main code here, to run repeatedly:
  delay(2000); //En ms = 0.5s 

  float temperature = dht.readTemperature();
  float humidite = dht.readHumidity();
  
  int temperature_formated =(int)(dht.readTemperature() * 100);
  int humidite_formated =(int)(dht.readTemperature() * 100);

  //Fomat pour envoie en ASCii
  int resultat_formated = temperature_formated * 10000 + humidite_formated; 

  /*//Traitement separe des cas rares et particuliers en concervant la 
  if (temperature <= 100 )
    {
      temperature_formated +=temperature_formated/10000;   //Stockage des centaines dans l
    }
  if (temperature < 0 )
    {
      temperature_formated +=9;
    }
  */

  // Test des donnees
  Serial.println("Formated Data: " + String(resultat_formated)+"\n");

}
