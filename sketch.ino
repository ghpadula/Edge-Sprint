#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define led 2
#define temp 13

OneWire oneWire(temp);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27,16,2);

byte grauSimbolo[8] = {
  0b00111,
  0b00101,
  0b00111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};



float temperatura(){
  sensors.requestTemperatures();
  float celsius = sensors.getTempCByIndex(0);
  return celsius;
}


void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, grauSimbolo);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  


}

void loop() {
  float celsius = temperatura();//chama a função
  Serial.println(celsius);
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.setCursor(5,0);
  lcd.print(celsius);
  lcd.write(byte(0)); 
  lcd.print("C ");  

    while(celsius > 80 || celsius < 40){
    digitalWrite(led, HIGH);
    delay(200);
    digitalWrite(led, LOW);
    delay(200);
    lcd.setCursor(5,0);
    celsius = temperatura();
    lcd.print(celsius);
    lcd.write(byte(0)); 
    Serial.println(celsius);
    lcd.setCursor(0,1);
    lcd.print("Temp irregular!");  
    
  }
  lcd.setCursor(0,1);
  lcd.print("                 ");
  delay(500);

}
