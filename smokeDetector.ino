
#include <Wire.h>
#include <UnoWiFiDevEd.h>
 
#define CONNECTOR     "rest" 
#define SERVER_ADDR   "api.thingspeak.com"
 
#define APIKEY_THINGSPEAK  "PB8IZ8SJLS33EW2C" //Insert your API Key 
 
short hum = 60;
short temp = 22;
short delta;

// smoke detector

#define redLed 6
#define detector A0

short reading1;
short reading2;

void setup() {
  Serial.begin(9600);
  Ciao.begin(); // CIAO INIT
  pinMode(redLed, OUTPUT);   
  pinMode(detector, INPUT);  
}
 
void loop() {

  reading1 = analogRead(detector);
  delay(500);
  reading2 = analogRead(detector);
  delta = abs(reading1 - reading2);

  if (delta > 2){
    
    digitalWrite(redLed, HIGH);
    Serial.println(delta);
     
    String uri = "/update?api_key=";
    uri += APIKEY_THINGSPEAK;
    uri += "&field1=";
    uri += String(hum);
    uri += "&field2=";
    uri += String(temp);
    uri += "&field3=";
    uri += String(delta);
 
    Ciao.println("Send data on ThingSpeak Channel"); 
      
    CiaoData data = Ciao.write(CONNECTOR, SERVER_ADDR, uri);
 
    if (!data.isEmpty()){
      Ciao.println( "State: " + String (data.get(1)) );
      Ciao.println( "Response: " + String (data.get(2)) );
    }
    else { 
      Ciao.println("Write Error");
    }    
    
  delay(30000); // Thinkspeak policy
  } else {
    digitalWrite(redLed, LOW);
    Serial.println(reading1);
    Serial.println(reading2);
    Serial.println("nothing");
  }
}
