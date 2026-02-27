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
#include "PinControl.h"
#include "LetrasNumeros.h"

int setup();

uint8_t matrix[8] = {0};
uint8_t setupdone = 0;
uint8_t actualExec = LETTERS;
	
	

int main(void)
{
	if(setupdone == 0)
	{
		setup();
	}
	
	
	while(1)
	{
		switch(actualExec)
		{
			case LETTERS:
				letras();
				break;
			case SCROLL:
				scrollHello();
				break;
			default:
			break;
		}
	}
}

int setup()
{
	setupdone = 1;
	portMode('B',OUTPUT);
	portMode('D',OUTPUT);
	portMode('C',OUTPUT);
	
	setPortStatus('D',ALLHIGH);
	
	prueba();
	return 0;
}

int prueba()
{
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
	
	for(int i = 0; i<8; i++)
	{
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


void setLight(uint8_t x, uint8_t y)
{
	matrix[y] |= (1 << x);
}

void clearLight(uint8_t x, uint8_t y)
{
	matrix[y] &= ~(1 << x);
}

void setMatrixtoZero()
{
	for(int i = 0; i<8; i++)
	{
		matrix[i] = 0;
	}
}


void refreshMatrix()
{
	for(uint8_t y = 0; y < 8; y++)
	{
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

void letras()
{
	
	while(1)
	{
		showLetter(letter_A);
		showLetter(letter_B);
		showLetter(letter_C);
		showLetter(letter_D);
		showLetter(letter_E);
		showLetter(letter_F);
		showLetter(letter_G);
		showLetter(letter_H);
		showLetter(letter_I);
		showLetter(letter_J);
		showLetter(letter_K);
		showLetter(letter_L);
		showLetter(letter_M);
		showLetter(letter_N);
		showLetter(letter_O);
		showLetter(letter_P);
		showLetter(letter_Q);
		showLetter(letter_R);
		showLetter(letter_S);
		showLetter(letter_T);
		showLetter(letter_U);
		showLetter(letter_V);
		showLetter(letter_W);
		showLetter(letter_X);
		showLetter(letter_Y);
		showLetter(letter_Z);	
	
		showLetter(numero_0);
		showLetter(numero_1);
		showLetter(numero_2);
		showLetter(numero_3);
		showLetter(numero_4);
		showLetter(numero_5);
		showLetter(numero_6);
		showLetter(numero_7);
		showLetter(numero_8);
		showLetter(numero_9);
	}
	
	return 0;
}

void showLetter(uint8_t letter[8])
{
	for(int i = 0; i<8; i++)
	{
		matrix[i] = letter[i];
	}
	
	uint16_t elapsed = 0;
	while(elapsed < 125)
	{
		refreshMatrix();
		_delay_ms(2);
		elapsed += 2;
	}
}

void scrollHello()
{

}