#include <stdio.h>
#include "MKL25Z4.h"

#define MD0 0
#define MD1 1
#define MD2 2
#define MD3 3
#define MD4 4
#define MD5 5
#define MD6 6
#define MD7 7

#define FD0 12
#define FD1 13

#define MCU_SIGNAL 0
#define MCU_READY 1
#define FPGA_SIGNAL 2
#define FPGA_READY 3

#define CS (0)
#define SCK (1)
#define MOSI (2)
#define MISO (3)

#define LED (18)

uint8_t fpga_read();
void fpga_write_byte(uint8_t value);
void fpga_write(uint16_t value);
void fpga_reset();

void init_signal_pins();
void init_mcu_to_fpga();
void init_fpga_to_mcu();
void init_interrupt();
void init_LED();
void init_TPM();
void TPM0_IRQHandler()

void delay_ms(uint16_t delay);
void delay_us(uint16_t delay);
void flash_LED(uint8_t delay);

void spi_init();
uint8_t spi_read_write(uint8_t value);

uint8_t processing = 0;// 0 - Ready to write to FPGA; 1 - Inference is occurring; 2 - Inference result is ready
uint8_t nn_result = 0;
uint8_t waiting = 0; //1 - Waiting for interrupt; 0 - Not waiting for interrupt
uint16_t ms_count = 0;

int main(void) {
	__disable_irq();
	init_signal_pins();
	init_mcu_to_fpga();
	init_fpga_to_mcu();

	init_interrupt();
	init_LED();

	PTB->PSOR |= (1 << MCU_SIGNAL); // Set MCU_SIGNAL to high
	PTB->PSOR |= (1 << LED); // Turn off LED

	fpga_reset();

	__enable_irq();
	while(1){
		if(processing == 0){
			fpga_write(3);
			fpga_write(1);
			fpga_write(2);
			processing = 1;
			flash_LED(200);
		}

		else if(processing == 2){
			nn_result = fpga_read();
//			flash_LED(200);
			processing = 0;
		}
	}
	return 0;
}

uint8_t fpga_read(){
	uint8_t value = 0;
//	while(!(PTB->PDIR & (1 << FPGA_SIGNAL))); //Wait until FPGA_SIGNAL goes high
	while(!(PTD->PDIR & (1 << FPGA_SIGNAL))); //Wait until FPGA_SIGNAL goes high
	PTB->PCOR |= (1 << MCU_READY); // Set MCU_READY to low
	value |= (PTC->PDIR & (1 << FD0) >> FD0) << 0;
	value |= (PTC->PDIR & (1 << FD1) >> FD1) << 1;
	PTB->PSOR |= (1 << MCU_READY); // Set MCU_SIGNAL to high
	return value;
}

void fpga_write_byte(uint8_t value){
	waiting = 1;
	PTB->PCOR |= (1 << MCU_SIGNAL); // Set MCU_SIGNAL to low
	PTC->PDOR &= 0xFFFFFF00; // Clear data bits
	PTC->PDOR |= (value); // Set data bits to input value
	PTB->PSOR |= (1 << MCU_SIGNAL); // Set MCU_SIGNAL to high
	PTB->PCOR |= (1 << LED);
//	while(!(PTB->PDIR & (1 << FPGA_SIGNAL))); //Wait until FPGA_SIGNAL goes high
	while(waiting);
	PTB->PSOR |= (1 << LED);
}

void fpga_write(uint16_t value){
	fpga_write_byte(value);
	fpga_write_byte(value >> 8);
}

void fpga_reset(){
	PTB->PCOR |= (1 << MCU_READY); // Set MCU_READY to low
	delay_ms(2);
	PTB->PSOR |= (1 << MCU_READY); // Set MCU_SIGNAL to high
//	while(!(PTB->PDIR & (1 << FPGA_SIGNAL))); //Wait until FPGA_SIGNAL goes high
	while(!(PTD->PDIR & (1 << FPGA_SIGNAL))); //Wait until FPGA_SIGNAL goes high
}

void PortD_IRQHandler(void){
	if(processing == 1){
		processing = 2;
	}

	// Check if code is waiting for an interrupt
	if(waiting){
		waiting = 0;
	}
	// Clear IRQ flags
	PORTD->ISFR = 0xFFFFFFFF;
}

