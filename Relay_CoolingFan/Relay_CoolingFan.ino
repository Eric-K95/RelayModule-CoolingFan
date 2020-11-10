//Relay Module
//Sketched by JIN-WOO KIM

#include <LiquidCrystal_I2C.h>
#include<math.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int thermistorPin = A0;
int beta = 3950; //the beta of the thermistor
const int ledPin = 13;
const int relayPin = 3;

void setup() {
  pinMode(relayPin, OUTPUT); //initialize the replay Pin as an output
  pinMode(ledPin, OUTPUT); //initialize the LED Pin as an output
  lcd.begin();
  lcd.setCursor(5, 0); //first column, row #5
  lcd.print("Hello!");
  lcd.setCursor(0, 1); //second column, row #1
  lcd.print("MECHATRONICS :)");
  delay(2000);   //delay of the message
  lcd.clear();   // clear screen
  lcd.setCursor(0, 0); //first column, row #1
  lcd.print("Temperature");
  lcd.setCursor(0, 1); //second column, row #1
  lcd.print("Sensor");
  delay(2000); //delay 2000ms
  lcd.clear();
  Serial.begin(9600);
}
void loop() {
  long a = 1023 - analogRead(thermistorPin);
  float tempC = beta / (log((1025.0 * 10 / a - 10) / 10) + beta / 298.0) - 273.0;
  float tempF = 1.8 * tempC + 32.0;
  Serial.print("Centigrade: ");
  Serial.println(tempC);
  Serial.print("Fahrenheit: ");
  Serial.println(tempF);
  Serial.println(""); 
  delay(100);

  //Set the range of the temperature
  if (tempF <= 92) {
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, LOW);
  }
  else {
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, HIGH);
  }
  delay(100);

  //print values on lcd screen
  lcd.setCursor(0, 0); //first column, row #1
  lcd.print("tempC:"); //print name
  lcd.setCursor(8, 0); //first column, row #10
  lcd.print(tempC); //print temperature in Celsius
  lcd.setCursor(13, 0); //first column, row #7
  lcd.print(char(223)); //print units
  lcd.setCursor(0, 1); //second coulumn, row#0
  lcd.print("tempF:"); //print name
  lcd.setCursor(8, 1); //second coulumn, row#5
  lcd.print(tempF); //print temperature in Fahrenheit
  lcd.setCursor(13, 1); //second coulumn, row#7
  lcd.print(char(223));  //unit of temperature
}
