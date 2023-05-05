#include <stdio.h>
#include "MKL25Z4.h"
#include "uart_code.h"

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

#define RED_LED (18)
#define GREEN_LED (19)
#define BLUE_LED (1)

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
void init_clock();
void init_systick();
void init_UART0();
//void TPM0_IRQHandler();

void transmit_data(char *pdata);
uint32_t get_number_of_ticks(uint32_t start_time, uint32_t end_time);
uint32_t get_time_diff_ms(uint32_t start_time, uint32_t end_time);
void delay_ms(uint16_t delay);
void delay_us(uint16_t delay);
void flash_RED_LED(uint16_t delay);

void spi_init();
uint8_t spi_read_write(uint8_t value);

uint8_t processing = 0;// 0 - Ready to write to FPGA; 1 - Inference is occurring; 2 - Inference result is ready
uint8_t waiting = 0; //1 - Waiting for interrupt; 0 - Not waiting for interrupt
uint16_t ms_count = 0;
uint16_t global_end_time;
uint16_t systick_counter;

int main(void) {
	uint32_t start_time;
	uint32_t end_time;
	uint32_t inference_time;
	uint8_t reset_counter;

	__disable_irq();// Disable interrupts

	init_clock(); // Set system clock to 48MHz
	init_signal_pins(); // Initialise MCU and FPGA signal pins
	init_mcu_to_fpga();// Initialise MCU-to-FPGA communication pins
	init_fpga_to_mcu();// Initialise FPGA-to-MCU communication pins

	init_interrupt();// Initialise interrupts on FPGA_SIGNAL and FPGA_READY pins for communication
	init_TPM();// Initialise the TPM0 timer interrupt

	PTD->PSOR |= 1 << 5;// For Testing purposes

	init_UART0();// Initialise UART
	delay_ms(200);
	init_LED();// Initialise the on-board RED RED_LED
	fpga_reset();// Reset the communication module of the FPGA

	__enable_irq();// Enable interrupts
	init_systick();// Initialise the SysTick timer
	char string[10];
	uint8_t nn_result = 0;
	reset_counter = 0;
	uint32_t tick_diff;
	uint8_t tick_overflow;

	while(1){
//		systick_counter = 0;
//		start_time = SysTick->VAL;
//		for(int i = 0;i < 0xFFFFF;i++);
//		end_time = SysTick->VAL;
//		tick_diff = get_number_of_ticks(start_time, end_time);
//		sprintf(string,"%d,",tick_diff);
////		sprintf(string,"%d,",systick_counter);
//		transmit_data(string);

		 switch(processing){
		 	case 0: // Check if FPGA is performing inference
		 		processing = 1;
				systick_counter = 0;
		 		fpga_write(0x0201);
		 		fpga_write(0x0403);
		 		fpga_write(0x0605);
		 		start_time = SysTick->VAL;
		 		break;

		 	case 2: // Check if FPGA is done performing inference
		 		end_time = global_end_time;
		 		tick_overflow = systick_counter;
		 		nn_result = fpga_read();
//		 		inference_time = get_time_diff_ms(start_time, end_time);
		 		inference_time = get_number_of_ticks(start_time, end_time);
		 		sprintf(string,"%d,",inference_time);
		 		transmit_data(string);
		 		processing = 0;

		 		fpga_reset();// Reset the communication module of the FPGA
		 		break;

		 	default:
//		 		reset_counter++;
//		 		if(reset_counter == 50){
//		 			processing = 0;
//		 			reset_counter = 0;
//		 			fpga_reset();
//		 		}
		 		break;
		 }
	}
	return 0;
}

uint8_t fpga_read(){
	uint8_t value = 0;
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
//	PTB->PCOR |= (1 << RED_LED);
//	while(waiting); // Wait until rising edge is detected on FPGA_SIGNAL
//	PTB->PSOR |= (1 << RED_LED);
}

void fpga_write(uint16_t value){
	fpga_write_byte(value);
	delay_ms(2);
	fpga_write_byte(value >> 8);
	delay_ms(2);
}

