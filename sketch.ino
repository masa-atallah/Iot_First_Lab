// Channel ID: 3551643
// Api Key : 


#include <WiFi.h> 
#include "ThingSpeak.h"
#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT22

DHT senorDHT(15, DHT22);

const char* WIFI_Name="Wokwi-GUEST";
const char* WIFI_Pass="";

const int channelNumber=3551643;
const char* apiKey="Api Key";

WiFiClient clientObject;

void setup() {

  Serial.begin(115200);
  senorDHT.begin();
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_Name,WIFI_Pass);

 while( WiFi.status()!= WL_CONNECTED)
 {
  Serial.println("Status: Not Connected");
    delay(1000);
 }
  Serial.println("Status:  Connected");
  ThingSpeak.begin(clientObject);
}

void loop() {

  float temperature = senorDHT.readTemperature();
  float humidity = senorDHT.readHumidity();

  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.println("%");

  Serial.println( "University ID: 12114670");
 
    ThingSpeak.setField(1,temperature);
    ThingSpeak.setField(2,humidity);

    int stat=ThingSpeak.writeFields(channelNumber,apiKey);

    if(stat==200)
    {
    Serial.println("Data Sent to ThingSpeak");
    }
    else{
    Serial.println("Error sending data. Code:");
    Serial.println(stat);
    }

 delay(20000);

}
