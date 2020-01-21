#include "DHT.h"

#define DHTPIN D4     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT12   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
float tab[10];
  int i = 0 ;
  int j;
  float moyTemp = 0;
  bool full = false ;
  float av1 = 0;
  float av2 = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  
  dht.begin();
}

void loop() {
  
  // frequence de meure du capteur est de 1 seconde 
  delay(1000);
  

  
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  
    tab[i] = t;
 
  if (i == 9 ) {
    for(j = 0;j<=9;j++){
      moyTemp += tab[j];
    }
    moyTemp /= 10;
  
    
    Serial.print(moyTemp);
    if( av1!=0){
      av2 = moyTemp;
      if (av1<av2){
        digitalWrite(D1, HIGH);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
      }else if(av1>av2){
        digitalWrite(D2, HIGH);
        digitalWrite(D1, LOW);
        digitalWrite(D3, LOW);
      }else if(av1 == av2){
        digitalWrite(D2, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D3, HIGH);
      }
      av1=av2;
      
    }else{
      av1 = moyTemp;
    }
    
    Serial.print("\t");
    moyTemp = 0;
    i = -1;
  }

  Serial.println(av1);
  Serial.println(av2);
    

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Impossible de lire la sonde DHT!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

 //Serial.print("Humidity: ");
  //Serial.print(h);
  //Serial.print(" %\t");
  //Serial.print("Temperature: ");
  //Serial.print(t);
  //Serial.print(" *C ");
  //Serial.print(f);
    //Serial.print(" *F\t");
    //Serial.print("Heat index: ");
    //Serial.print(hic);
    //Serial.print(" *C ");
    //Serial.print(hif);
    //Serial.println(" *F");
  i++;
}
