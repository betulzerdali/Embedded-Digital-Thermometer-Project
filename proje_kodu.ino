#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2          
#define DHTTYPE DHT11     
#define BUTTON_PIN 4      
#define RED_PIN 3         
#define BLUE_PIN 6        

LiquidCrystal_I2C lcd(0x27, 16, 2); 
DHT dht(DHTPIN, DHTTYPE);

bool gostergeModu = true; 

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  dht.begin();
  lcd.init();
  lcd.backlight(); 
}

void loop() {
  float sicaklik = dht.readTemperature();
  float nem = dht.readHumidity();

  if (digitalRead(BUTTON_PIN) == LOW) {
    gostergeModu = !gostergeModu; 
    lcd.clear();                  
    delay(300);                   
  }

  // Eger sensor baglantisi tam degilse LCD'de net uyaralim
  if (isnan(sicaklik) || isnan(nem)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Baglantisi");
    lcd.setCursor(0, 1);
    lcd.print("Kontrol Ediniz! ");
    digitalWrite(RED_PIN, HIGH); // Hata durumunda kirmizi yansin
    digitalWrite(BLUE_PIN, LOW);
    delay(500);
    return;
  }

  if (sicaklik > 30.0) {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
  } else {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
  }

  if (gostergeModu) {
    lcd.setCursor(0, 0);
    lcd.print("Sicaklik Degeri:");
    lcd.setCursor(0, 1);
    lcd.print(sicaklik);
    lcd.print(" C  ");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Ortam Nem Orani:");
    lcd.setCursor(0, 1);
    lcd.print("% ");
    lcd.print(nem);
    lcd.print("   ");
  }

  delay(100); 
}