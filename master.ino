#include "Wire.h"
#include "EEPROM.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SH1106.h"

//oled define
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16
#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

//sistem define
#define pinIRd 7
#define pinIRa A0
#define pinLED 13
#define pbReset 11
#define pbOK 10
#define pbScroll 8
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
int jmlArr=0;
unsigned int sensor_L[10] = {};
unsigned int sensor_S[10] = {};
int dumb = 0;

void setup()
{
	Serial.begin(9600);
	pinMode(pinIRd, INPUT);
  	pinMode(pinIRa, INPUT);
  	pinMode(pinLED, OUTPUT);
  	pinMode(pbOK, INPUT_PULLUP);
  	pinMode(pbScroll, INPUT_PULLUP);
  	pinMode(pbReset, INPUT_PULLUP);

	display.begin(SH1106_SWITCHCAPVCC, 60);
	display.clearDisplay();
	showBooting();
	showBnner();

	batasTersimpan=EEPROM.read(0);
}

void loop()
{

utama:
	showIDName();
	while(1){
	    // statement
	    if(digitalRead(pbOK)==LOW)
	    {
	    	delay(20);
	    	if(digitalRead(pbOK)==LOW)
	    	{
	    		while(digitalRead(pbOK)==LOW);
	    		goto MenuUtamaKalibrasi;
	    	}
	    }
	}

MenuUtamaKalibrasi:
	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(BLACK,WHITE);
	display.setCursor(0,0);
	display.println("KALIBRASI");
	display.setTextColor(WHITE);
	display.setCursor(0,20);
	display.println("COUNTER");
	display.setTextColor(WHITE);
	display.setCursor(0,40);
	display.println("CREDIT");
	display.display();
	delay(20);
	while(1){
		    // statement
		    if(digitalRead(pbScroll)==LOW)
		    {
		    	delay(20);
		    	if(digitalRead(pbScroll)==LOW)
		    	{
		    		while(digitalRead(pbScroll)==LOW);
		    		goto MenuUtamaCounter;
		    	}
		    }

		    if(digitalRead(pbOK)==LOW)
		    {
		    	delay(20);
		    	if(digitalRead(pbOK)==LOW)
		    	{
		    		while(digitalRead(pbOK)==LOW);
		    		goto kalibrasi;
		    	}

		    }
		}

MenuUtamaCounter:
	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("KALIBRASI");
	display.setTextColor(BLACK,WHITE);
	display.setCursor(0,20);
	display.println("COUNTER  ");
	display.setTextColor(WHITE);
	display.setCursor(0,40);
	display.println("CREDIT");
	display.display();
	delay(20);
	while(1){
	    // statement
	    if(digitalRead(pbScroll)==LOW)
		{
		    delay(20);
		    if(digitalRead(pbScroll)==LOW)
		    {
		    	while(digitalRead(pbScroll)==LOW);
		    	goto MenuUtamaCredit;
		    }
		}

		if(digitalRead(pbOK)==LOW)
		{
			delay(20);
			if(digitalRead(pbOK)==LOW)
			{
				while(digitalRead(pbOK)==LOW);
				goto counterStart;
			}
		}
	}

MenuUtamaCredit:
	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("KALIBRASI");
	display.setTextColor(WHITE);
	display.setCursor(0,20);
	display.println("COUNTER");
	display.setTextColor(BLACK,WHITE);
	display.setCursor(0,40);
	display.println("CREDIT   ");
	display.display();
	delay(20);
	while(1){
	    // statement
	    if(digitalRead(pbScroll)==LOW)
		{
		    delay(20);
		    if(digitalRead(pbScroll)==LOW)
		    {
		    	while(digitalRead(pbScroll)==LOW);
		    	goto MenuUtamaKalibrasi;
		    }
		}

		if(digitalRead(pbOK)==LOW)
		{
			delay(20);
			if(digitalRead(pbOK)==LOW)
			{
				while(digitalRead(pbOK)==LOW);
				goto CreditShow;
			}
		}
	}

kalibrasi:
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(10,0);
	display.println("KALIBRASI MODE : ON");
	display.drawLine(0,10,550,10,WHITE); 
	display.display();
	while(1){
	    // statement
	    if(digitalRead(pinIRd)==LOW)
	    {
	    	while(var1<10){
	    		display.clearDisplay();
	    	    if(digitalRead(pinIRd)==LOW)
	    	    {
	    	    	while(analogRead(pinIRa)<=10);
	    	    	sensor_S[arr1]=analogRead(pinIRa);
	    	    	arr1++;
	    	    	var1++;
	    	    	display.setTextSize(4);
	    	    	display.setCursor(40,20);
	    	    	display.println(arr1);
	    	    	display.display();
	    	    }
	    	    else{
	    	    	dumb = analogRead(pinIRa);
	    	    }
	    	}
	    	display.setCursor(0,0);
	    	display.setTextSize(1);
	    	for(int i=0; i<10; i++){
	    		jmlArr+=sensor_S[i];
	    	}
	    	display.setCursor(0,50);
	    	display.println(jmlArr/10);
	    	display.display();	
	    }
	    if(digitalRead(pbReset)==LOW)
	    {
	    	delay(20);
	    	if(digitalRead(pbReset)==LOW)
	    	{
	    		while(digitalRead(pbReset)==LOW);
	    		var1=0;
	    		arr1=0;
	    		jmlArr=0;
	    		goto kalibrasi;
	    	}
	    }	
	}

counterStart:
	while(1){
		    // statement
		}

blankTest:
	blankShow();
	while(1){
	    // statement
	}

CreditShow:
	display.clearDisplay();
	showIDName();
	while(1){
		    // statement
		if(digitalRead(pbOK)==LOW)
		{
		    delay(20);
		    if(digitalRead(pbOK)==LOW)
		    {
		    	while(digitalRead(pbOK)==LOW);
		    	goto MenuUtamaCredit;
		    }
		}
	}	
}

void blankShow(void)
{
	display.println(" ");
	display.display();
	delay(3000);
	display.clearDisplay();
}

void showBnner(void)
{
	display.setTextSize(2);
	display.setTextColor(BLACK,WHITE);
	display.setCursor(10,20);
	display.println("PROJECT 2");
	display.setTextSize(1);
	display.setCursor(30,40);
	display.setTextColor(WHITE);
	display.println("TIMEOUT COIN");
	display.display();
	delay(3000);
	display.clearDisplay();

}

void showIDName(void)
{
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("ILFAT IZZAT P.");
	display.setCursor(0,15);
	display.setTextColor(WHITE);
	display.println("FITROTUL IRDA A.");
	display.display();
	delay(20);
	display.clearDisplay();
}

void showBooting(void)
{
	display.drawPixel(10,10,WHITE);
	display.display();
	delay(1000);
	display.drawPixel(20,10,WHITE);
	display.display();
	delay(1000);
	display.drawPixel(30,10,WHITE);
	display.display();
	delay(1000);
	display.clearDisplay();
}