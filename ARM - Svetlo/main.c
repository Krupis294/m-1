#include "stm32f4xx.h"  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "config_kit_ver3.c"

void prumer(float x, int z);

int main() {
	uint16_t volba,volba1;
	
	GPIOD_conf();
	LCD_config();
	klavesnice_config();
	ADC_config();
	
	SystemCoreClockUpdate();                                
	SysTick_Config(SystemCoreClock/ 10000);
	
	LCD_ini();  	
		
	puts_LCD(1,"1:Luxy       ");
	puts_LCD(2,"2:Candel     ");
	volba = getkey();

	puts_LCD(1,"1:Zarovka    ");
	puts_LCD(2,"2:Den.sv     ");
	volba1 = getkey();
	
	//vstup promennych do funkce dle zvolene volby
	if(volba=='1' && volba1=='1') prumer(1.05, 0);
	if(volba=='1' && volba1=='2') prumer(0.95, 0);
	if(volba=='2' && volba1=='1') prumer(1.05, 1);
	if(volba=='2' && volba1=='2') prumer(0.95, 1);		
}

void prumer(float x, int z) { 
	char radek1[50], radek2[50];
	uint16_t sample,i;
	float prum, y;

	while (1) {
		prum = 0;

		for (i = 0; i < 128; i++) {
			sample = sample_1();
			prum = prum + sample;
		}

		prum = prum / 128;
		y = (prum * 3000) / pow(2, 12);

		sprintf(radek1, "mV:%2.f          ", y);
		puts_LCD(1, radek1);

		y = 24.814 * expm1(0.0017 * y);
		y = y * x;

		if (y >= 500) {
			GPIOD->ODR |= (1 << 13);
			GPIOD->ODR |= (1 << 14);
			GPIOD->ODR |= (1 << 15);
		} else {
			GPIOD->ODR &= ~(1 << 13);
			GPIOD->ODR &= ~(1 << 14);
			GPIOD->ODR &= ~(1 << 15);
		}

		if (z == 1) {
			y = y * 0.0929;
			sprintf(radek2,"Cd:%f          ", y);
		} else {
			sprintf(radek2,"Lx:%f          ", y);
		}				

		puts_LCD(2, radek2);
	}
}	
