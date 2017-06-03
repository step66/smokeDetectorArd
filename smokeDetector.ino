// smoke detector

#define redLed 6

#define detector A0

float reading1;
float reading2;
float delta;

void setup() {
  Serial.begin(9600);
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
     delay(10000);
   } else {
     digitalWrite(redLed, LOW);
     Serial.println(reading1);
     Serial.println(reading2);
     Serial.println("nothing");
   }
    
  delay(300);
  
}