void fpga_reset(){
	PTB->PCOR |= (1 << MCU_READY); // Set MCU_READY to low
	delay_ms(20);
	PTB->PSOR |= (1 << MCU_READY); // Set MCU_SIGNAL to high
}

void init_clock(){
	MCG->C1 &= ~(3 << 7); // Sets clock source for MCGOUTCLK to FLL/PLL
	MCG->C1 |= (1 << 2);// Sets slow internal reference clk as input to FLL

	MCG->C4 |= (1 << 5);// Setting mid range as the frequency range for FLL output
	MCG->C4 |= (1 << 7);// Important for setting frequency to 48MHz
}

void init_UART0(){
	// Select MCGFLLCLK as UART0 clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

	// Enable UART0 Clock
	SIM->SCGC4 |= SIM_SCGC4_UART0(1);

	// Enable PORTA clock
	SIM->SCGC5 |= SIM_SCGC5_PORTA(1);

	PORTA->PCR[1] |=  PORT_PCR_MUX(2); /* PTA1 as ALT2 (UART0) */
	PORTA->PCR[2] |=  PORT_PCR_MUX(2); /* PTA2 as ALT2 (UART0) */

	// Configure Baud Rate as 9600
	UART0->BDL = 0x38;
	UART0->BDH = 0x1;

	// Configure Serial Port as 8-N-1
	// (8 data bits, No parity and 1 stop bit)
	UART0->C1  = 0x00;

	// Configure Tx/Rx Interrupts
	UART0->C2  |= UART_C2_TIE(0);  // Tx Interrupt disabled
	UART0->C2  |= UART_C2_TCIE(0); // Tx Complete Interrupt disabled
	UART0->C2  |= UART_C2_RIE(1);     // Rx Interrupt enabled

	// Configure Transmitter/Receiever
	UART0->C2  |= UART_C2_TE(1);  // Tx Enabled
	UART0->C2  |= UART_C2_RE(1);  // Rx Enabled

	// Enable UART0 Interrupt
	NVIC_EnableIRQ(UART0_IRQn);
}

void init_signal_pins(){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

	PORTB->PCR[MCU_SIGNAL] 	&= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[MCU_SIGNAL]	|= (1 << 8);

	PORTB->PCR[MCU_READY] 	&= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[MCU_READY]	|= (1 << 8);

	PORTD->PCR[FPGA_SIGNAL] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[FPGA_SIGNAL]	|= (1 << 8);

	PORTD->PCR[FPGA_READY] 	&= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[FPGA_READY]	|= (1 << 8);


	// SET PINS AS INPUT
	PTD->PDDR &= ~(1 << FPGA_SIGNAL); //FPGA_SIGNAL
	PTD->PDDR &= ~(1 << FPGA_READY); //FPGA_READY

	// SET PINS AS OUTPUT
	PTB->PDDR |= (1 << MCU_SIGNAL); // MCU_SIGNAL
	PTB->PDDR |= (1 << MCU_READY); // MCU_READY

	// TEST PINS
	PORTD->PCR[5] 	&= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[5]	|= (1 << 8);
	PTD->PDDR |= (1 << 5);

	// Initialise pin values
	PTB->PSOR |= (1 << MCU_SIGNAL); // Set MCU_SIGNAL to high
}

void init_LED(){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[RED_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED]	|= (1 << 8);
	PTB->PDDR |= (1 << RED_LED); //RED_LED
	PTB->PSOR |= (1 << RED_LED);

	PORTB->PCR[GREEN_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED]	|= (1 << 8);
	PTB->PDDR |= (1 << GREEN_LED); //GREEN_LED
	PTB->PSOR |= (1 << GREEN_LED);
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

	PORTD->PCR[FPGA_READY] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[FPGA_READY] |= PORT_PCR_MUX(1) | PORT_PCR_IRQC(9);// | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;

	PORTD->PCR[FPGA_SIGNAL] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[FPGA_SIGNAL] |= PORT_PCR_MUX(1) | PORT_PCR_IRQC(9);// | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;

//	NVIC_SetPriority(PORTD_IRQn,2);
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	NVIC_EnableIRQ(PORTD_IRQn);
}

