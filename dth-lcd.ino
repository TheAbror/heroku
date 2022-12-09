//dht11 and lcd --start
#include "DHT.h"
#include <LCD_I2C.h>
#define DHTPIN 2
LCD_I2C lcd(0x27, 16, 2);
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//dht11 and lcd --end
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0; 
const int buzzer = 9;


void setup() {
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  myservo.attach(8); 
  pinMode(buzzer, OUTPUT);
}

void loop() {
  delay(1000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15 ms for the servo to reach the position
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  lcd.print("Humidity : ");
  lcd.print(h);
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.setCursor(0, 1);


  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
   tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(2000); 
}
