#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define led 2
#define temp 13

OneWire oneWire(temp);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27,20,4);

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


int energia1(){
  int a0Value = analogRead(A0);
  int energia1 = map(a0Value, 0, 1023, 0, 100);
  return energia1;
}
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
  int energia = energia1();
  Serial.println(celsius);
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.setCursor(5,0);
  lcd.print(celsius);
  lcd.write(byte(0)); 
  lcd.print("C ");  
  lcd.setCursor(0,2);
  lcd.print("Energia: ");
  lcd.print(energia);
  lcd.print("%");

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

  while(energia < 10 && energia > 0){
    energia = energia1();
    lcd.setCursor(0,2);
    lcd.print("Energia: ");
    lcd.print(energia);
    lcd.print("%");
    lcd.setCursor(0,3);
    lcd.print("Energia baixa!");
    //Serial.println(energia);
    
    
  }
  while(energia == 0){  
    energia = energia1();  
    lcd.setCursor(0,2);
    lcd.print("Energia: ");
    lcd.print(energia);
    lcd.print("%");
    lcd.setCursor(0,3);
    lcd.print("Sem energia!");
    //Serial.println(energia);
    

  }
  
  lcd.setCursor(0,1);
  lcd.print("                 ");
  delay(500);
  lcd.setCursor(0,2);
  lcd.print("                        ");
  lcd.setCursor(0,3);
  lcd.print("                        ");

}
