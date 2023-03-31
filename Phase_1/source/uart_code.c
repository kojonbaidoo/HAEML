#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#define RX	1		//PTA1
#define TX	2		//PTA2
#define OSR 15		//over sample rate
#define BAUD_RATE   (9600)	//baud rate
#define SYS_CLOCK	48000000	//
#define MASK(x) (1UL << (x))

//static char rxChar;

void init_pins(void);
void init_UART(void);
void uart_send_byte(uint8_t data);
void uart_print(char *string);
void uart_esc_code();

#define BLUE 1
#define RED 18
#define GREEN 19
volatile char rxChar; //char rx over BT
volatile char txChar;
int done =1; //to track if there is any char to transmit.
//done=1 means no more chars to transmit, disable transmitter
//178nterrupts

void init_LEDs(void);
void lightLED(void);
char * message1 = " All good students read the ";
char * message2 = "Reference Manual";
char * message3 = "Test:";

char * redclr = "\033[31m";
char * greenclr = "\033[33m";
char * blueclr = "\033[34m";
char * whiteclr= "\033[37m";
char * curdwn3= "\033[3B";
char * curdwn1= "\033[1B";
char * right5= "\033[5C";
char * right21= "\033[21C";
char * blink= "\033[5m";
char * rtrn= "\033H";
char * attrstr= "\0338";
char * clearscreen= "\033[2J";
char * retcur= "\033[0;0H";

//int main (void) {
//	init_pins();
//	init_UART();
//	init_LEDs();
//	while (1) {
//		//uart_esc_code(clearscreen);
//		lightLED();
//     	uart_esc_code(retcur);
//		uart_esc_code(curdwn3);
//		uart_esc_code(right5);
//		//uart_esc_code(message1);
//     	uart_print(message1);
//     	uart_esc_code(curdwn1);
//     	uart_esc_code(right21);
//     	uart_esc_code(blink);
//     	uart_print(message2);
//     	uart_esc_code(retcur);
//     	uart_esc_code(attrstr);
//     	uart_print(message3);
//
//		//(0x77);
//
//	}
//}


void init_pins(void){
	//Clock gate port A
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[RX] &= ~PORT_PCR_MUX_MASK;  	//clear mux
	PORTA->PCR[RX] =  PORT_PCR_MUX(2); 	//set for UART0 RX
	PORTA->PCR[TX] &= ~PORT_PCR_MUX_MASK;	//clear
	PORTA->PCR[TX] =  PORT_PCR_MUX(2); 	//set for UART0 TX
}

void init_UART(void){

	// clock gate UART0
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;		//clock gate UART0

	//select clock for uart0 4MHz
//	SIM->SOPT2 |= (3<<26); //Select MCG for uart
//	MCG -> C1 |= 0x2;  //enable internal reference clock
//	MCG -> C2 |= 0x1; // select 4MHz source
//	MCG -> SC &= ~0xE;

	 //The MCG is set to the IRC which runs at 4 MHz when set to fast IRC

	  SIM->SOPT2 |= (1 << 26);   //SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	  SIM->SOPT2 &=~ (1 << 16);


	  MCG->C1 |= MCG_C1_CLKS(0);  	// Select PLL/FLL as clock source
	  MCG->C1 |= MCG_C1_IREFS(1); 	// Sel Internal Reference clock for FLL
	  MCG->C4 |= MCG_C4_DRST_DRS(1); 	// Select DCO range as Mid range
	  MCG->C4 |= MCG_C4_DMX32(1);    	// Select DCO frequency as 48Mhz


	UART0 -> C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK; //disable transmitter and receiver before initialization

	//compute set baud rate (SBR), choosing baud rate of 115200 for BT
	uint16_t sbr = (uint16_t)((SYS_CLOCK)/((OSR+1) *BAUD_RATE ));	//default OSR is 15, sbr=2.17 if SYS_CLOCK = 4MHz

	UART0 -> BDH &= ~UART0_BDH_SBR_MASK;
	UART0 -> BDH |= UART0_BDH_SBR(sbr >> 8);
	UART0 -> BDL &= ~UART0_BDL_SBR_MASK;
	UART0 -> BDL = UART0_BDL_SBR(sbr);
	UART0 -> C4 |= UART0_C4_OSR(OSR);


	// Only Rx Interrupt enabled
	UART0->C2 |= UART_C2_RIE_MASK | UART_C2_RE_MASK ;
	//note: C1 settings unchanged. Default is 8N1 if uart0->C1=0
	//setup and enable interrupts
	NVIC_SetPriority(UART0_IRQn, 3);
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable UART transmitter and receiver
	UART0->C2 |= UART0_C2_TE (1) | UART0_C2_RE (1);

}