void init_signal_pins(){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

	PORTB->PCR[MCU_SIGNAL] 	&= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[MCU_SIGNAL]	|= (1 << 8);

	PORTB->PCR[MCU_READY] 	&= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[MCU_READY]	|= (1 << 8);

//	PORTB->PCR[FPGA_SIGNAL] &= ~PORT_PCR_MUX_MASK;
//	PORTB->PCR[FPGA_SIGNAL]	|= (1 << 8);
	PORTD->PCR[FPGA_SIGNAL] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[FPGA_SIGNAL]	|= (1 << 8);


//	PORTB->PCR[FPGA_READY] 	&= ~PORT_PCR_MUX_MASK;
//	PORTB->PCR[FPGA_READY]	|= (1 << 8);
	PORTD->PCR[FPGA_READY] 	&= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[FPGA_READY]	|= (1 << 8);

	// SET PINS AS INPUT
//	PTB->PDDR &= ~(1 << FPGA_SIGNAL); //FPGA_SIGNAL
//	PTB->PDDR &= ~(1 << FPGA_READY); //FPGA_READY

	PTD->PDDR &= ~(1 << FPGA_SIGNAL); //FPGA_SIGNAL
	PTD->PDDR &= ~(1 << FPGA_READY); //FPGA_READY

	// SET PINS AS OUTPUT
	PTB->PDDR |= (1 << MCU_SIGNAL); // MCU_SIGNAL
	PTB->PDDR |= (1 << MCU_READY); // MCU_READY

}

void init_LED(){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[LED]	|= (1 << 8);
	PTB->PDDR |= (1 << LED); //LED
}

void init_mcu_to_fpga(){
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

	PORTC->PCR[MD0] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[MD0] |= (1 << 8);
	PORTC->PCR[MD1] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[MD1] |= (1 << 8);
	PORTC->PCR[MD2] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[MD2] |= (1 << 8);
	PORTC->PCR[MD3] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[MD3] |= (1 << 8);
	PORTC->PCR[MD4] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[MD4] |= (1 << 8);
	PORTC->PCR[MD5] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[MD5] |= (1 << 8);
	PORTC->PCR[MD6] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[MD6] |= (1 << 8);
	PORTC->PCR[MD7] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[MD7] |= (1 << 8);

	// SET PINS AS OUTPUT
	PTC->PDDR |= (1 << MD0);
	PTC->PDDR |= (1 << MD1);
	PTC->PDDR |= (1 << MD2);
	PTC->PDDR |= (1 << MD3);
	PTC->PDDR |= (1 << MD4);
	PTC->PDDR |= (1 << MD5);
	PTC->PDDR |= (1 << MD6);
	PTC->PDDR |= (1 << MD7);
}

void init_fpga_to_mcu(){
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

	PORTC->PCR[FD0] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[FD0] |= (1 << 8);
	PORTC->PCR[FD1] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[FD1] |= (1 << 8);

	// SET PINS AS INPUT
	PTC->PDDR &= ~(1 << FD0);
	PTC->PDDR &= ~(1 << FD1);
}

void init_interrupt(){
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[FPGA_READY] = PORT_PCR_MUX_MASK | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(9);
	PORTD->PCR[FPGA_SIGNAL] = PORT_PCR_MUX_MASK | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(9);

	NVIC_SetPriority(PORTD_IRQn,2);
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	NVIC_EnableIRQ(PORTD_IRQn);
}

void init_TPM(){
	// Clock gating for TPM1
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;

	// Setting clock source FOR TPM
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK;
	TPM0->MOD = 374;

	TPM0->SC = TPM0_SC_CMOD(1) | TPM_SC_PS(7) | TPM_SC_TOIE_MASK;

	NVIC_SetPriority(TPM0_IRQn,3);
	NVIC_ClearPendingIRQ(TPM0_IRQn);
	NVIC_EnableIRQ(TPM0_IRQn);

}

void TPM0_IRQHandler(){
	ms_count++;
	TPM0->STATUS |= TPM_STATUS_TOF_MASK;
}

void delay_ms(uint16_t delay){
  uint32_t iter =delay*1618;
  for(uint32_t i = 0; i<iter; i++){
    __asm volatile("nop"); //Takes one clock cycle. 1 clock cycle at 20.9MHz is 47.8ns
  }
}

void delay_us(uint16_t delay){
  uint32_t iter =delay*1618/1000;
  for(uint32_t i = 0; i<iter; i++){
    __asm volatile("nop"); //Takes one clock cycle. 1 clock cycle at 20.9MHz is 47.8ns
  }
}

void flash_LED(uint8_t delay){
	PTB->PCOR |= (1 << LED);
	delay_ms(delay);
	PTB->PSOR |= (1 << LED);
}
