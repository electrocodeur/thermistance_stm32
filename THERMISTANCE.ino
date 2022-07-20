// PIN DE LECTURE
#define THERMISTORPIN PA0         
// resistance 
#define THERMISTORNOMINAL 10000      
// temp. pour nominal resistance (souvent 25 C)
#define TEMPERATURENOMINAL 25   

#define NUMSAMPLES 5
#define BCOEFFICIENT 3950
// la valeur pour l'autre resistance
#define SERIESRESISTOR 10000    

int samples[NUMSAMPLES];

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  uint8_t i;
  float average;

  // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++) {
   samples[i] = analogRead(THERMISTORPIN);
   delay(10);
  }
  
  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  }
  average /= NUMSAMPLES;

  Serial.print("Average analog reading "); 
  Serial.println(average);
  
  // convert the value to resistance
  average = 4096 / average - 1;
  average = SERIESRESISTOR / average;
  Serial.print("Thermistor resistance "); 
  Serial.println(average);
  
  float temperature;
  temperature = average / THERMISTORNOMINAL;     // (R/Ro)
  temperature = log(temperature);                  // ln(R/Ro)
  temperature /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  temperature += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  temperature = 1.0 / temperature;                 // Invert
  temperature -= 273.15;                         // convert absolute temp to C
  
  Serial.print("Temperature "); 
  Serial.print(temperature);
  Serial.println(" *C");
  
  delay(1000);
}
