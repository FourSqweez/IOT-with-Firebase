
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>

// Set these to run example.
#define FIREBASE_HOST "osproject-c90ac.firebaseio.com"
#define FIREBASE_AUTH "kZSfJOfKhPlzUIkJLKjQhqAJW6CbmpA7eeOhCtTr"
#define WIFI_SSID "Mr"
#define WIFI_PASSWORD "mrnutnin"

#define DHTPIN D1   // Data Pin of DHT 11 , for NodeMCU D5 GPIO no. is 14
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

#define Lamp_pin D3
#define Lamp_on LOW
#define Lamp_off HIGH

void setup() {
  Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  dht.begin();
  pinMode(D2, OUTPUT);
  pinMode(Lamp_pin, OUTPUT);

}

void loop() {
    // get value

  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Reading temperature as Celsius (the default)
  Serial.println(h);
  Serial.println(t);
  Firebase.setFloat("Temp",t);
  Firebase.setFloat("Humidity",h);
  
  int n = Firebase.getInt("ledStatus");
  //boolean S == Scale.  True == Fahrenheit; False == Celcius
  float temp = dht.readTemperature(false);
  // handle error

  if (temp <= 28){
    Firebase.setFloat("ledStatus",1);
    Serial.println("LED ON");
      digitalWrite(D2,HIGH); 
      digitalWrite(Lamp_pin,Lamp_on);
    return;
    delay(2);
  }

  if (temp >= 29){
    Firebase.setFloat("ledStatus",0);
    Serial.println("LED OFF");
    digitalWrite(D2,LOW);
    digitalWrite(Lamp_pin,Lamp_off); 
    return;
    delay(2);
  }
   

  
 }
 
