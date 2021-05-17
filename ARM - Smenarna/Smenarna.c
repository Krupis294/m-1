#include "stm32f4xx.h"
#include <stdio.h>
#include <stdlib.h>

void LCD_config(void);
void LCD_ini(void);
void puts_LCD(int radek, char* ukaz);
void LCD_ctrlWR(uint16_t cmd);
void Delay(uint32_t ms);
void LCD_dataWR(uint16_t cmd);
uint8_t getkey(void);
void klavesnice_config(void);

int main() {
	int i=0;
	int poct=0;
	uint8_t vol;
	char czk_char[8];
	char kurz_char[8];
	char vys_char[8];
	char euro_char[8];
	float kurz, vys, czk, euro;
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/10000);
	
	LCD_config();
	LCD_ini();
	klavesnice_config();

	do{
		poct =0;
		LCD_ctrlWR(0x1);
		Delay(1000);
		puts_LCD(1,"SMENARNA");
		LCD_ctrlWR(0xC0);
		do{
			kurz_char[i] = getkey();
			if(kurz_char[i] == '#')
				break;
			if(kurz_char[i] == '.')
				poct++;
			LCD_dataWR(kurz_char[i]);
			Delay(1000);
			i++;
		}while(kurz_char[i-1] != '#');
	}while(poct > 1);
	
	while(1)
	{
		kurz_char[i] = '\0';
		kurz = atof(kurz_char);
		Delay(1000);
		puts_LCD(1,"1 CZK->E");
		puts_LCD(2,"2 E->CZK");
		Delay(1000);
		vol = getkey();
		switch(vol)
		{
			case '1':
				puts_LCD(1,"CZK -> E");
				puts_LCD(2,"        ");
				LCD_ctrlWR(0xC0);
				i=0;
				poct = 0;
				do{
					czk_char[i] = getkey();
					if(czk_char[i] == '#')
						break;
					if(kurz_char[i] == '.')
						poct++;
					LCD_dataWR(czk_char[i]);
					Delay(1000);
					i++;
				}while(czk_char[i] != '#');
				if(poct > 1)
					continue;
				czk_char[i] = '\0';
				czk = atof(czk_char);
				vys = czk / kurz;
				sprintf(vys_char,"%6.2f     ", vys);
				puts_LCD(1,"Vysledek");
				puts_LCD(2,vys_char);
				Delay(15000);
				break;
			case '2':
				puts_LCD(1,"E -> CZK");
				puts_LCD(2,"        ");
				LCD_ctrlWR(0xC0);
				i=0;
				poct = 0;
				do{
					euro_char[i] = getkey();
					if(euro_char[i] == '#')
						break;
					if(kurz_char[i] == '.')
						poct++;
					LCD_dataWR(euro_char[i]);
					Delay(1000);
					i++;
				}while(euro_char[i] != '#');
				if(poct > 1)
					continue;
				euro_char[i] = '\0';
				euro = atof(euro_char);
				vys = euro * kurz;
				sprintf(vys_char,"%6.2f   ", vys);
				puts_LCD(1,"Vysledek");
				puts_LCD(2,vys_char);
				Delay(15000);
				break;
			default:
				break;
		}
	}
}
