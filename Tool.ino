// Temperatur sensor krever biblioteker onewire og dallastemperature til å ta imot rå temperatur data og omgjøre dem til grader celsius
#include <OneWire.h>
#include <DallasTemperature.h>
 
// Dataledningen fra tempreratursensoren er koblet til arduinoen via port 2
#define ONE_WIRE_BUS 2
 
// Oppsett av Onewire instansen
OneWire oneWire(ONE_WIRE_BUS);
 
// Sende onewire instansen til DallasTemperature
DallasTemperature sensors(&oneWire);

DeviceAddress thermometer;

// fuktighet sensor og potentiometer som er brukt til å bytte mellom moduser bruker analoge porter
int fuktPin = A0;
int potentioPin = A1;

// Variabler til LEDer
int fuktL = 7;
int fuktG = 8;
int fuktH = 5;
int tempL = 9;
int tempG = 10;
int tempH = 6;
int vanning = 4;
int saaing = 3;

// Variabler med verdiene fra sensorer og potentiometeren
float temp = 0;
int fukt = 0;
int potVerdi = 0;

// En variabel som beholder det nåværende moduset
bool modus = true;
 
void setup(void)
{
  // Starte DallasTempature instansen
  sensors.begin();
  if (!sensors.getAddress(thermometer, 0)) digitalWrite(vanning,HIGH); digitalWrite(saaing, HIGH));
  sensors.setResolution(thermometer, 9);
}
 
 
void loop(void)
{
  sensors.requestTemperatures(); // Be om temperatur
  temp = sensors.getTempC(thermometer); // Lagre temperatur verdi
  fukt = analogRead(fuktPin); // Lagre fuktighet verdi
  potVerdi = analogRead(potentioPin); // Lagre potentiometer verdi

  // Sjekke for modus-bytte
  if (potVerdi < 200) {
    modus = true;
    digitalWrite(vanning, HIGH);
    digitalWrite(saaing, LOW);
  } else if (potVerdi > 800) {
    modus = false;
    digitalWrite(vanning, LOW);
    digitalWrite(saaing, HIGH);
  }

  if (modus) { // vanning modus
    if (temp <= 25) { // Lav temperatur
      digitalWrite(tempL, HIGH);
      digitalWrite(tempG, LOW);
      digitalWrite(tempH, LOW);
    } else if (temp > 25 && temp < 30) { // God temperatur
      digitalWrite(tempL, LOW);
      digitalWrite(tempG, HIGH);
      digitalWrite(tempH, LOW);
    } else if (temp > 30) { // Høy temperatur
      digitalWrite(tempL, LOW);
      digitalWrite(tempG, LOW);
      digitalWrite(tempH, HIGH);
    }

    if (fukt < 200) { // Lav fuktighet
      digitalWrite(fuktL, HIGH);
      digitalWrite(fuktG, LOW);
      digitalWrite(fuktH, LOW);
    } else if (fukt >= 200 && fukt <= 450) { // God fuktighet
      digitalWrite(fuktL, LOW);
      digitalWrite(fuktG, HIGH);
      digitalWrite(fuktH, LOW);
    } else if (fukt > 450) { // Høy fuktighet
      digitalWrite(fuktL, LOW);
      digitalWrite(fuktG, LOW);
      digitalWrite(fuktH, HIGH);
    }
  }
  else // saaing modus
  {
    if (temp < 20) { // Lav temperatur
      digitalWrite(tempL, HIGH);
      digitalWrite(tempG, LOW);
      digitalWrite(tempH, LOW);
    } else if (temp >= 20 && temp <= 25) { // God temperatur
      digitalWrite(tempL, LOW);
      digitalWrite(tempG, HIGH);
      digitalWrite(tempH, LOW);
    } else if (temp > 25 ) { // Høy temperatur
      digitalWrite(tempL, LOW);
      digitalWrite(tempG, LOW);
      digitalWrite(tempH, HIGH);
    }

    if (fukt < 250) { // Lav fuktighet
      digitalWrite(fuktL, HIGH);
      digitalWrite(fuktG, LOW);
      digitalWrite(fuktH, LOW);
    } else if (fukt >= 250 && fukt < 400) { // God fuktighet
      digitalWrite(fuktL, LOW);
      digitalWrite(fuktG, HIGH);
      digitalWrite(fuktH, LOW);
    } else if (fukt >= 400) { // Høy fuktighet
      digitalWrite(fuktL, LOW);
      digitalWrite(fuktG, LOW);
      digitalWrite(fuktH, HIGH);
    }
  }
}



