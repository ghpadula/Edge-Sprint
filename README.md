# Sistema de Monitoramento de Temperatura
# Nomes

## Rodrigo H M Nakata 556417
## Gabriel Henrique Padula 554907
## Enzo Gaião Real 557943
## Gustavo Pasquini Lucas 555454
## Vitor Couto Victorino 554965

## Descrição

Esse projeto tem como principal função mostrar para o piloto do carro a temperatura atual de suas rodas, caso esteja acima ou abaixo da temperatura correta ele ira acender um led e avisar no lcd.

## Componentes

- Placa Arduino
- Sensor de temperatura DS18B20(Usado pois no simulador tem como colocar maiores temperaturas)
- Display LCD I2C (16x2)
- LED vermelho
- Resistor 220Ω
- Potenciometro(Para simular a energia)
- Protoboard e fios jumpers

## Bibliotecas

bibliotecas utilizadas neste projeto:

- **LiquidCrystal_I2C**: Para controlar o lcd do tipo I2C
- **OneWire**: Para utilizar o sensor DS18B20.
- **DallasTemperature**: Para pegar os dados de temperatura do sensor DS18B20.

### Conexões

1. **Sensor DS18B20**:
   - VCC -- 5V(Protoboard)
   - GND -- GND(Protoboard)
   - Data -- Pino Digital 13

2. **LCD I2C**:
   - SDA -- A4
   - SCL -- A5
   - VCC -- 5V(Protoboard)
   - GND -- GND(Protoboard)

3. **LED**:
   - Ânodo (perna longa) --Digital 2 (com um resistor de 220Ω)
   - Cátodo (perna curta) -- GND(Protoboard)

4. **Potenciomentro**
   - SIG - A0

## Código

```cpp
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
    Serial.println(energia);
    
    
  }
  while(energia == 0){  
    energia = energia1();  
    lcd.setCursor(0,2);
    lcd.print("Energia: ");
    lcd.print(energia);
    lcd.print("%");
    lcd.setCursor(0,3);
    lcd.print("Sem energia!");
    Serial.println(energia);
    

  }
  
  lcd.setCursor(0,1);
  lcd.print("                 ");
  delay(500);
  lcd.setCursor(0,2);
  lcd.print("                        ");
  lcd.setCursor(0,3);
  lcd.print("                        ");

}
