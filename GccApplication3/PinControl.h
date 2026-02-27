/*
 * Microcontroladores - Actividad 4.1
 * Libreria_GPIO.c
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

// Declaracion de funciones
void pinMode(char portID, uint8_t pinID, int mode);
void portMode(char portID, int mode);
uint8_t readPinStatus(char portID, uint8_t pinID);
void setPinStatus(char portID, uint8_t pinID, uint8_t status);
uint8_t readPortStatus(char portID);
void setPortStatus(char portID, uint8_t status);


/* Establecer Pin como Entrada/Salida
 * portID:
 *		  'B' = Puerto B seleccionado
 *		  'C' = Puerto C seleccionado
 *		  'D' = Puerto D seleccionado
 * pinID:
 *		  Puerto B = 0 a 7
 *		  Puerto C = 0 a 6
 *		  Puerto D = 0 a 7
 * mode:
 *		  0 = Entrada
 *		  1 = Salida
 */
void pinMode(char portID, uint8_t pinID, int mode){
	// Determinar Puerto
	switch(portID){
		case 'B':
			// Validar si pinID esta dentro del rango
			if((pinID >= 0) && (pinID <= 7)){
				//Seleccionar modo de direccionamiento
				if(mode == 1){
					DDRB |= (1 << pinID);
				}else{
					DDRB &= ~(1 << pinID);
				}
			}
			break;
			
		case 'C':
			// Validar si pinID esta dentro del rango
			if((pinID >= 0) && (pinID <= 6)){
				//Seleccionar modo de direccionamiento
				if(mode == 1){
					DDRC |= (1 << pinID);
				}else{
					DDRC &= ~(1 << pinID);
				}
			}
			break;
			
		case 'D':
			// Validar si pinID esta dentro del rango
			if((pinID >= 0) && (pinID <= 7)){
				//Seleccionar modo de direccionamiento
				if(mode == 1){
					DDRD |= (1 << pinID);
				}else{
					DDRD &= ~(1 << pinID);
				}
			}
			break;
			
		default:
			// Nada
			break;
	}
}

/* Establecer Puerto como Entrada/Salida
 * portID:
 *		  'B' = Puerto B seleccionado
 *		  'C' = Puerto C seleccionado
 *		  'D' = Puerto D seleccionado
 * mode:
 *		  0 = Entrada
 *		  1 = Salida
 */
void portMode(char portID, int mode){
	// Determinar puerto
	switch(portID){
		case 'B':
			// Determinar modo de direccionamiento
			if(mode == 1){
				DDRB = 0xFF;
			}else{
				DDRB = 0x00;
			}
			break;
			
		case 'C':
			// Determinar modo de direccionamiento
			if(mode == 1){
				DDRC = 0xFF;
			}else{
				DDRC = 0x00;
			}
			break;
		
		case 'D':
			// Determinar modo de direccionamiento
			if(mode == 1){
				DDRD = 0xFF;
			}else{
				DDRD = 0x00;
			}
			break;
		
		default:
			// Nada
			break;
	}
}

/* Leer estado de Pin
 * portID:
 *		  'B' = Puerto B seleccionado
 *		  'C' = Puerto C seleccionado
 *		  'D' = Puerto D seleccionado
 * pinID:
 *		  Puerto B = 0 a 7
 *		  Puerto C = 0 a 6
 *		  Puerto D = 0 a 7
 */
uint8_t readPinStatus(char portID, uint8_t pinID){
	// Estado de pin
	uint8_t pinStatus = 0;
	
	// Determinar puerto
	switch(portID){
		case 'B':
			// Determinar validez de pinID
			if((pinID >= 0) && (pinID <= 7)){
				// Derminar estado de pin
				if(PINB & (1 << pinID)){
					pinStatus = 1;
				}
			}
			break;
			
		case 'C':
			// Determinar validez de pinID
			if((pinID >= 0) && (pinID <= 6)){
				// Derminar estado de pin
				if(PINC & (1 << pinID)){
					pinStatus = 1;
				}
			}
			break;
		
		case 'D':
			// Determinar validez de pinID
			if((pinID >= 0) && (pinID <= 7)){
				// Derminar estado de pin
				if(PIND & (1 << pinID)){
					pinStatus = 1;
				}
			}
			break;
		
		default:
			// Nada
			break;
	}
	return pinStatus;
}

/* Escribir estado de Pin
 * portID:
 *		  'B' = Puerto B seleccionado
 *		  'C' = Puerto C seleccionado
 *		  'D' = Puerto D seleccionado
 * pinID:
 *		  Puerto B = 0 a 7
 *		  Puerto C = 0 a 6
 *		  Puerto D = 0 a 7
 * status:
 *		  0 = LOW
 *		  1 = HIGH
 */
void setPinStatus(char portID, uint8_t pinID, uint8_t status){
	// Seleccionar puerto
	switch(portID){
		case 'B':
			// Determinar validez de pinID
			if((pinID >= 0) && (pinID <= 7)){
				// Establer estado HIGH o LOW
				if(status == 1){
					PORTB |= (1 << pinID);
				}else{
					PORTB &= ~(1 << pinID);
				}
			}
			break;
			
		case 'C':
			// Determinar validez de pinID
			if((pinID >= 0) && (pinID <= 6)){
				// Establer estado HIGH o LOW
				if(status == 1){
					PORTC |= (1 << pinID);
				}else{
					PORTC &= ~(1 << pinID);
				}
			}
			break;
		
		case 'D':
			// Determinar validez de pinID
			if((pinID >= 0) && (pinID <= 7)){
				// Establer estado HIGH o LOW
				if(status == 1){
					PORTD |= (1 << pinID);
				}else{
					PORTD &= ~(1 << pinID);
				}
			}
			break;
		
		default:
			// Nada
			break;
	}
}

/* Leer estado de un Puerto
 * portID:
 *		  'B' = Puerto B seleccionado
 *		  'C' = Puerto C seleccionado
 *		  'D' = Puerto D seleccionado
 */
uint8_t readPortStatus(char portID){
	// Seleccionar puerto
	switch(portID){
		case 'B':
			return PINB;
		break;
		
		case 'C':
			return PINC;
		break;
		
		case 'D':
			return PIND;
		break;
		
		default:
			return 0;
		break;
	}
}

/* Escribir estado de un Puerto
 * portID:
 *		  'B' = Puerto B seleccionado
 *		  'C' = Puerto C seleccionado
 *		  'D' = Puerto D seleccionado
 * status:
 *		  0x00 = LOW
 *		  0xFF = HIGH
 */
void setPortStatus(char portID, uint8_t status){
	// Seleccionar puerto
	switch(portID){
		case 'B':
			PORTB = status;
		break;
		
		case 'C':
			PORTC = status;
		break;
		
		case 'D':
			PORTD = status;
		break;
		
		default:
			// Nada
		break;
	}
}

