/*
 * GccApplication3.c
 *
 * Created: 26/2/2026 04:12:33
 * Author : jhare
 */ 
#define F_CPU 16000000L

#define LOW 0
#define HIGH 1

#define OUTPUT 1
#define INPUT 0

#define ALLHIGH 0xFF
#define ALLLOW 0x00

#define LETTERS 0
#define SCROLL 1

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "PinControl.h"
#include "LetrasNumeros.h"

int setup();
int prueba();
void setLight(uint8_t x, uint8_t y);
void clearLight(uint8_t x, uint8_t y);
void setMatrixtoZero();
void refreshMatrix();
void letras();
void showLetter(uint8_t letter[8]);
void showSlideLetter(uint8_t letter[8]);
void showSliddingMessage();

uint8_t matrix[8] = {0};
uint8_t setupdone = 0;
volatile uint8_t actualExec = LETTERS;

int main(void){
	// Inicializar pantalla LED
	if(setupdone == 0){
		setup();
	}
	
	// Configurar interrupciones
	DDRC &= ~(1 << DDC3);
	PORTC |= (1 << PORTC3);
	PCICR |= (1 << PCIE1);
	PCMSK1 |= (1 << PCINT11);
	sei();
	
	// Iniciar secuencias
	while(1){
		if(actualExec == LETTERS){
			letras();
		}else{
			showSliddingMessage();
		}
	}
}

int setup(){
	setupdone = 1;
	portMode('B',OUTPUT);
	portMode('D',OUTPUT);
	portMode('C',OUTPUT);
	
	setPortStatus('D',ALLHIGH);
	
	prueba();
	return 0;
}

int prueba(){
	setPortStatus('D',ALLLOW);
	for(int i = 0; i<8; i++)
	{
		setPortStatus('B',ALLLOW);
		setPortStatus('C',ALLLOW);
		if(i<=5)
		setPinStatus('B',i,HIGH);
		else if(i == 6)
		setPinStatus('C', 0, 1);
		else if(i == 7)
		setPinStatus('C', 1, 1);
		
		_delay_ms(200);
	}
	
	setPortStatus('B',ALLHIGH);
	setPortStatus('C',ALLHIGH);
	setPortStatus('D',ALLHIGH);
	
	for(int i = 0; i<8; i++){
		setPortStatus('D',ALLHIGH);
		setPinStatus('D',i,LOW);
		_delay_ms(200);
	}
	
	setPortStatus('D',ALLLOW);
	setPortStatus('B',ALLHIGH);
	setPortStatus('C',ALLHIGH);
	_delay_ms(400);
	
	setPortStatus('B',ALLLOW);
	setPortStatus('C',ALLLOW);
	setPortStatus('D',ALLHIGH);
	return 0;
}


void setLight(uint8_t x, uint8_t y){
	matrix[y] |= (1 << x);
}

void clearLight(uint8_t x, uint8_t y){
	matrix[y] &= ~(1 << x);
}

void setMatrixtoZero(){
	for(int i = 0; i<8; i++){
		matrix[i] = 0;
	}
}


void refreshMatrix(){
	for(uint8_t y = 0; y < 8; y++){
		// Apagar todo
		setPortStatus('D', 0xFF);   // Desactivar filas
		setPortStatus('B', 0x00);
		setPortStatus('C', 0x00);

		// Configurar columnas según buffer
		for(uint8_t x = 0; x < 8; x++)
		{
			if(matrix[y] & (1 << x))
			{
				if(x <= 5)
				setPinStatus('B', x, 1);
				else if(x == 6)
				setPinStatus('C', 0, 1);
				else if(x == 7)
				setPinStatus('C', 1, 1);
			}
		}

		// Activar SOLO la fila actual
		setPinStatus('D', y, 0);
		

		_delay_us(500);
	}
}

void letras(){
	// Arraglo con funciones de letras
	uint8_t* characters[] = {
		letter_A, letter_B, letter_C, letter_D, letter_E,
		letter_F, letter_G, letter_H, letter_I, letter_J,
		letter_K, letter_L, letter_M, letter_N, letter_O,
		letter_P, letter_Q, letter_R, letter_S, letter_T,
		letter_U, letter_V, letter_W, letter_X, letter_Y,
		letter_Z, numero_0, numero_1, numero_2, numero_3,
		numero_4, numero_5, numero_6, numero_7, numero_8,
		numero_9
	};

	for(uint8_t i = 0; i < 36; i++){
		// Terminar proceso
		if(actualExec != LETTERS){
			return;
		}

		showLetter(characters[i]);
	}
}

void showLetter(uint8_t letter[8]){
	for(int i = 0; i<8; i++){
		matrix[i] = letter[i];
	}
	
	uint16_t elapsed = 0;
	while(elapsed < 125){
		refreshMatrix();
		_delay_ms(2);
		elapsed += 2;
	}
}

// Mostrar letras de Derecha a Izquierda
void showSlideLetter(uint8_t letter[8]){
	// Copiar la letra a matriz temporal
	uint8_t tMatrix[8] = {0};
	for(uint8_t i = 0; i < 8; i++){
		tMatrix[i] = letter[i];
	}

	// Limpiar matriz principal
	for(uint8_t i = 0; i < 8; i++){
		matrix[i] = 0b00000000;
	}

	// Efecto de entrada
	for(uint8_t i = 1; i <= 8; i++){
		// Uso de mascara de bits, extraccion y corrimiento
		for(uint8_t row = 0; row < 8; row++){
			uint8_t mask = 0xFF << (8 - i);
			matrix[row] = (matrix[row] << 1) | ((tMatrix[row] & mask) >> (8 - i));
		}

		// Mostrar en pantalla
		uint16_t elapsed = 0;
		while(elapsed < 29){
			refreshMatrix();
			_delay_ms(2);
			elapsed += 2;
		}
	}

	// Efecto de salida
	for(uint8_t i = 0; i < 8; i++){
		// Desplazamiento de 1 bit a la izquierda
		for(uint8_t row = 0; row < 8; row++){
			matrix[row] <<= 1;
		}

		// Mostrar en pantalla
		uint16_t elapsed = 0;
		while(elapsed < 29){
			refreshMatrix();
			_delay_ms(2);
			elapsed += 2;
		}
	}
}

// Mensaje a Mostrar "Hola Mundo 1197428 y 1199835"
void showSliddingMessage(){
	// Arreglo con funciones de letras
	uint8_t* characters[] = {
		letter_H,
		letter_O,
		letter_L,
		letter_A,
		letter_M,
		letter_U,
		letter_N,
		letter_D,
		letter_O,
		numero_1,
		numero_1,
		numero_9,
		numero_7,
		numero_4,
		numero_2,
		numero_8,
		letter_Y,
		numero_1,
		numero_1,
		numero_9,
		numero_9,
		numero_8,
		numero_3,
		numero_5
	};
	
	for(uint8_t i = 0; i < 24; i++){
		// Terminar proceso
		if(actualExec != SCROLL){
			return;
		}

		showSlideLetter(characters[i]);
	}
}

// Funcion de interrupcion
ISR(PCINT1_vect){
	// Anti rebote
	_delay_ms(500);
	
	// Alternar entre modos
	if(actualExec == LETTERS){
		actualExec = SCROLL;
	}else{
		actualExec = LETTERS;
	}
}