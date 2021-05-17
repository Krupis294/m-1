#include <RTL.h>
#include "stm32f4xx.h"
#include "config_kit_RTX_2.c"
#include <stdio.h>
#include <math.h>

OS_TID t_job1, t_job2, t_job3;    
__task void job1 (void);	// 0001
__task void job2 (void);	// 0010
__task void job3 (void);	// 0100

const uint16_t N = 8192, N2 = N >> 3;
uint16_t sample_mic[N];
int16_t sample_zvuk[N2];
uint16_t AnOut;

__task void job1(void) {
	int i;

	while(1) {
		os_evt_wait_and(0x0001, 0xFFFF);

		for (i = 200; i < N2; i++) {
			AnOut = sample_zvuk[i] + 2048;
			DAC->DHR12R1 = AnOut;

			Delay(1);
		}

		os_evt_set(0x0004, t_job3);
	}
}

__task void job2(void) {
	int i = 0;
	float RMS, Au, au;
	uint32_t Sum;
	char ComStr[15], Line[9];

	while(1) {
		os_evt_wait_and(0x0002, 0xFFFF);

		read_data_mic(sample_mic, N);									//nacti data z mikrofunu
		decode_PDM2PCM(sample_mic, sample_zvuk, N);		//dekoduj z pulzne sirkove na amplitudovou modulaci
 
		for (i = 200; i < N2; i++) {											//posilej vzorky pomoci COMu 
			sprintf(ComStr, "%d %d\n\r", i, sample_zvuk[i]);
			putserial(ComStr);
		}

		for (i = 256; i < 512; i++) {
			Sum += sample_zvuk[i] * sample_zvuk[i];
		}

		/*	RMS	*/
		RMS = (float) (Sum >> 8); // Sum / 256
		RMS = sqrtf(RMS);

		sprintf(Line, "mV:%.1f       ", RMS);
		puts_LCD(1, Line);

		/*	au  */
		Au = RMS / 32767;
		au = 20*log10f(Au);

		sprintf(Line, "dB:%.1f       ", au);
		puts_LCD(2, Line);

		os_evt_set(0x0001, t_job1);
	}
}

__task void job3(void) {
	while(1) {
		os_evt_wait_and(0x0004, 0xFFFF);

		if (GPIOA->IDR & 0x1) {
			os_evt_set(0x0002, t_job2);
		} else {
			os_evt_set(0x0001, t_job1);
		}	
	}
}

/*----------------------------------------------------------------------------*/

__task void init(void) {
	LCD_config();
	LCD_ini();

	t_job1 = os_tsk_create(job1, 1);
	t_job2 = os_tsk_create(job2, 1);
	t_job3 = os_tsk_create(job3, 1);

	os_evt_set(0x0001, t_job1);
  	os_tsk_delete_self();
}

int main (void) {
	RCC->AHB1ENR |= (1 << 0);

	Mic_config();
	DA_config();
	SERIAL_ini();

	os_sys_init(init);
}
