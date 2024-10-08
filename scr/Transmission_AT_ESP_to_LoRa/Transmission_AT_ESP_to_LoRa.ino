//#include <LoRa-E5.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial_to_LoRa (D5, D6); // D5 : GPIO14 Rx to Lora D6 : GPIO12 Tx to Lora 
// GPIO3 to RX, GPIO1 to TX reserved to ESP8266 to USB convert

//Creer mini fonction pour l affichage synthetique type Serial_to_LoRa_function (str commande, str texte_affiche, int delay )

void setup()
{
  delay (3000);
  Serial.begin(9600); //Monitor
  Serial_to_LoRa.begin(9600); //LoRa  
  delay (2000);

  Serial_to_LoRa.write ("AT+ID=DevEUI,70B3D57ED006AE59 ,");
  Serial.println("\n\nSerial_to_LoRa \"AT+ID=DevEUI\"");
  delay (1000);
  Serial_to_LoRa.write ("AT+ID=AppEUI,A0A0A0A0A0A0A0A0 ");
  Serial.println("Serial_to_LoRa \"AT+ID=AppEUI\"");
  delay (1000);
  Serial_to_LoRa.write ("AT+KEY=APPKEY,B3C21FF5B9ECD87A0BB702B2C3D87459 ");
  Serial.println("Serial_to_LoRa \"AT+KEY=APPKEY\"\n");
  delay (1000);

  Serial_to_LoRa.write ("AT+DR=EU868");
  Serial.println("Serial_to_LoRa \"AT+DR=EU868\"");
  delay (2000);

  Serial_to_LoRa.write ("AT+MODE=LWOTAA ");
  Serial.println("Serial_to_LoRa \"AT+MODE=LWOTAA \"");
  delay (2000);

  Serial_to_LoRa.write ("AT+JOIN");
  Serial.println("Serial_to_LoRa \"AT+JOIN\"");
  delay (2000);
  Serial_to_LoRa.write ("AT");
  Serial.println("Serial_to_LoRa \"AT\"");
  
  

}

void loop() 
{
  for (int ii = 1; ii < 10; ii++)
{
    if (Serial_to_LoRa.available())
    {
        delay(1000);

        // Utilisation d'un seul print pour AT+MSG avec la valeur de ii
        Serial_to_LoRa.print("AT+MSG=");
        Serial_to_LoRa.println(ii); // Incrémente le numéro
        Serial.println("Serial_to_LoRa \"AT+MSG=" + String(ii) + "\"");

        delay(4000);
    }
    else
    {
        Serial.print("Serial_to_LoRa not available");
        delay(500);

        // Pause visuelle
        for (int i = 0; i < 8; i++)
        {
            Serial.printf(" .");
            if (i == 7)
            {
                Serial.print("\n");
            }
            delay(200);
        }
    }
}

}