void init_systick(){
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // Enable the SysTick timer
	SysTick->LOAD = 0xFFFFFF; // Set the reload value to the maximum value
	SysTick->VAL = 0; // Clearing the current value of the timer
//	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // Enable the SysTick timer
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk; // Enable the SysTick timer with the processor clock as the source, and enable the SysTick interrupt
}

void init_TPM(){
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;// Enable clock for TPM0
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);	// Set TPM0 clock source to the bus clock (48MHz)
	TPM0->SC |= TPM_SC_PS(7);	// Set TPM0 pre-scaler to divide by 128

	TPM0->MOD = 37500; // (48MHz / 128) / 37500 = 10Hz

	TPM0->SC |= TPM_SC_TOIE_MASK;	// Enable TPM0 interrupt
	TPM0->SC |= TPM_SC_CMOD(1);	// Start TPM0 counter

	NVIC_SetPriority(TPM0_IRQn, 3);	// Set interrupt priority
	NVIC_EnableIRQ(TPM0_IRQn);	// Enable interrupt
}

void SysTick_Handler(void){
	systick_counter++;
}

void PORTD_IRQHandler(void){
	// Check if FPGA has received data
	if(PORTD->ISFR & (1 << FPGA_SIGNAL)){
		PORTD->ISFR |= (1 << FPGA_SIGNAL);
		waiting = 0; // Clear waiting flag to indicate FPGA is done reading and MCU can continue
		PTB->PCOR |= (1 << RED_LED); // Toggle RED_LED
		delay_ms(10);
		PTB->PSOR |= (1 << RED_LED); // Toggle RED_LED
	}

	// Check if FPGA is done processing
//	else if (processing == 1 && PORTD->ISFR & (1 << FPGA_READY)){
	else if (PORTD->ISFR & (1 << FPGA_READY)){
		global_end_time = SysTick->VAL;
		PORTD->ISFR |= (1 << FPGA_READY);
		processing = 2; // Set increment processing flag to tell MCU to read inference result from FPGA data pin
		PTB->PCOR |= (1 << GREEN_LED); // Toggle GREEN_LED
		delay_ms(10);
		PTB->PSOR |= (1 << GREEN_LED); // Toggle GREEN_LED
	}
}

void TPM0_IRQHandler(){
	TPM0->SC |= TPM_SC_TOF_MASK;
	PTD->PTOR |= 1 << 5;
}

void transmit_data(char *pdata){
	uint16_t i;

	// Wait until complete string is transmitted on serial port
	// and every byte is shifted out of Transmit buffer before
	// loading new byte
	while (*pdata)
	{
		__disable_irq();
		UART0->D = *pdata;

		// Wait until byte is transmitted from Tx Buffer
		while (!(UART0->S1 & UART_S1_TDRE_MASK)) {
		}
		__enable_irq();

		pdata++;
	}
}

uint32_t get_number_of_ticks(uint32_t start_time, uint32_t end_time){
	uint32_t tick_diff;
	if(systick_counter > 0){
				tick_diff = 16777216*systick_counter - end_time + start_time;
			}
	else{
		tick_diff = start_time - end_time;
	}
	return tick_diff;
}

uint32_t get_time_diff_ms(uint32_t start_time, uint32_t end_time){
	float clock_period_ms = 0.000208;
	return (start_time - end_time) * clock_period_ms;
}

void flash_RED_LED(uint16_t delay){
	PTB->PCOR |= (1 << RED_LED);
	delay_ms(delay/2);
	PTB->PSOR |= (1 << RED_LED);
	delay_ms(delay/2);
}

void delay_ms(uint16_t delay){
  uint32_t iter =(delay*1000)/20.8;
  for(uint32_t i = 0; i<iter; i++){
    __asm volatile("nop"); //Takes one clock cycle. 1 clock cycle at 48MHz is 20.8ns
  }
}
