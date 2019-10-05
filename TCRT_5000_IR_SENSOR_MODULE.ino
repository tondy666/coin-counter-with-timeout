##include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include<EEPROM.h>


#define pinIRd 6
#define pinIRa A0
#define pinLED 13
#define pbReset A13
#define pbOk A9
#define pbScroll A8



int IRvalueA = 0;
int IRvalueD = 0;
int jmlkoin = 0;
int koin = 0;
int jml = 0;
int jmltunai = 0;
int var1 = 0;
int var2 = 0;
int arr2 = 0;
int arr1 = 0;
int arrmin = 0;
int arrmax = 0;
int batas;
int batasTersimpan;
int adc;
unsigned int sensor_L[10] = {};
unsigned int sensor_S[10] = {};
int dumb = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.begin();
  lcd.print("I IZZAT P");
  lcd.setCursor(0, 1);
  lcd.print("Fithrotul I A");
  delay(3000);
  lcd.clear();

  pinMode(pinIRd, INPUT);
  pinMode(pinIRa, INPUT);
  pinMode(pinLED, OUTPUT);
  pinMode(pbOk, INPUT_PULLUP);
  pinMode(pbScroll, INPUT_PULLUP);
  pinMode(pbReset, INPUT_PULLUP);

  batasTersimpan=EEPROM.read(0);

}

void loop()
{

utama:
  lcd.print("kalibrasi");
  while (1)
  {
    if (digitalRead(pbOk) == LOW)
    {
      delay(20);
      if (digitalRead(pbOk) == LOW)
      {
        while (digitalRead(pbOk) == LOW);
        lcd.clear();
        goto kalibrasi;
      }
    }

    if (digitalRead(pbScroll) == LOW)
    {
      delay(20);
      if (digitalRead(pbScroll) == LOW)
      {
        while (digitalRead(pbScroll) == LOW);
        lcd.clear();
        goto menuconter;
      }
    }
  }

menuconter:
  while (1)
  {
    lcd.setCursor(0, 0);
    lcd.print("start conter");
    if (digitalRead(pbOk) == LOW)
    {
      delay(20);
      if (digitalRead(pbOk) == LOW)
      {
        while (digitalRead(pbOk) == LOW);
        lcd.clear();
        goto conter;
      }
    }

    if (digitalRead(pbScroll) == LOW)
    {
      delay(20);
      if (digitalRead(pbScroll) == LOW)
      {
        while (digitalRead(pbScroll) == LOW);
        lcd.clear();
        goto utama;
      }
    }
  }

kalibrasi:
  lcd.print("Kalibrasi");
  while (1)
  {
    while (var1 < 10)
    {
      lcd.setCursor(0, 1);
      lcd.print("Scaning 500......");
      if (digitalRead(pinIRd) == LOW)
      {
        delay(20);
        while (analogRead(pinIRa) <= 10);
        sensor_L[arr1] = analogRead(pinIRa);
        arr1++;
        var1++;
        lcd.setCursor(15, 0);
        lcd.print(var1);
        delay(20);
      }
      else
      {
        dumb = analogRead(pinIRa);
      }
      delay(20);
    }

    
    while (var2 < 10)
    {
      lcd.setCursor(0, 1);
      lcd.print("Scaning 1000....");
      if (digitalRead(pinIRd) == LOW)
      {
        delay(20);
        //while(digitalRead(pinIRd)==LOW);
        sensor_S[arr2] = analogRead(pinIRa);
        arr2++;
        var2++;
        lcd.setCursor(15, 0);
        lcd.print(var2);
        delay(20);
      }
      else
      {
        dumb = analogRead(pinIRa);
      }
      delay(20);
    }

    for (int i = 0; i < 10; i++)
    {
      if (arrmin <= sensor_L[i])
        arrmin = sensor_L[i];

      else
        arrmin = arrmin;

      i++;
    }

    for (int i = 0; i < 10; i++)
    {
      if (sensor_L[i] <= arrmin)
      {
        arrmin = sensor_L[i];
      }
      else
      {
        arrmin = arrmin;
      }
    }

    for (int j = 0; j < 10; j++)
    {
      if (sensor_S[j] >= arrmax && sensor_S[j] <= arrmin)
      {
        arrmax = sensor_S[j];
      }
      else
      {
        arrmax = arrmax;
      }
    }
    
    batas = ((arrmin+arrmax)/2)+1;

    EEPROM.write(0, batas);
    if (digitalRead(pbScroll) == LOW)
    {
      delay(20);
      if (digitalRead(pbScroll) == LOW)
      {
        while (digitalRead(pbScroll) == LOW);
        batasTersimpan=EEPROM.read(0);
        lcd.clear();
        goto utama;
      }
    }
    lcd.clear();
    lcd.setCursor(8, 0);
    lcd.print(batas);
  }

conter:
  lcd.setCursor(10, 1);
  lcd.print("$:");
  lcd.setCursor(0, 1);
  lcd.print("JKOIN:");
  lcd.setCursor(0, 0);
  lcd.print("JML:");
  while (1)
  {
    if (analogRead(pinIRa) <= batasTersimpan)
    {
      delay(10);
      adc = analogRead(pinIRa);
      while (analogRead(pinIRa) <= batasTersimpan);
      digitalWrite(LED_BUILTIN, HIGH);
      jmlkoin++;
      koin = 1000;
      jmltunai += 10;

      lcd.setCursor(12, 1);
      lcd.print(koin);
      lcd.setCursor(12, 0);
      lcd.print(adc);
      lcd.setCursor(6, 1);
      lcd.print(jmlkoin);
      lcd.setCursor(4, 0);
      lcd.print(jmltunai);
      lcd.print("00");
    }
    else if (analogRead(pinIRa) <= 70)
    {
      delay(10);
      adc = analogRead(pinIRa);
      while (analogRead(pinIRa) <= 70);
      digitalWrite(LED_BUILTIN, HIGH);
      jmlkoin++;
      koin = 500;
      jmltunai += 5;

      lcd.setCursor(12, 1);
      lcd.print(koin);
      lcd.print(" ");
      lcd.setCursor(12, 0);
      lcd.print(adc);
      lcd.setCursor(6, 1);
      lcd.print(jmlkoin);
      lcd.setCursor(4, 0);
      lcd.print(jmltunai);
      lcd.print("00");
    }

    delay(50);

    if (digitalRead(pbReset) == LOW)
    {
      delay(20);
      if (digitalRead(pbReset) == LOW)
      {
        while (digitalRead(pbReset) == LOW);
        lcd.clear();
        goto ResetConter;
      }
    }
  }

ResetConter:
  while (1)
  {
    jmlkoin = 0;
    koin = 0;
    jml = 0;
    jmltunai = 0;
    goto conter;
  }
}