//void lightLED(void){
//	switch (rxChar){
//		case 'r':
//				break;
//		case 'g':
//				break;
//		case 'b':
//				break;
//		default:
//
//	}
//}
//

void uart_send_byte(uint8_t data)
{
	// Ensure Tx Buffer is empty
	while (!(UART0->S1 & UART0_S1_TDRE_MASK));
	//printf("sending: %d",data);
	UART0->D = data;
}

void uart_print(char* string){

	while(*string != '\0'){
		uart_send_byte(*string);
		string++;
	}

}

void uart_esc_code(char* string1){

	//uart_send_byte("[3B");
	while(*string1 != '\0'){
		uart_send_byte(*string1);
		string1++;
	}
}


void init_LEDs(void) {
// Clock gate ports B (red+green) and D (blue)
SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
//set up mux for leds. Blue is on port D. Make output
PORTD->PCR[BLUE] &= ~PORT_PCR_MUX_MASK;
PORTD->PCR[BLUE] |= PORT_PCR_MUX(1);
PTD->PDDR |= MASK(BLUE); //direction is output
PORTB->PCR[RED] &= ~PORT_PCR_MUX_MASK;
PORTB->PCR[RED] |= PORT_PCR_MUX(1);
PORTB->PCR[GREEN] &= ~PORT_PCR_MUX_MASK;
PORTB->PCR[GREEN] |= PORT_PCR_MUX(1);
PTB->PDDR |= MASK(RED) | MASK(GREEN); //output
}

void lightLED(void){
//turn off all leds
PTB->PSOR = MASK(RED);
PTB->PSOR = MASK(GREEN);
PTD->PSOR = MASK(BLUE);
switch (rxChar){
	case 'r':
	PTB->PCOR = MASK(RED);
	uart_esc_code(redclr);
	break;
	case 'g':
	PTB->PCOR = MASK(GREEN);
	uart_esc_code(greenclr);
	break;
	case 'b':
	PTD->PCOR = MASK(BLUE);
	uart_esc_code(blueclr);
	break;
	case 'w':
	PTB->PCOR = MASK(RED);
	PTB->PCOR = MASK(GREEN);
	PTD->PCOR = MASK(BLUE);
	uart_esc_code(whiteclr);
	break;
	default:
	PTB->PCOR = MASK(RED);
	PTB->PCOR = MASK(GREEN);
//	PTD->PCOR = MASK(BLUE);

}
}

void UART0_IRQHandler(void) {
uint8_t ch;
if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK |
UART_S1_FE_MASK | UART_S1_PF_MASK)) {
// clear the error flags
UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
UART0_S1_FE_MASK | UART0_S1_PF_MASK;
// read the data register to clear RDRF
ch = UART0->D;
}
if (UART0->S1 & UART0_S1_RDRF_MASK) {
// received a character
ch = UART0->D;
rxChar=ch; //to enable me take some action
}

//
////deal with transmission
//if ( (UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
//(UART0->S1 & UART0_S1_TDRE_MASK) ) { // tx buffer empty
//// can send another character
//if (1) {
//UART0->D = 'a';
//done=1;
//} else {
//// 1-char queue is empty so disable transmitter
//UART0->C2 &= ~UART0_C2_TIE_MASK;
//}
//}
}


